/* Copyright 2018 TechieLiang. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "restaurant_db_initialization.h"

#include <QtSql>
#include <QString>
#include <QVariant>
/* Copyright 2018 TechieLiang. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "predef.h"

#include "system_config_manager.h"
#include "restaurant_sql_command.h"

typedef DbInitializationInterface::InitReturnType rtype;

DbInitializationInterface::InitReturnType RestaurantDbInitialization::Init() {
    QSqlDatabase db;
    if(QSqlDatabase::contains(kSqlConnectionName))
        db = QSqlDatabase::database(kSqlConnectionName);
    else
        db = QSqlDatabase::addDatabase(kSqlDbType, kSqlConnectionName);
    auto configs = SystemConfigManager::GetInstance();

    //系统配置有错误，此时初始化直接返回未知错误
    if(SystemConfigManager::kConfigNoError != configs->is_good()) {
        qWarning("RestaurantDbInitialization::Init-"
                 "SystemConfigManager is kConfigNoError");
        return DbInitializationInterface::kUnknowError;
    }
    //从系统配置获取数据库相关配置内容并赋值
    db.setDatabaseName(configs->GetConfig(SystemConfigManager::kSqlDbName));
    db.setHostName(configs->GetConfig(SystemConfigManager::kSqlHost));
    db.setPort(configs->GetConfig(SystemConfigManager::kSqlPort).toInt());
    db.setUserName(configs->GetConfig(SystemConfigManager::kSqlUserName));
    db.setPassword(configs->GetConfig(SystemConfigManager::kSqlUserPassword));

    //尝试连接数据库
    if(!db.open()) {
        auto error = db.lastError();
        QString message = QString("RestaurantDbInitialization::"
                                  "Init-db open:%1")
                          .arg(error.text());
        qWarning(message.toStdString().c_str());
        switch (error.type()) {
        case QSqlError::ConnectionError:
            return DbInitializationInterface::kDbServerConnectError;
        default:
            return DbInitializationInterface::kUnknowError;
        }
    }

    //数据库连接成功-清除相关表
    if(!restaurant::DeleteTable::DeleteAll()) {
        return DbInitializationInterface::kDbCannotDeleteSameTable;
    }

    //建立表
    if(!restaurant::CreateTable::CreatAll()) {
        return DbInitializationInterface::kDbCannotCreatTable;
    }
    return DbInitializationInterface::kOk;
}

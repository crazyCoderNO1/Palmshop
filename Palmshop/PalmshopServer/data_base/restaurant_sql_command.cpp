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

#include "restaurant_sql_command.h"

#include <QtSql>
#include <QCryptographicHash>

#include "system_config_manager.h"

#include "predef.h"

namespace restaurant {
namespace restaurant_private {
namespace create_table {
const static QString Commodity =
    "CREATE TABLE if not exists `Commodity`("
    "`id` BIGINT NOT NULL primary key AUTO_INCREMENT,"
    "`comm_id` VARCHAR(50) NOT NULL,"
    "`comm_name` VARCHAR(50) NOT NULL,"
    "`comm_unit_id` INT NOT NULL,"
    "`comm_price` INT NOT NULL,"
    "`comm_vip_price` INT NOT NULL,"
    "`is_usable` TINYINT NOT NULL,"
    "`comm_describe` TEXT NOT NULL);";
const static QString CommPackage =
    "CREATE TABLE if not exists `CommPackage`("
    "`id` BIGINT NOT NULL primary key AUTO_INCREMENT,"
    "`package_id` VARCHAR(50) NOT NULL,"
    "`package_name` VARCHAR(50) NOT NULL,"
    "`package_source_price` INT NOT NULL,"
    "`package_price` INT NOT NULL,"
    "`package_vip_price` INT NOT NULL,"
    "`is_usable` TINYINT NOT NULL,"
    "`package_describe` TEXT NOT NULL);";
const static QString CommUnit =
    "CREATE TABLE if not exists `CommUnit`("
    "`unit_id` INT NOT NULL primary key AUTO_INCREMENT ,"
    "`unit_name` VARCHAR(50) NOT NULL);";
const static QString EmployeeAccount =
    "CREATE TABLE if not exists `EmployeeAccount`("
    "`id` INT NOT NULL primary key AUTO_INCREMENT ,"
    "`account` CHAR(20) NOT NULL,"
    "`password` CHAR(41) NOT NULL,"
    "`name` CHAR(10) NOT NULL,"
    "`telnum` CHAR(20) NOT NULL,"
    "`email` CHAR(30) NOT NULL,"
    "`sex` TINYINT NOT NULL,"
    "`hire_date` DATE NOT NULL,"
    "`leave_date` DATE);";
const static QString Order =
    "CREATE TABLE if not exists `Order`("
    "`id` BIGINT NOT NULL primary key AUTO_INCREMENT ,"
    "`order_id` VARCHAR(50) NOT NULL,"
    "`sequence` INT NOT NULL,"
    "`date` DATE NOT NULL,"
    "`order_time` TIME(0) NOT NULL,"
    "`submitter` INT NOT NULL,"
    "`table_number` INT NOT NULL,"
    "`total_amount` INT NOT NULL,"
    "`vip_id` INT,"
    "`is_settlement` TINYINT NOT NULL,"
    "`cashier` INT,"
    "`is_draw_bill` TINYINT NOT NULL,"
    "`bill_id` VARCHAR(50),"
    "`is_effective` TINYINT NOT NULL);";
const static QString OrderDetail =
    "CREATE TABLE if not exists `OrderDetail`("
    "`id` BIGINT NOT NULL primary key AUTO_INCREMENT ,"
    "`order_id` VARCHAR(50) NOT NULL,"
    "`comm_id` VARCHAR(50) NOT NULL,"
    "`comm_name` VARCHAR(50) NOT NULL,"
    "`comm_price` INT NOT NULL,"
    "`number` INT NOT NULL,"
    "`discount` INT NOT NULL,"
    "`subtotal` INT NOT NULL);";
const static QString OrderSettlement =
    "CREATE TABLE if not exists `OrderSettlement`("
    "`id` BIGINT NOT NULL primary key AUTO_INCREMENT ,"
    "`order_id` VARCHAR(50) NOT NULL,"
    "`payment_type` INT NOT NULL,"
    "`payment_amount` INT NOT NULL);";
const static QString PaymentType =
    "CREATE TABLE if not exists `PaymentType`("
    "`payment_type` INT NOT NULL primary key AUTO_INCREMENT ,"
    "`payment_name` VARCHAR(50) NOT NULL);";
const static QString SystemConfig =
    "CREATE TABLE if not exists `SystemConfig`("
    "`id` INT NOT NULL primary key AUTO_INCREMENT ,"
    "`name` VARCHAR(50) NOT NULL,"
    "`value` TEXT NOT NULL);";
const static QString VipCustomer =
    "CREATE TABLE if not exists `VipCustomer`("
    "`id` INT NOT NULL primary key AUTO_INCREMENT ,"
    "`vip_id` VARCHAR(50) NOT NULL,"
    "`customer_name` VARCHAR(50) NOT NULL,"
    "`customer_phone_num` VARCHAR(50) NOT NULL,"
    "`registration_time` DATETIME(0) NOT NULL,"
    "`effective_time` DATETIME(0) NOT NULL,"
    "`account_balance` INT NOT NULL);";
const static QString VipRechargeOrder =
    "CREATE TABLE if not exists `VipRechargeOrder`("
    "`id` BIGINT primary key AUTO_INCREMENT ,"
    "`vip_id` VARCHAR(50),"
    "`record_value` INT,"
    "`record_date` DATE,"
    "`record_time` TIME(0));";
}//namespace create_table

namespace delete_table {
const static QString Commodity =
    "DROP TABLE IF EXISTS `Commodity`;";
const static QString CommPackage =
    "DROP TABLE IF EXISTS `CommPackage`;";
const static QString CommUnit =
    "DROP TABLE IF EXISTS `CommUnit`;";
const static QString EmployeeAccount =
    "DROP TABLE IF EXISTS `EmployeeAccount`;";
const static QString Order =
    "DROP TABLE IF EXISTS `Order`;";
const static QString OrderDetail =
    "DROP TABLE IF EXISTS `OrderDetail`;";
const static QString OrderSettlement =
    "DROP TABLE IF EXISTS `OrderSettlement`;";
const static QString PaymentType =
    "DROP TABLE IF EXISTS `PaymentType`;";
const static QString SystemConfig =
    "DROP TABLE IF EXISTS `SystemConfig`;";
const static QString VipCustomer =
    "DROP TABLE IF EXISTS `VipCustomer`;";
const static QString VipRechargeOrder =
    "DROP TABLE IF EXISTS `VipRechargeOrder`;";
}//namespace delete_table

QSqlError::ErrorType RunSql (QString sql_text) {
    QSqlQuery sql_query(sql_text, QSqlDatabase::database(kSqlConnectionName));
    if(!sql_query.exec()) {
        QSqlError error = sql_query.lastError();
        QString warning_text = error.text() + " " + sql_text;
        qWarning(warning_text.toStdString().c_str());
        return error.type();
    }
    return QSqlError::NoError;
}
}//namespace restaurant_private

bool RestaurantSqlCommand::ConnectDbJudgement() {
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
        return false;
    }

    //从系统配置获取数据库相关配置内容并赋值
    db.setDatabaseName(configs->GetConfig(SystemConfigManager::kSqlDbName));
    db.setHostName(configs->GetConfig(SystemConfigManager::kSqlHost));
    db.setPort(configs->GetConfig(SystemConfigManager::kSqlPort).toInt());
    db.setUserName(configs->GetConfig(SystemConfigManager::kSqlUserName));
    db.setPassword(configs->GetConfig(SystemConfigManager::kSqlUserPassword));
    //尝试连接数据库
    if(db.open()) {
        return true;
    }
    //连接失败
    auto error = db.lastError();
    QString message = QString("RestaurantDbInitialization::"
                              "Init-db open:%1")
                      .arg(error.text());
    qWarning(message.toStdString().c_str());
    return false;
}

bool RestaurantSqlCommand::CreatAllTable() {
    using namespace restaurant_private::create_table;
    if(restaurant_private::RunSql(Commodity)) return false;
    if(restaurant_private::RunSql(CommPackage)) return false;
    if(restaurant_private::RunSql(CommUnit)) return false;
    if(restaurant_private::RunSql(EmployeeAccount)) return false;
    if(restaurant_private::RunSql(Order)) return false;
    if(restaurant_private::RunSql(OrderDetail)) return false;
    if(restaurant_private::RunSql(OrderSettlement)) return false;
    if(restaurant_private::RunSql(PaymentType)) return false;
    if(restaurant_private::RunSql(SystemConfig)) return false;
    if(restaurant_private::RunSql(VipCustomer)) return false;
    if(restaurant_private::RunSql(VipRechargeOrder)) return false;
    return true;
}

bool RestaurantSqlCommand::DeleteAllTable() {
    using namespace restaurant_private::delete_table;
    if(restaurant_private::RunSql(Commodity)) return false;
    if(restaurant_private::RunSql(CommPackage)) return false;
    if(restaurant_private::RunSql(CommUnit)) return false;
    if(restaurant_private::RunSql(EmployeeAccount)) return false;
    if(restaurant_private::RunSql(Order)) return false;
    if(restaurant_private::RunSql(OrderDetail)) return false;
    if(restaurant_private::RunSql(OrderSettlement)) return false;
    if(restaurant_private::RunSql(PaymentType)) return false;
    if(restaurant_private::RunSql(SystemConfig)) return false;
    if(restaurant_private::RunSql(VipCustomer)) return false;
    if(restaurant_private::RunSql(VipRechargeOrder)) return false;
    return true;
}

int RestaurantSqlCommand::LoginJudgement(const QString &account,
        const QString &password) {
    QString pw = QCryptographicHash::hash(password.toLatin1(),
                                          QCryptographicHash::Sha3_512).toHex();
    pw = QCryptographicHash::hash(pw.toLatin1(),
                                  QCryptographicHash::Md5).toHex();
    QString sql_text = "SELECT id from employeeaccount "
                       "WHERE '%1' = employeeaccount.account and "
                       "PASSWORD('%2') = employeeaccount.password;";
    //FIXME 内容替换，不知道为什么不能用bindValue，等待解决
    sql_text = sql_text.arg(account).arg(pw);
    QSqlQuery sql_query(sql_text, QSqlDatabase::database(kSqlConnectionName));
    if(!sql_query.exec()) {
        QSqlError error = sql_query.lastError();
        QString warning_text = error.text() + " " + sql_text;
        qWarning(warning_text.toStdString().c_str());
        return -1;
    }
    QList<int> users_id;
    while(sql_query.next()) {
        users_id.append(sql_query.value(0).toInt());
    }
    if(users_id.size() == 1) {
        return users_id.first();
    }
    return -1;
}






}//namespace restaurant

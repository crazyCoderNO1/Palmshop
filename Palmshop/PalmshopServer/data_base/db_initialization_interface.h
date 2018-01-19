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

#ifndef DB_INITIALIZATION_INTERFACE_H
#define DB_INITIALIZATION_INTERFACE_H

#include <QObject>

/**
 * @brief The DbInitializationInterface class
 *   根据系统配置中不同店铺类型进行相应的数据库初始化
 */
class DbInitializationInterface : public QObject {
    Q_OBJECT
  public:
    enum InitReturnType {
        kOk,///成功
        kShopTypeError,///系统配置中店铺类型与此初始化不匹配
        kDbServerConnectError,///数据库服务器连接失败
        kDbNameUnfind,///指定数据库名称未找到
        kDbCannotCreatTable,///数据库无法建立表,可能用户权限不足
        kDbCannotDeleteSameTable,///数据库有重名表且无法删除
        kUnknowError,///未知错误
    };
    Q_ENUM(InitReturnType)
    /**
     * @brief 虚析构函数
     */
    virtual ~DbInitializationInterface() { }
    /**
     * @brief Init 初始化
     * @return 初始化状态
     */
    virtual InitReturnType Init() = 0;
};

#endif // DB_INITIALIZATION_INTERFACE_H

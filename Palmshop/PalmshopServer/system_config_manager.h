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

#ifndef SYSTEM_CONFIG_MANAGER_H
#define SYSTEM_CONFIG_MANAGER_H

#include <QObject>

/**
 * @brief The SystemConfig class 单例
 */
class SystemConfigManager : public QObject {
    Q_OBJECT
  public:
    /**
     * @brief 配置错误类型
     */
    enum ConfigError {
        kConfigNoError,///无错误
        kConfigFileCreateError,///配置文件创建失败
        kConfigReadNotAllError,///配置文件读取-配置内容不全错误
        kConfigUnInit,///配置文件未初始化
    };
    Q_ENUM(ConfigError)
    /**
     * @brief 系统配置枚举
     */
    enum SystemConfigType {
        //系统全局配置
        kShopType = 0,///商店类型-饭店、小商品
        kAdministratorAccount,///店铺管理员账号,若连锁请使用服务端登陆账号
        kAdministratorPassword,///店铺管理员密码
        //连锁店铺配置
        kIsMultipleShop = 100,///是否为连锁店铺
        kHeadquartersHost,///总部服务器主机名或IP地址
        kHeadquartersPort,///总部服务器端口号
        //数据库
        kSqlUserName = 200, ///MySQL登陆用户名
        kSqlUserPassword,   ///MySQL登陆密码
        kSqlHost,           ///MySQL数据库主机名或IP地址
        kSqlPort,           ///MySQL服务器的端口号
        kSqlDbName, ///MySQL数据库名称,要求此库存在且具有完全权限
    };
    Q_ENUM(SystemConfigType)
    /**
     * @brief 商店类型枚举
     */
    enum ShopType {
        kShopTypeRestaurant,///饭店
        kShopTypeRetailStore,///零售店
    };
    Q_ENUM(ShopType)
    /**
     * @brief 单例模式，获取实例化对象
     * @param 无
     * @return 单例对象
     */
    static SystemConfigManager * GetInstance();
    /**
     * @brief 单例模式，主动销毁实例化对象
     * @param 无
     * @return 无
     */
    static void DestoryInstance();
    /**
     * @brief 设置配置值
     * @param value 值
     * @param type 值类型
     */
    void SetConfig(QString value, SystemConfigType type);
    /**
     * @brief 获取配置值
     * @param type 值类型
     * @return 值
     */
    QString GetConfig(SystemConfigType type);
    /**
     * @brief 系统配置管理器状态判断
     * @return 状态
     */
    ConfigError is_good();
    /**
     * @brief 自检并修复
     * @return 修复后状态
     */
    ConfigError CheckAndRepair();
  private:
    /**
     * @brief 构造函数
     */
    SystemConfigManager();
    /**
     * @brief 单例模式在程序结束时自动删除单例的方法
     */
    class SingletonDel {
      public:
        ~SingletonDel() {
            if (instance_ != nullptr) {
                delete instance_;
                instance_ = nullptr;
            }
        }
    };
    static SystemConfigManager singleton_del_;///程序结束时销毁
    static SystemConfigManager *instance_;    //单例对象指针
};

#endif // SYSTEM_CONFIG_MANAGER_H

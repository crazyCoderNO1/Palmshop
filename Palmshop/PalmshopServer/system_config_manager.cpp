#include "system_config_manager.h"
#include <QMutex>
#include <QMutexLocker>
#include <QVariant>
#include <QMetaEnum>
#include <QSettings>
#include <QFile>
#include <QMap>
#include "predef.h"
//私有静态成员
namespace system_config_manager_private {
//配置未读取到的默认值
const static QString kDefaultValue = "defaultValue";
//互斥量
static QMutex mutex_;
//枚举-字符串映射
static QMetaEnum config_enum_ =
    QMetaEnum::fromType<SystemConfigManager::SystemConfigType>();
//配置枚举-值映射
static QMap<SystemConfigManager::SystemConfigType, QVariant> config_map_;
/**
 * @brief 读取配置文件
 */
void ReadConfigFile (QSettings *configs) {
    for(int i = 0, num = config_enum_.keyCount(); i < num; ++i) {
        QVariant config = configs->value(config_enum_.key(i), kDefaultValue);
        if(config.toString() == "defaultValue")
            Q_ASSERT(QString("config read error").isEmpty());
        config_map_.insert(static_cast<SystemConfigManager::SystemConfigType>
                           (config_enum_.value(i)), config);
    }
}
/**
 * @brief 创建默认配置文件
 */
void CreatDefaultConfigFile(QSettings *configs) {
    for(int i = 0, num = config_enum_.keyCount(); i < num; ++i) {
        switch (config_enum_.value(i)) {
        case SystemConfigManager::kConfigShopType:
            configs->setValue(config_enum_.key(i),
                              SystemConfigManager::kShopTypeRestaurant);
            break;
        case SystemConfigManager::kConfigAdministratorAccount:
            configs->setValue(config_enum_.key(i), "");
            break;
        case SystemConfigManager::kConfigAdministratorPassword:
            configs->setValue(config_enum_.key(i), "");
            break;
        case SystemConfigManager::kConfigMultipleShop:
            configs->setValue(config_enum_.key(i), false);
            break;
        case SystemConfigManager::kConfigHeadquartersHost:
            configs->setValue(config_enum_.key(i), "");
            break;
        case SystemConfigManager::kConfigHeadquartersPort:
            configs->setValue(config_enum_.key(i), "");
            break;
        case SystemConfigManager::kConfigShopName:
            configs->setValue(config_enum_.key(i), "");
            break;
        case SystemConfigManager::kConfigShopId:
            configs->setValue(config_enum_.key(i), "");
            break;
        case SystemConfigManager::kConfigSqlUserName:
            configs->setValue(config_enum_.key(i), "");
            break;
        case SystemConfigManager::kConfigSqlUserPassword:
            configs->setValue(config_enum_.key(i), "");
            break;
        case SystemConfigManager::kConfigSqlHost:
            configs->setValue(config_enum_.key(i), "");
            break;
        case SystemConfigManager::kConfigSqlPort:
            configs->setValue(config_enum_.key(i), "");
            break;
        case SystemConfigManager::kConfigSqlDbName:
            configs->setValue(config_enum_.key(i), "");
            break;
        default: {
            qDebug(config_enum_.key(i));
            Q_ASSERT(QString("CreatDefaultConfigFile-cann't "
                             "creat all config").isEmpty());
            break;
        }
        }
    }
}
}//namespace system_config_manager_private
SystemConfigManager *SystemConfigManager::instance_ = nullptr;
//单例模式，获取实例化对象
SystemConfigManager *SystemConfigManager::GetInstance() {
    if (instance_ == nullptr) {
        QMutexLocker lock(&system_config_manager_private::mutex_);
        if (instance_ == nullptr) {
            instance_ = new SystemConfigManager();
        }
    }
    return instance_;
}
//单例模式，主动销毁实例化对象
void SystemConfigManager::DestoryInstance() {
    if (instance_ != nullptr) {
        delete instance_;
        instance_ = nullptr;
    }
}
//设置配置值
void SystemConfigManager::SetConfig
(QVariant value, SystemConfigManager::SystemConfigType type) {
    system_config_manager_private::config_map_.insert(type, value);
}
//获取配置值
QVariant SystemConfigManager::GetConfig(SystemConfigManager::
                                        SystemConfigType type) {
    return system_config_manager_private::config_map_.value(type,
            system_config_manager_private::kDefaultValue);
}
//构造函数
SystemConfigManager::SystemConfigManager() {
    //判断配置文件是否存在
    QSettings configs(QSettings::IniFormat,
                      QSettings::SystemScope,
                      kProgramDeveloperName,
                      kProgramName);
    QFile file(configs.fileName());
    if(file.exists()) {//文件存在-读取
        system_config_manager_private::ReadConfigFile(&configs);
    } else { //文件不存在-以默认配置创建后读取
        system_config_manager_private::CreatDefaultConfigFile(&configs);
        if(file.exists())
            system_config_manager_private::ReadConfigFile(&configs);
        else
            qFatal("系统配置文件读取失败且重新创建默认配置文件失败");
    }
}

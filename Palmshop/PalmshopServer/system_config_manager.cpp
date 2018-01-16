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
void ReadConfigFile () {
    QSettings configs(QSettings::IniFormat,
                      QSettings::SystemScope,
                      "TechieLiang",
                      "Palmshop");
}
/**
 * @brief 创建默认配置文件
 */
void CreatDefaultConfigFile() {

}
}//namespace system_config_manager_private
SystemConfigManager *SystemConfigManager::instance_ = nullptr;
//析构函数
SystemConfigManager::~SystemConfigManager() {

}
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
    return system_config_manager_private::config_map_.value(type, QVariant());
}
//构造函数
SystemConfigManager::SystemConfigManager() {
    //判断配置文件是否存在
    QFile file(kSystemConfigFilePath);
    if(file.exists()) {//文件存在-读取
        system_config_manager_private::ReadConfigFile();
    } else { //文件不存在-以默认配置创建后读取
        system_config_manager_private::CreatDefaultConfigFile();
        if(file.exists())
            system_config_manager_private::ReadConfigFile();
        else
            qFatal("系统配置文件读取失败且重新创建默认配置文件失败");
    }
}

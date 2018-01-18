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
static QMutex kGetInstanceMutex_;
//枚举-字符串映射
static QMetaEnum KConfigEnum =
    QMetaEnum::fromType<SystemConfigManager::SystemConfigType>();
static SystemConfigManager::ConfigError kManagerState;
static QSettings kConfigs(QSettings::IniFormat,
                          QSettings::SystemScope,
                          kProgramDeveloperName,
                          kProgramName);//配置管理对象
}//namespace system_config_manager_private
//私有命名空间别名
namespace private_ = system_config_manager_private;
//类静态成员初始化
SystemConfigManager *SystemConfigManager::instance_ = nullptr;
//单例模式，获取实例化对象
SystemConfigManager *SystemConfigManager::GetInstance() {
    if (instance_ == nullptr) {
        QMutexLocker lock(&private_::kGetInstanceMutex_);
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
(QString value, SystemConfigManager::SystemConfigType type) {
    //判断是否具有此类型，防止使用错误导致配置内容膨胀
    if(private_::KConfigEnum.valueToKey(type) == 0) {
        return;
    }
    private_::kConfigs.setValue(private_::KConfigEnum.valueToKey(type),
                                value);
}
//获取配置值
QString SystemConfigManager::GetConfig(SystemConfigManager::
                                       SystemConfigType type) {
    QString type_text = private_::KConfigEnum.valueToKey(type);
    QString config = private_::kConfigs.value(type_text,
                     private_::kDefaultValue).toString();
    //如果读取到的为设定的默认值，则表明文件中并未记录此配置
    //状态转为配置文件记录不全
    if(config == private_::kDefaultValue) {
        private_::kManagerState = kConfigReadNotAllError;
    }
    return config;
}

SystemConfigManager::ConfigError SystemConfigManager::is_good() {
    return private_::kManagerState;
}
//自检并修复
SystemConfigManager::ConfigError SystemConfigManager::CheckAndRepair() {
    QFile file(private_::kConfigs.fileName());
    if(!file.exists()) {//文件存在-读取
        private_::kManagerState = kConfigFileCreateError;
        return private_::kManagerState;
    }
    bool is_all_config_right = true;
    int enum_num = private_::KConfigEnum.keyCount();
    for(int i = 0; i < enum_num; ++i) {
        if(private_::kDefaultValue ==
                GetConfig(static_cast<SystemConfigManager::SystemConfigType>
                          (private_::KConfigEnum.value(i)))) {
            is_all_config_right = false;
            break;
        }
    }
    if(!is_all_config_right) {
        private_::kManagerState = kConfigReadNotAllError;
        return private_::kManagerState;
    }
    private_::kManagerState = kConfigNoError;
    return private_::kManagerState;
}
//构造函数
SystemConfigManager::SystemConfigManager() {
    //判断配置文件是否存在
    QFile file(private_::kConfigs.fileName());
    if(file.exists()) {//文件存在
        private_::kManagerState = CheckAndRepair();
    } else { //文件不存在
        //新建配置-均赋值为默认值，等修改
        for(int i = 0, num = private_::KConfigEnum.keyCount();
                i < num;
                ++i) {
            private_::kConfigs.setValue(private_::KConfigEnum.key(i),
                                        private_::kDefaultValue);
        }
        if(file.exists()) {
            //新建了配置需要初始化
            private_::kManagerState = kConfigUnInit;
        } else {
            //新建失败，错误
            private_::kManagerState = kConfigFileCreateError;
            qFatal("系统配置文件读取失败且重新创建默认配置文件失败");
        }
    }
}

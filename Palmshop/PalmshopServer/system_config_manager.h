/**
 * @file
 * @brief 本文件包含全局系统配置类声明。
 * @version 1.0.0.0
 * @date 2018.01.16
 * @author 周亮
 */
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
     * @brief 系统配置枚举
     */
    enum SystemConfigType {
        //系统全局配置
        kSystemShopType = 0,///商店类型-饭店、小商品
        //数据库
        kSqlUserName = 100, ///MySQL用户名
        kSqlUserpassword,   ///MySQL密码
        kSqlHost,           ///MySQL数据库主机名或IP地址
        kSqlPort,           ///MySQL服务器的端口号
        kSqlDbName,         ///MySQL数据库名称
    };
    Q_ENUM(SystemConfigType)
    /**
     * @brief 析构函数
     */
    ~SystemConfigManager();
    /**
     * @brief 单例模式，获取实例化对象
     * @param 无
     * @return 单例对象
     */
    static SystemConfigManager* GetInstance();
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
    void SetConfig(QVariant value, SystemConfigType type);
    /**
     * @brief 获取配置值
     * @param type 值类型
     * @return 值
     */
    QVariant GetConfig(SystemConfigType type);
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
    static SystemConfigManager *instance_;       //单例对象指针
};
#endif // SYSTEM_CONFIG_MANAGER_H

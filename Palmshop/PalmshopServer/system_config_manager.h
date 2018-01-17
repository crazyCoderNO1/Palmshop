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
        kConfigShopType = 0,///商店类型-饭店、小商品
        kConfigAdministratorAccount,///店铺管理员账号,若连锁请使用服务端登陆账号
        kConfigAdministratorPassword,///店铺管理员密码
        //连锁店铺配置
        kConfigMultipleShop = 100,///连锁店铺
        kConfigHeadquartersHost,///总部服务器主机名或IP地址
        kConfigHeadquartersPort,///总部服务器端口号
        kConfigShopName,///当前店铺的名字或唯一id
        kConfigShopId,///当前店铺的唯一id,提供名称和id分离的识别方式，以id为识别标注
        //数据库
        kConfigSqlUserName = 200, ///MySQL用户名
        kConfigSqlUserPassword,   ///MySQL密码
        kConfigSqlHost,           ///MySQL数据库主机名或IP地址
        kConfigSqlPort,           ///MySQL服务器的端口号
        kConfigSqlDbName,         ///MySQL数据库名称
    };
    Q_ENUM(SystemConfigType)
    /**
     * @brief 商店类型枚举
     */
    enum ShopType {
        kShopTypeRestaurant,///饭店
        kShopTypeRetailStore,///零售店
    };
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
    static SystemConfigManager *instance_;    //单例对象指针
};
#endif // SYSTEM_CONFIG_MANAGER_H

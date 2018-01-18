/**
 * @file
 * @brief 数据库初始化接口
 * @version 1.0.0.0
 * @date 2018.01.18
 * @author 周亮
 */
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

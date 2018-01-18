#include "restaurant_db_initialization.h"
#include <QtSql>
#include <QString>
#include <QVariant>
//#include "D:/Qt/Qt5.10.0/5.10.0/Src/sql/drivers/psql/qsql_mysql.cpp"
#include "predef.h"
#include "system_config_manager.h"
typedef DbInitializationInterface::InitReturnType rtype;
namespace restaurant_db_initialization_private {
static QString kDeleteAll = "DROP TABLE IF EXISTS `commodity_package_detail_table`;"
                            "DROP TABLE IF EXISTS `commodity_package_table`;"
                            "DROP TABLE IF EXISTS `commodity_table`;"
                            "DROP TABLE IF EXISTS `commodity_unit_table`;"
                            "DROP TABLE IF EXISTS `employees_account_table`;
                            "DROP TABLE IF EXISTS `orders_detail_table`;
                            "DROP TABLE IF EXISTS `orders_settlement_table`;
                            "DROP TABLE IF EXISTS `orders_table`;
                            "DROP TABLE IF EXISTS `orders_YEAR_old_detail_table`;
                            "DROP TABLE IF EXISTS `orders_YEAR_old_settlement_table`;
                            "DROP TABLE IF EXISTS `payment_type_table`;
                            "DROP TABLE IF EXISTS `system_config_table`;
                            "DROP TABLE IF EXISTS `vip_customer_table`;
                            "DROP TABLE IF EXISTS `vip_recharge_record_table`;";
static QString kCreatecommodity_package_detail_table =
    "CREATE TABLE `commodity_package_detail_table`"
    "("
    "`id` INT not null primary key auto_increment,"
    "`commodity_id` CHAR(20) not null,"
    "`commodity_name` VARCHAR(50) not null,"
    "`commodity_unit` INT not null,"
    "`commodity_price` INT not null,"
    "`commodity_number` INT not null);";
bool RunSql(QString sql_text) {
    QSqlQuery sql_query(sql_text, QSqlDatabase::database(kSqlConnectionName));
    if(!sql_query.exec()) {
        return false;
    }
    return true;
}
}//namespace restaurant_db_initialization_private
DbInitializationInterface::InitReturnType RestaurantDbInitialization::Init() {
    QSqlDatabase db = QSqlDatabase::addDatabase(kSqlDbType, kSqlConnectionName);
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
//数据库连接成功
    return DbInitializationInterface::kOk;
}

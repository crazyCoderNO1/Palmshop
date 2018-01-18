#ifndef RESTAURANT_DB_INITIALIZATION_H
#define RESTAURANT_DB_INITIALIZATION_H
#include "db_initialization_interface.h"
/**
 * @brief 饭店-店铺类型数据库初始化
 */
class RestaurantDbInitialization : public DbInitializationInterface {
  public:
    /**
     * @brief 析构函数
     */
    ~RestaurantDbInitialization() override {}
    /**
     * @brief Init 初始化
     * @return 初始化状态
     */
    InitReturnType Init() override final;
};
#endif // RESTAURANT_DB_INITIALIZATION_H

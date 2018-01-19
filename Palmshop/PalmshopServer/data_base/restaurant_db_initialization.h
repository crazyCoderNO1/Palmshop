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

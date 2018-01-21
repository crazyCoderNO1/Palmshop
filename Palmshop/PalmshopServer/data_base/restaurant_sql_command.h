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

#ifndef RESTAURANT_SQL_COMMAND_H
#define RESTAURANT_SQL_COMMAND_H

#include <QObject>
#include <QString>

namespace restaurant {
/**
 * @brief 表类型
 * 为了方便表类型及表名转换，下述枚举以k+表默认名称方式存储
 */
enum class TableType {
    //系统相关
    SystemConfig,//系统配置
    //商品相关
    Commodity,//商品
    CommPackage,//套餐
    CommUnit,//商品量纲、单位
    //店员相关
    EmployeeAccount,//店员账户
    //订单相关
    Order,//订单
    OrderDetail,//订单详情
    //支付相关
    OrderSettlement,//订单支付信息
    PaymentType,//支付类型
    //客户相关
    VipCustomer,//vip客户
    VipRechargeOrder,//vip客户充值记录
};

//表名称
const static QList<QString>
kTableName{{"SystemConfig"},
    {"Commodity"}, {"CommPackage"}, {"CommUnit"},
    {"EmployeeAccount"},
    {"Order"}, {"OrderDetail"},
    {"OrderSettlement"}, {"PaymentType"},
    {"VipCustomer"}, {"VipRechargeOrder"}};

class RestaurantSqlCommand {
  public:
    //判断是否连接了数据库
    static bool ConnectDbJudgement();
    //创建所有表
    static bool CreatAllTable();
    //删除所有表
    static bool DeleteAllTable();
    //判断登陆信息 传入用户填写的原始的用户密码
    //-1为登陆失败，其余为用户id
    static int LoginJudgement(const QString &account, const QString &password);
};
}//namespace restaurant

#endif // RESTAURANT_SQL_COMMAND_H

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

#include "main_window.h"
#include "ui_main_window.h"

#include <QDebug>
#include <QAction>
#include <QMessageBox>

#include "predef.h"
#include "system_config_manager.h"
#include "user_interface/system_config_setting_dialog.h"
#include "user_interface/login_dialog.h"

//餐饮类相关
#include "data_base/restaurant_db_initialization.h"
#include "data_base/restaurant_sql_command.h"
#include "user_interface/restaurant_checkstand_form.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //窗口标题
    setWindowTitle(kProgramName);

    //状态栏设置
    //不显示其内控件的边框
    statusBar()->setStyleSheet("QStatusBar::item{border: 0px}");
    //永久部件
    statusBar()->addPermanentWidget(new QLabel(kProgramName +
                                    " by " + kProgramDeveloperName));
    //临时部件
    statusbar_state_label_  = new QLabel(this);
    statusBar()->addWidget(statusbar_state_label_);

    //根据用户权限显示功能
    if(!SystemConfigManager::GetInstance()->user_is_admin()) {
        //非管理员用户隐藏用户管理
        ui->menu_admin->menuAction()->setVisible(false);
        //隐藏个人信息修改
        ui->action_information_modification->setVisible(false);
    } else {
        //管理员用户具有用户管理、系统配置等功能
        //管理员专用菜单栏信号槽
        //系统配置按钮
        connect(ui->action_admin_config, &QAction::triggered, []() {
            SystemConfigSettingDialog dialog;
            dialog.exec();
        });
    }

    //通用菜单栏信号槽
    //退出
    connect(ui->action_exit, &QAction::triggered, []() {
        exit(0);
    });
    //注销
    connect(ui->action_logout, &QAction::triggered, []() {
        LoginDialog login_dialog;
        login_dialog.exec();
        //非正常关闭登陆对话框，直接退出程序
        if(login_dialog.user_id() == -1) {
            exit(0);
        }
    });
    //收银
    connect(ui->action_cashier, &QAction::triggered, []() {
        RestaurantCheckstandForm restaurant_form;
        restaurant_form.show();
        //阻塞主窗口
        QEventLoop loop;
        connect(&restaurant_form, SIGNAL(WidgetClose()), &loop, SLOT(quit()));
        loop.exec(QEventLoop::AllEvents);
    });

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetState(const QString & text, bool is_good) {
    QPalette pa;
    if(is_good)
        pa.setColor(QPalette::WindowText, Qt::green);
    else
        pa.setColor(QPalette::WindowText, Qt::red);
    statusbar_state_label_->setPalette(pa);
    statusbar_state_label_->setText(text);
}

void MainWindow::showEvent(QShowEvent * event) {
    Q_UNUSED(event);
}



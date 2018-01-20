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
#include "data_base/restaurant_db_initialization.h"
#include "user_interface/login_dialog.h"
#include "data_base/restaurant_sql_command.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //窗口标题
    setWindowTitle(kProgramName);

    //菜单栏信号槽
    //退出
    connect(ui->action_exit, &QAction::triggered, []() {
        exit(0);
    });
    //系统配置
    connect(ui->action_config, &QAction::triggered, []() {
        SystemConfigSettingDialog dialog;
        dialog.exec();
    });
    //系统配置
    connect(ui->action_config, &QAction::triggered, []() {
        SystemConfigSettingDialog dialog;
        dialog.exec();
    });

    //状态栏设置
    //不显示其内控件的边框
    statusBar()->setStyleSheet("QStatusBar::item{border: 0px}");
    //永久部件
    statusBar()->addPermanentWidget(new QLabel(kProgramName +
                                    " by " + kProgramDeveloperName));
    //临时部件
    statusbar_state_label_  = new QLabel(this);
    statusBar()->addWidget(statusbar_state_label_);

    //系统配置检查
    if(SystemConfigManager::kConfigNoError !=
            SystemConfigManager::GetInstance()->CheckAndRepair()) {
        SetState("系统配置文件错误，请更改配置信息！", false);
        qWarning("系统配置文件错误，请更改配置信息！");
    } else {
        if(restaurant::RestaurantSqlCommand::ConnectDbJudgement()) {
            SetState("数据库登陆成功", true);
        } else {
            SetState("数据库登陆失败", false);
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetState(const QString &text, bool is_good) {
    QPalette pa;
    if(is_good)
        pa.setColor(QPalette::WindowText, Qt::green);
    else
        pa.setColor(QPalette::WindowText, Qt::red);
    statusbar_state_label_->setPalette(pa);
    statusbar_state_label_->setText(text);
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
}

void MainWindow::on_pushButton_clicked() {
    LoginDialog d;
    d.exec();
}

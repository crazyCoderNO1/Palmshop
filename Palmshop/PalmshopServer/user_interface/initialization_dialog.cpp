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

#include "initialization_dialog.h"
#include "ui_initialization_dialog.h"

#include <QCloseEvent>
#include <QTimer>

#include "system_config_manager.h"
#include "system_config_setting_dialog.h"
#include "data_base/restaurant_sql_command.h"

InitializationDialog::InitializationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitializationDialog),
    is_closeable_(false) {
    ui->setupUi(this);
    //隐藏标题栏
    setWindowFlags(Qt::FramelessWindowHint);
    //启动显示
    timer_ = new QTimer();
    connect(timer_, &QTimer::timeout, this, &InitializationDialog::TimerRunInit);
    ShowUpdata(QString(), 0);//初始状态为0
    timer_->start();
}

InitializationDialog::~InitializationDialog() {
    delete ui;
}

bool InitializationDialog::is_closeable() {
    return is_closeable_;
}

void InitializationDialog::closeEvent(QCloseEvent *event) {
    if(is_closeable_) {
        QDialog::closeEvent(event);
    } else {
        event->ignore();
    }
}

void InitializationDialog::ShowUpdata(QString text, int pross) {
    ui->label_state->setText(text);
    ui->progressBar->setValue(pross);
}

void InitializationDialog::TimerRunInit() {
    timer_->stop();
    QString state_text;
    int pross_value;
    state_text = "检测系统配置信息……";
    pross_value = 10;
    ShowUpdata(state_text, pross_value);

    //系统配置文件检查
    if(SystemConfigManager::kConfigNoError !=
            SystemConfigManager::GetInstance()->CheckAndRepair()) {
        state_text = "系统配置文件错误，请更改配置信息！更改完成后请点击退出并重新启动";
        pross_value = 0;
        ShowUpdata(state_text, pross_value);
        qWarning(state_text.toStdString().c_str());
        SystemConfigSettingDialog dialog;
        dialog.exec();
        return;
    }
    state_text = "检测数据库连接状态……";
    pross_value = 50;
    ShowUpdata(state_text, pross_value);
    if(!restaurant::RestaurantSqlCommand::ConnectDbJudgement()) {
        state_text = "数据库连接失败，请修改配置后重新启动";
        pross_value = 80;
        ShowUpdata(state_text, pross_value);
        qWarning(state_text.toStdString().c_str());
        return;
    }
    state_text = "启动成功";
    pross_value = 100;
    ShowUpdata(state_text, pross_value);
    is_closeable_ = true;
    close();
}

void InitializationDialog::on_pushButton_clicked() {
    exit(0);
}

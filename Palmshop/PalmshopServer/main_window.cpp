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
#include <QMessageBox>

#include "system_config_manager.h"
#include "user_interface/system_config_setting_dialog.h"
#include "data_base/restaurant_db_initialization.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    if(SystemConfigManager::kConfigNoError !=
            SystemConfigManager::GetInstance()->CheckAndRepair()) {
        ui->pushButton->setText("请先配置");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event) {
    QMainWindow::showEvent(event);
}

void MainWindow::on_pushButton_clicked() {
    SystemConfigSettingDialog setting_dialog(this);
    setting_dialog.exec();
}

void MainWindow::on_pushButton_2_clicked() {
    DbInitializationInterface *db = new RestaurantDbInitialization();
    auto r = db->Init();
    if(r != DbInitializationInterface::kOk) {
        QMessageBox::warning(this, "失败", QString::number(r));
    } else {
        QMessageBox::warning(this, "成功", QString::number(r));
    }
    delete db;
}

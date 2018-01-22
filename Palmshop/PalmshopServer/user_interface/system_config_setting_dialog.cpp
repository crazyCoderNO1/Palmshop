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

#include "system_config_setting_dialog.h"
#include "ui_system_config_setting_dialog.h"

#include "system_config_manager.h"

SystemConfigSettingDialog::SystemConfigSettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemConfigSettingDialog) {
    ui->setupUi(this);
    ui->comboBox_shop_type->addItem(
        "餐饮", SystemConfigManager::kShopTypeRestaurant);
    ui->comboBox_shop_type->addItem(
        "小商品", SystemConfigManager::kShopTypeRetailStore);
    auto configs = SystemConfigManager::GetInstance();
    ui->comboBox_shop_type->setCurrentIndex(ui->comboBox_shop_type->findData(
            configs->GetConfig(SystemConfigManager::kShopType).toInt()));
    ui->checkBox_is_have_parent->setChecked(configs->GetConfig(
            SystemConfigManager::kIsMultipleShop).toInt());
    on_checkBox_is_have_parent_stateChanged(
        ui->checkBox_is_have_parent->checkState());
    ui->lineEdit_admin_account->setText(
        configs->GetConfig(SystemConfigManager::kAdministratorAccount));
    ui->lineEdit_admin_password->setText(
        configs->GetConfig(SystemConfigManager::kAdministratorPassword));
    ui->lineEdit_db_ip->setText(
        configs->GetConfig(SystemConfigManager::kSqlHost));
    ui->lineEdit_db_port->setText(
        configs->GetConfig(SystemConfigManager::kSqlPort));
    ui->lineEdit_db_account->setText(
        configs->GetConfig(SystemConfigManager::kSqlUserName));
    ui->lineEdit_db_password->setText(
        configs->GetConfig(SystemConfigManager::kSqlUserPassword));
    ui->lineEdit_db_name->setText(
        configs->GetConfig(SystemConfigManager::kSqlDbName));
    ui->lineEdit_parent_ip->setText(
        configs->GetConfig(SystemConfigManager::kHeadquartersHost));
    ui->lineEdit_parent_port->setText(
        configs->GetConfig(SystemConfigManager::kHeadquartersPort));
}

SystemConfigSettingDialog::~SystemConfigSettingDialog() {
    delete ui;
}

void SystemConfigSettingDialog::
on_checkBox_is_have_parent_stateChanged(int) {
    if(ui->checkBox_is_have_parent->isChecked()) {
        ui->lineEdit_parent_port->setEnabled(true);
        ui->lineEdit_parent_ip->setEnabled(true);
    } else {
        ui->lineEdit_parent_port->setEnabled(false);
        ui->lineEdit_parent_ip->setEnabled(false);
    }
}

void SystemConfigSettingDialog::on_pushButton_yes_clicked() {
    auto configs = SystemConfigManager::GetInstance();
    configs->SetConfig(QString::number(ui->comboBox_shop_type->
                                       currentData().toInt()),
                       SystemConfigManager::kShopType);
    configs->SetConfig(ui->lineEdit_admin_account->text(),
                       SystemConfigManager::kAdministratorAccount);
    configs->SetConfig(ui->lineEdit_admin_password->text(),
                       SystemConfigManager::kAdministratorPassword);
    configs->SetConfig(ui->lineEdit_db_account->text(),
                       SystemConfigManager::kSqlUserName);
    configs->SetConfig(ui->lineEdit_db_password->text(),
                       SystemConfigManager::kSqlUserPassword);
    configs->SetConfig(ui->lineEdit_db_ip->text(),
                       SystemConfigManager::kSqlHost);
    configs->SetConfig(ui->lineEdit_db_port->text(),
                       SystemConfigManager::kSqlPort);
    configs->SetConfig(ui->lineEdit_db_name->text(),
                       SystemConfigManager::kSqlDbName);
    configs->SetConfig(QString::number((int)(ui->checkBox_is_have_parent->
                                       isChecked())),
                       SystemConfigManager::kIsMultipleShop);
    if(ui->checkBox_is_have_parent->isChecked()) {
        configs->SetConfig(ui->lineEdit_parent_ip->text(),
                           SystemConfigManager::kHeadquartersHost);
        configs->SetConfig(ui->lineEdit_parent_port->text(),
                           SystemConfigManager::kHeadquartersPort);
    } else {
        configs->SetConfig(QString(),
                           SystemConfigManager::kHeadquartersHost);
        configs->SetConfig(QString(),
                           SystemConfigManager::kHeadquartersPort);
    }
    close();
}

void SystemConfigSettingDialog::on_pushButton_no_clicked() {
    close();
}

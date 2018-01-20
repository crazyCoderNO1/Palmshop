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

#include "login_dialog.h"
#include "ui_login_dialog.h"

#include "data_base/restaurant_sql_command.h"
#include <QDebug>


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog) {
    ui->setupUi(this);
}

LoginDialog::~LoginDialog() {
    delete ui;
}

void LoginDialog::on_pushButton_clicked() {
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();
    qDebug() << restaurant::RestaurantSqlCommand::LoginJudgement(account, password);
}

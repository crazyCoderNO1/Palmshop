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

#include <QCloseEvent>

#include "data_base/restaurant_sql_command.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog) {
    ui->setupUi(this);
    //隐藏标题栏右侧最小化、大小化、关闭按钮、问号按钮
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint
                   & ~Qt::WindowContextHelpButtonHint);
    user_id_ = -1;
}

LoginDialog::~LoginDialog() {
    delete ui;
}

int LoginDialog::user_id() {
    return user_id_;
}

void LoginDialog::closeEvent(QCloseEvent *event) {
    if(user_id_ > 0) {
        QDialog::closeEvent(event);
    } else {
        event->ignore();
    }
}

void LoginDialog::on_pushButton_login_clicked() {
    QString account = ui->lineEdit_account->text();
    QString password = ui->lineEdit_password->text();
    int user_id = restaurant::RestaurantSqlCommand::
                  LoginJudgement(account, password);
    //登陆成功
    if(user_id > 0) {
        user_id_ = user_id;
        close();
    }
}

void LoginDialog::on_pushButton_exit_clicked() {
    exit(0);
}

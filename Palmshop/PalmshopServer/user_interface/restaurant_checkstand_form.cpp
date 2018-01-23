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

#include "restaurant_checkstand_form.h"
#include "ui_restaurant_checkstand_form.h"

RestaurantCheckstandForm::RestaurantCheckstandForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RestaurantCheckstandForm) {
    ui->setupUi(this);
    setWindowFlag(Qt::WindowStaysOnTopHint, true);//置顶显示
    showFullScreen();//全屏显示
}

RestaurantCheckstandForm::~RestaurantCheckstandForm() {
    delete ui;
}

void RestaurantCheckstandForm::closeEvent(QCloseEvent *event) {
    emit WidgetClose();
    QWidget::closeEvent(event);
}

void RestaurantCheckstandForm::on_pushButton_clicked() {
    emit WidgetClose();
    close();
}

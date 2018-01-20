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

#ifndef INITIALIZATION_DIALOG_H
#define INITIALIZATION_DIALOG_H

#include <QDialog>

namespace Ui {
class InitializationDialog;
}

/**
 * @brief 初始化对话框
 * 检查程序系统配置、数据库连接、显示程序启动进度条等
 * 若配置不完整或数据库连接不成功，跳转至配置页面
 */
class InitializationDialog : public QDialog {
    Q_OBJECT

  public:
    explicit InitializationDialog(QWidget *parent = 0);
    ~InitializationDialog();

  private:
    Ui::InitializationDialog *ui;
};

#endif // INITIALIZATION_DIALOG_H

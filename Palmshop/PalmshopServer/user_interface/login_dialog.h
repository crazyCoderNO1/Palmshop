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

#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}
/**
 * @brief 登陆对话框，提供用户密码输入及验证功能
 */
class LoginDialog : public QDialog {
    Q_OBJECT

  public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    int user_id();
  protected:
    //重写关闭事件，防止Ctrl+F4等途径跳过登陆页面
    void closeEvent(QCloseEvent *event) override;
  private slots:
    //登陆按钮点击
    void on_pushButton_login_clicked();
    //退出按钮点击
    void on_pushButton_exit_clicked();

  private:
    Ui::LoginDialog *ui;
    int user_id_;
};

#endif // LOGIN_DIALOG_H

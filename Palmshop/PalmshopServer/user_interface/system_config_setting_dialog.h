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

#ifndef SYSTEM_CONFIG_SETTING_DIALOG_H
#define SYSTEM_CONFIG_SETTING_DIALOG_H

#include <QDialog>

namespace Ui {
class SystemConfigSettingDialog;
}

class SystemConfigSettingDialog : public QDialog {
    Q_OBJECT
  public:
    explicit SystemConfigSettingDialog(QWidget *parent = 0);
    ~SystemConfigSettingDialog();

  private slots:
    void on_checkBox_is_have_parent_stateChanged(int arg1);

    void on_pushButton_yes_clicked();

    void on_pushButton_no_clicked();

  private:
    Ui::SystemConfigSettingDialog *ui;
};

#endif // SYSTEM_CONFIG_SETTING_DIALOG_H

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

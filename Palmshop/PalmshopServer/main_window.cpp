#include "main_window.h"
#include "ui_main_window.h"
#include "system_config_manager.h"
#include "user_interface/system_config_setting_dialog.h"
#include "data_base/restaurant_db_initialization.h"
#include <QDebug>
#include <QMessageBox>
//构造函数
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    if(SystemConfigManager::kConfigNoError !=
            SystemConfigManager::GetInstance()->CheckAndRepair()) {
        ui->pushButton->setText("请先配置");
    }
}
//析构函数
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

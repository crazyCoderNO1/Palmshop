#include "main_window.h"
#include "ui_main_window.h"
#include "system_config_manager.h"
//构造函数
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    SystemConfigManager::GetInstance();
}
//析构函数
MainWindow::~MainWindow() {
    delete ui;
}

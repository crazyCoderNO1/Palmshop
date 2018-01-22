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

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    /**
     * @brief 构造函数
     * @param parent
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief 析构函数
     */
    ~MainWindow();
  public slots:
    /**
     * @brief 设置系统状态
     * @param text 状态值
     * @param is_good 状态好坏
     */
    void SetState(const QString &text, bool is_good);
  protected:
    /**
     * @brief 显示事件-窗口显示时操作
     * @param event
     */
    void showEvent(QShowEvent *event) override;
  private slots:

  private:
    Ui::MainWindow *ui;
    QLabel *statusbar_state_label_;

};

#endif // MAIN_WINDOW_H

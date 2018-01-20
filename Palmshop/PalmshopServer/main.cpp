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

#include <QApplication>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>

#include "main_window.h"
#include "user_interface/login_dialog.h"

/**
 * @brief CustomOutputMessage
 * @param type 消息类型
 * @param context 消息信息
 * @param msg 消息内容
 */
void CustomOutputMessage(QtMsgType type,
                         const QMessageLogContext &,
                         const QString &msg) {
    QString message_type;
    switch(type) {
    case QtInfoMsg:
        message_type = QString("Info:");
        break;
    case QtDebugMsg:
        message_type = QString("Debug:");
        break;
    case QtWarningMsg:
        message_type = QString("Warning:");
        break;
    case QtCriticalMsg:
        message_type = QString("Critical:");
        break;
    case QtFatalMsg:
        message_type = QString("Fatal:");
    }
    QString current_date = QDateTime::currentDateTime().
                           toString("yyyy-MM-dd hh:mm:ss");
    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QString message = QString("%1 %2 (%3)\r\n").arg(message_type).
                      arg(msg).arg(current_date);
    file.write(message.toLatin1());
    file.close();
    if(type == QtFatalMsg) {
        QMessageBox::critical(nullptr, "致命错误",
                              QString("%2\r\n%1\r\n请解决问题后重新启动程序\r\n"
                                      "问题反馈：techieliang@qq.com")
                              .arg(msg)
                              .arg(current_date));
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //日志功能
#ifndef QT_DEBUG
    qInstallMessageHandler(CustomOutputMessage);
#endif
    //启动主窗口
    MainWindow w;
    w.show();

    return a.exec();
}

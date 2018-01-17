#include "main_window.h"
#include <QApplication>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
/**
 * @brief CustomOutputMessage
 * @param type 消息类型
 * @param context 消息信息
 * @param msg 消息内容
 */
void CustomOutputMessage(QtMsgType type,
                         const QMessageLogContext &context,
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
                                      "问题反馈：techieliang@qq.com").
                              arg(msg).arg(current_date));
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //日志功能
#ifndef QT_DEBUG
    qInstallMessageHandler(CustomOutputMessage);
#endif
    MainWindow w;
    w.show();

    return a.exec();
}

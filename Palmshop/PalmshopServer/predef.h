#ifndef PREDEF_H
#define PREDEF_H
#include <QObject>
#include <QString>
#ifdef Q_OS_WIN
const static QString kSystemConfigFilePath = "config.ini";
#endif //Q_OS_WIN
#ifdef Q_OS_LINUX
const static QString kSystemConfigFilePath = "config.ini";
#endif //Q_OS_LINUX
#ifdef Q_OS_ANDROID
const static QString kSystemConfigFilePath = "config.ini";
#endif //Q_OS_ANDROID
#endif // PREDEF_H

#ifndef PREDEF_H
#define PREDEF_H
#include <QObject>
#include <QString>
#ifdef Q_OS_WIN

#endif //Q_OS_WIN
#ifdef Q_OS_LINUX

#endif //Q_OS_LINUX
#ifdef Q_OS_ANDROID

#endif //Q_OS_ANDROID
const static QString kProgramDeveloperName = "TechieLiang";///开发者名
const static QString kProgramName = "Palmshop";///程序名
const static QString kSqlConnectionName = "PalmshopSqlConnection";///sql连接标识名
const static QString kSqlDbType = "QMYSQL";///sql类型名，用于QSqlDatabase
#endif // PREDEF_H

#-------------------------------------------------
#
# Project created by QtCreator 2017-12-21T21:49:22
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PalmshopServer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        main_window.cpp \
    system_config_manager.cpp \
    data_base/restaurant_db_initialization.cpp \
    user_interface/system_config_setting_dialog.cpp \
    data_base/restaurant_sql_command.cpp \
    user_interface/login_dialog.cpp \
    user_interface/initialization_dialog.cpp \
    user_interface/restaurant_checkstand_form.cpp \
    user_interface/restaurant/restaurant_checkstand_title_bar.cpp

HEADERS += \
        main_window.h \
    system_config_manager.h \
    predef.h \
    data_base/db_initialization_interface.h \
    data_base/restaurant_db_initialization.h \
    user_interface/system_config_setting_dialog.h \
    data_base/restaurant_sql_command.h \
    user_interface/login_dialog.h \
    user_interface/initialization_dialog.h \
    user_interface/restaurant_checkstand_form.h \
    user_interface/restaurant/restaurant_checkstand_title_bar.h

FORMS += \
        main_window.ui \
    user_interface/system_config_setting_dialog.ui \
    user_interface/login_dialog.ui \
    user_interface/initialization_dialog.ui \
    user_interface/restaurant_checkstand_form.ui

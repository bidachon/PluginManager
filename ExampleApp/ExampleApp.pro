#-------------------------------------------------
#
# Project created by QtCreator 2015-03-11T09:34:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ExampleApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


DISTFILES += \
    pluginlist.json


INCLUDEPATH += $$PWD/../PluginManager


unix|win32: LIBS += -L$$OUT_PWD/../PluginManager/ -lPluginManager

INCLUDEPATH += $$PWD/../PluginManager
DEPENDPATH += $$PWD/../PluginManager

win32:!win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../PluginManager/PluginManager.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$OUT_PWD/../PluginManager/libPluginManager.a

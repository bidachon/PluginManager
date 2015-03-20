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


INCLUDEPATH += $$ROOTSRCDIR/PluginManager


unix|win32: LIBS += -L$$ROOTBUILDDIR/PluginManager/ -lPluginManager

DEPENDPATH += $$ROOTSRCDIR/PluginManager

win32:!win32-g++: PRE_TARGETDEPS += $$ROOTBUILDDIR/PluginManager/PluginManager.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$ROOTBUILDDIR/PluginManager/libPluginManager.a

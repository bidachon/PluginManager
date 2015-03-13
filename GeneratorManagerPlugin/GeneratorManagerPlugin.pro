#-------------------------------------------------
#
# Project created by QtCreator 2015-03-13T09:54:53
#
#-------------------------------------------------

QT       += widgets core

TARGET = GeneratorManagerPlugin
CONFIG += plugin
TEMPLATE = lib

DEFINES += GENERATORMANAGERPLUGIN_LIBRARY

SOURCES += generatormanagerplugin.cpp \
    generatormanagerimpl.cpp

HEADERS += generatormanagerplugin.h\
        generatormanagerplugin_global.h \
    generatormanagerimpl.h

INCLUDEPATH += $$PWD/../PluginManager/

DESTDIR  = ../plugins

unix {
    target.path = /usr/lib
    INSTALLS += target
}

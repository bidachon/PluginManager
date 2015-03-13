#-------------------------------------------------
#
# Project created by QtCreator 2015-03-11T09:42:15
#
#-------------------------------------------------

QT       -= gui
QT += core xml

TARGET = PluginManager
CONFIG += static
TEMPLATE = lib

DEFINES += PLUGINMANAGER_LIBRARY


SOURCES += pluginmanager.cpp \
    pluginconfigurationparser.cpp

HEADERS += pluginmanager.h\
        pluginmanager_global.h \
    Interfaces/inumbergenerator.h \
    stdpluginlib.h \
    Interfaces/ipluginlib.h \
    Interfaces/iplugininterface.h \
    extension.h \
    interfaceid.h \
    pluginconfigurationparser.h \
    dependency.h \
    Interfaces/igeneratormanager.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

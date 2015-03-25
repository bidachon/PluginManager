//
// Created by nicolasrobert on 3/24/15.
//

#ifndef _PLUGINMANAGER_DUMMYGENERATORPLUGIN_H_
#define _PLUGINMANAGER_DUMMYGENERATORPLUGIN_H_

#include "DummyGenerator.h"
#include <stdpluginlib.h>
#include <QObject>
#include <QSharedPointer>
#include <QtCore/qglobal.h>

class Q_DECL_IMPORT DummyGeneratorPlugin :  public QObject, public plugin::StdPluginLib
{
Q_OBJECT
        Q_PLUGIN_METADATA(IID "Dummy2GeneratorPlugin")
Q_INTERFACES(plugin::interfaces::IPluginLib)


public:
DummyGeneratorPlugin();
~DummyGeneratorPlugin();

virtual void connectExtension(QSharedPointer<plugin::interfaces::IPluginInterface> iface);

private:
QSharedPointer<DummyGeneratorImpl> _numberGen;
};


#endif //_PLUGINMANAGER_DUMMYGENERATORPLUGIN_H_

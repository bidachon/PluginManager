#ifndef GENERATORMANAGERPLUGIN_H
#define GENERATORMANAGERPLUGIN_H
#include <stdpluginlib.h>
#include "generatormanagerplugin_global.h"
#include "generatormanagerimpl.h"

class GENERATORMANAGERPLUGINSHARED_EXPORT GeneratorManagerPlugin: public QObject, public plugin::StdPluginLib
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "IPluginLib")
    Q_INTERFACES(plugin::interfaces::IPluginLib)
public:
    GeneratorManagerPlugin();
    ~GeneratorManagerPlugin();
    virtual void connectExtension(QSharedPointer<plugin::interfaces::IPluginInterface> iface);
};

#endif // GENERATORMANAGERPLUGIN_H


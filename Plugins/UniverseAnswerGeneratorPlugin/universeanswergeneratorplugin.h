#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H

#include <stdpluginlib.h>
#include "Interfaces/ipluginlib.h"

#include "universeanswergenerator_global.h"
#include <QObject>
#include <universeanswergeneratorimpl.h>
#include <QSharedPointer>

class NUMBERGENERATORSHARED_EXPORT NumberGeneratorPlugin : public QObject,  public plugin::StdPluginLib
{
    Q_OBJECT
    Q_INTERFACES(plugin::interfaces::IPluginLib)
    Q_PLUGIN_METADATA(IID "IPluginLib")

public:
    NumberGeneratorPlugin();
    ~NumberGeneratorPlugin();

    virtual void connectExtension(QSharedPointer<plugin::interfaces::IPluginInterface> iface);

private:
    QSharedPointer<NumberGeneratorImpl> _numberGen;
};

#endif // NUMBERGENERATOR_H

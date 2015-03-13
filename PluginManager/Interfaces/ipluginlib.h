#ifndef IPLUGINLIB
#define IPLUGINLIB

#include <QString>
#include <QStringList>
#include <QSharedPointer>
#include <Interfaces/iplugininterface.h>
#include <extension.h>
#include <dependency.h>

namespace plugin {
namespace interfaces {

class IPluginLib
{

public:
    virtual ~IPluginLib() {}

    /**
     * Returns a list of extensions
     */
    virtual const std::list<Extension *> &extensions() const = 0;

    /**
     * Returns a list of extension points
     */
    virtual const std::list<Dependency *> &dependencies() const = 0;

    /**
     * Adds an extension interface pointer  to an Dependency.
     *
     * @param iface the interface pointer for the extension that will be
     *              connected to this extension point
     */
    virtual void connectExtension(QSharedPointer<IPluginInterface> iface) = 0;

    virtual const Extension* getExtension(const InterfaceId &id) const = 0;
};



}
}


Q_DECLARE_INTERFACE(plugin::interfaces::IPluginLib, "IPluginLib")

#endif // IPLUGINLIB


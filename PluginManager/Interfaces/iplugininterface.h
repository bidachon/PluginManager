#ifndef IBASEINTERFACE_H
#define IBASEINTERFACE_H

#include <QString>
#include <QObject>
#include <interfaceid.h>

namespace plugin {
namespace interfaces {

class IPluginInterface
{
public:
    virtual ~IPluginInterface() {}

    virtual InterfaceId id() const = 0;

    virtual bool rttiMatch(const char *str) const = 0;

};

}
}

Q_DECLARE_INTERFACE(plugin::interfaces::IPluginInterface, "IPluginInterface")



#endif // IBASEINTERFACE_H


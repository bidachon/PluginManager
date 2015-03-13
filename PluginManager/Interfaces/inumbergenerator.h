#ifndef INUMBERGENERATOR
#define INUMBERGENERATOR

#include <Interfaces/iplugininterface.h>
#include <QObject>

namespace plugin {
namespace interfaces {


class INumberGenerator: public IPluginInterface
{

public:
    virtual ~INumberGenerator() {}

    virtual int number() = 0;

    virtual InterfaceId id() const
    {
        return InterfaceId("INumberGenerator");
    }

    virtual bool rttiMatch(const char *str) const
    {
      return (::strcmp(id().name().c_str(), str) == 0);
    }

};

}
}


Q_DECLARE_INTERFACE(plugin::interfaces::INumberGenerator, "INumberGenerator")

#endif // INUMBERGENERATOR

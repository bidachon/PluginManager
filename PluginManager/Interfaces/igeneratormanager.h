#ifndef GENERATORMANAGER
#define GENERATORMANAGER

#include <QtWidgets/QWidget>

namespace plugin {
namespace interfaces {


class IGeneratorManager: public IPluginInterface
{
public:
    virtual ~IGeneratorManager() {}

    virtual QWidget* widget() = 0;

    virtual InterfaceId id() const
    {
        return InterfaceId("IGeneratorManager");
    }

    virtual bool rttiMatch(const char *str) const
    {
      return (::strcmp(id().name().c_str(), str) == 0);
    }
};

}
}


#endif // GENERATORMANAGER


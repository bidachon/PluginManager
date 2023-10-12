#ifndef GENERATORMANAGERPLUGIN_H
#define GENERATORMANAGERPLUGIN_H
#include "StdPluginLib.h"
#include "GeneratorManagerImpl.h"

class GeneratorManagerPlugin : public plugin::StdPluginLib
{
public:
    GeneratorManagerPlugin();

    void ConnectExtension(plugin::ExtensionPtr iface) override;
private:
    std::shared_ptr<GeneratorManagerImpl> m_generatorManager;
};

#endif // GENERATORMANAGERPLUGIN_H

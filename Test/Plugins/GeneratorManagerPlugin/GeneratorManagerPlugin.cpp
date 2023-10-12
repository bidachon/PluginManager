#include "GeneratorManagerPlugin.h"

#include "Interfaces/INumberGenerator.h"

#include <memory>

GeneratorManagerPlugin::GeneratorManagerPlugin():
    m_generatorManager(AddExtension<GeneratorManagerImpl>())

{
    AddDependency<plugin::interfaces::INumberGenerator>(0, 2);
}

void GeneratorManagerPlugin::ConnectExtension(plugin::ExtensionPtr iface)
{
    using namespace plugin::interfaces;
    if(iface->IsAn<INumberGenerator>())
    {
        auto const nbGen = std::static_pointer_cast<plugin::interfaces::INumberGenerator>(iface);
        m_generatorManager->addNumberGenerator(nbGen);
        return;
    }

    throw std::logic_error{"Did you add a new dependency and not handle it?"};
}

CREATE_PLUGIN_INSTANCE(GeneratorManagerPlugin);


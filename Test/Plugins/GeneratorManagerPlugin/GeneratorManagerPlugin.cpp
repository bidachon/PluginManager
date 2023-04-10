#include "GeneratorManagerPlugin.h"
#include "Common/CommonMacros.h"


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
        auto const nbGen = polymorphic_downcast<plugin::interfaces::INumberGenerator>(iface);
        m_generatorManager->addNumberGenerator(nbGen);
        return;
    }

    assert(!"Did you add a new dependency and not handle it?");
}

CREATE_PLUGIN_INSTANCE(GeneratorManagerPlugin);


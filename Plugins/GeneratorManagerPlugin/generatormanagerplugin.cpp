#include "generatormanagerplugin.h"

static QSharedPointer<GeneratorManagerImpl> generatorManager()
{
  static QSharedPointer<GeneratorManagerImpl> theGeneratorManager;
    if ( !theGeneratorManager ) {
      theGeneratorManager.reset( new GeneratorManagerImpl() );
    }

  return theGeneratorManager;
}

GeneratorManagerPlugin::GeneratorManagerPlugin()
{
    m_extensions.push_back(new plugin::Extension(generatorManager()));
    m_dependencies.push_back(new plugin::Dependency(0,plugin::DEPENDENCY_UNLIMITED,plugin::InterfaceId("INumberGenerator")));
}

GeneratorManagerPlugin::~GeneratorManagerPlugin()
{
}


void GeneratorManagerPlugin::connectExtension(QSharedPointer<plugin::interfaces::IPluginInterface> iface)
{
    //cast away my friend!
    QSharedPointer<plugin::interfaces::INumberGenerator> nbGen = qSharedPointerCast<plugin::interfaces::INumberGenerator>(iface);
    generatorManager()->addNumberGenerator(nbGen);
}


//
// Created by nicolasrobert on 3/24/15.
//

#include "DummyGeneratorPlugin.h"

static QSharedPointer<DummyGeneratorImpl> numberGenerator()
{
    static QSharedPointer<DummyGeneratorImpl> theNumberGenerator;
    if ( !theNumberGenerator ) {
        theNumberGenerator.reset( new DummyGeneratorImpl() );
    }

    return theNumberGenerator;
}

DummyGeneratorPlugin::DummyGeneratorPlugin()
{
    m_extensions.push_back(new plugin::Extension(numberGenerator()));
    m_dependencies.push_back(new plugin::Dependency(2,2,plugin::InterfaceId("INumberGenerator")));

}

DummyGeneratorPlugin::~DummyGeneratorPlugin()
{
}

void DummyGeneratorPlugin::connectExtension(QSharedPointer<plugin::interfaces::IPluginInterface> iface)
{

}
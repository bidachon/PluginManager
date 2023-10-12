//
// Created by nicolasrobert on 3/24/15.
//

#include "DummyGeneratorPlugin.h"


DummyGeneratorPlugin::DummyGeneratorPlugin():
    m_dummyGenerator(AddExtension<DummyGeneratorImpl>())
{
    AddDependency<plugin::interfaces::INumberGenerator>(2,2);
}

CREATE_PLUGIN_INSTANCE(DummyGeneratorPlugin);


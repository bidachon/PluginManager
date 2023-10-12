//
// Created by nicolasrobert on 3/24/15.
//

#include "DummyGeneratorPlugin.h"

#include "DummyGenerator.h"


DummyGeneratorPlugin::DummyGeneratorPlugin():
    m_dummyGenerator(AddExtension<DummyGeneratorImpl>())
{

}

CREATE_PLUGIN_INSTANCE(DummyGeneratorPlugin);


#include "StatefulTestPlugin.h"

StatefulTestPlugin::StatefulTestPlugin():
    m_testClass(AddExtension<StatefulTestClass>())
{
}

CREATE_PLUGIN_INSTANCE(StatefulTestPlugin);


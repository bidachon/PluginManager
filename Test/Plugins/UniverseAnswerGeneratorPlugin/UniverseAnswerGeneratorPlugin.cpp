#include "UniverseAnswerGeneratorPlugin.h"


NumberGeneratorPlugin::NumberGeneratorPlugin():
    m_numberGenerator(AddExtension<NumberGeneratorImpl>())
{

}

CREATE_PLUGIN_INSTANCE(NumberGeneratorPlugin);


#ifndef UNIVERSEANSWERGENERATORPLUGIN_H_B95017A0_691A_4800_91C7_B6B3A026520F
#define UNIVERSEANSWERGENERATORPLUGIN_H_B95017A0_691A_4800_91C7_B6B3A026520F

#include "UniverseAnswerGeneratorImpl.h"

#include "StdPluginLib.h"
#include "IPluginLib.h"

class NumberGeneratorPlugin : public plugin::StdPluginLib
{
public:
    NumberGeneratorPlugin();

private:
    std::shared_ptr<NumberGeneratorImpl> m_numberGenerator;
};

#endif // UNIVERSEANSWERGENERATORPLUGIN_H_B95017A0_691A_4800_91C7_B6B3A026520F


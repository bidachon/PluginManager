#ifndef DUMMYGENERATORPLUGIN_H_934BEDA3_50A7_4C6A_8A6F_DECBC0C2FA13
#define DUMMYGENERATORPLUGIN_H_934BEDA3_50A7_4C6A_8A6F_DECBC0C2FA13
// Created by nicolasrobert on 3/24/15.

#include "DummyGenerator.h"
#include "StdPluginLib.h"

class DummyGeneratorPlugin : public plugin::StdPluginLib
{
public:
    DummyGeneratorPlugin();

private:
    std::shared_ptr<DummyGeneratorImpl> m_dummyGenerator;
};

#endif // DUMMYGENERATORPLUGIN_H_934BEDA3_50A7_4C6A_8A6F_DECBC0C2FA13


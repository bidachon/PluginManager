#ifndef STATEFULTESTPLUGIN_H_E0717FE2_839D_48E6_ABC2_AF9A6DDF6C6F
#define STATEFULTESTPLUGIN_H_E0717FE2_839D_48E6_ABC2_AF9A6DDF6C6F

#include "StatefulTestClass.h"
#include "StdPluginLib.h"

class StatefulTestPlugin : public plugin::StdPluginLib
{
public:
    StatefulTestPlugin();

private:
    std::shared_ptr<StatefulTestClass> const m_testClass;
};


#endif // STATEFULTESTPLUGIN_H_E0717FE2_839D_48E6_ABC2_AF9A6DDF6C6F


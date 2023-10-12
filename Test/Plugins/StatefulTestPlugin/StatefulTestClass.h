#ifndef STATEFULTESTCLASS_H_CADC4880_53D0_4045_975E_94E696E08996
#define STATEFULTESTCLASS_H_CADC4880_53D0_4045_975E_94E696E08996

#include "Interfaces/IStatefulPluginInterface.h"

class StatefulTestClass : public plugin::interfaces::IStatefulPluginInterface
{
public:
    int GetNumber() const override;
    void SetNumber(int value) override;

private:
    int m_number { IStatefulPluginInterface::DEFAULT_VALUE };
};

#endif // STATEFULTESTCLASS_H_CADC4880_53D0_4045_975E_94E696E08996


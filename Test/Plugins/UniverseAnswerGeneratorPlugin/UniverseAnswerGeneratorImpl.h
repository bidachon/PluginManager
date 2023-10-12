#ifndef NUMBERGENERATORIMPL_H
#define NUMBERGENERATORIMPL_H

#include "Interfaces/INumberGenerator.h"

class NumberGeneratorImpl : public plugin::interfaces::INumberGenerator
{
public:
    NumberGeneratorImpl();
    ~NumberGeneratorImpl();

    int GetNumber() override;
};

#endif // NUMBERGENERATORIMPL_H

#ifndef NUMBERGENERATORIMPL_H
#define NUMBERGENERATORIMPL_H

#include "Interfaces/inumbergenerator.h"

class NumberGeneratorImpl: public plugin::interfaces::INumberGenerator
{
public:
    NumberGeneratorImpl();
    ~NumberGeneratorImpl();

    int number();

};

#endif // NUMBERGENERATORIMPL_H

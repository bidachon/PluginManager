#ifndef DUMMYGENERATOR_H_C53522B5_A00E_422E_A560_58349564D734
#define DUMMYGENERATOR_H_C53522B5_A00E_422E_A560_58349564D734
// Created by nicolasrobert on 3/24/15.

#include "Interfaces/INumberGenerator.h"

class DummyGeneratorImpl : public plugin::interfaces::INumberGenerator
{
public:
    int GetNumber() override;
};

#endif // DUMMYGENERATOR_H_C53522B5_A00E_422E_A560_58349564D734


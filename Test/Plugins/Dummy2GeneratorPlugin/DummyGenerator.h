#ifndef DUMMYGENERATOR_H_BF71F6F1_2814_405F_A304_7E65C7656442
#define DUMMYGENERATOR_H_BF71F6F1_2814_405F_A304_7E65C7656442
// Created by nicolasrobert on 3/24/15.

#include "Interfaces/INumberGenerator.h"

class DummyGeneratorImpl : public plugin::interfaces::INumberGenerator
{
public:
    int GetNumber() override;
};

#endif // DUMMYGENERATOR_H_BF71F6F1_2814_405F_A304_7E65C7656442


//
// Created by nicolasrobert on 3/24/15.
//

#ifndef _PLUGINMANAGER_DUMMYGENERATOR_H_
#define _PLUGINMANAGER_DUMMYGENERATOR_H_

#include "Interfaces/inumbergenerator.h"

class DummyGeneratorImpl: public plugin::interfaces::INumberGenerator
{
public:
    DummyGeneratorImpl();
    ~DummyGeneratorImpl();

    int number();

};

#endif //_PLUGINMANAGER_DUMMYGENERATOR_H_

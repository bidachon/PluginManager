#include "StatefulTestClass.h"

int StatefulTestClass::GetNumber() const
{
    return m_number;
}


void StatefulTestClass::SetNumber(int value)
{
    m_number = value;
}



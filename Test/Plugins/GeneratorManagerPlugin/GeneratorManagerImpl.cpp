#include "GeneratorManagerImpl.h"
#include <iostream>

GeneratorManagerImpl::GeneratorManagerImpl()
{
    generateNumbers();
}

void GeneratorManagerImpl::generateNumbers()
{
    for (const auto &ng : m_gens) {
        std::cout << ng->GetNumber() << std::endl;
    }
}

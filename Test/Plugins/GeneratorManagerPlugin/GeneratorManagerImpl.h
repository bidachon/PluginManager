#ifndef GENERATORMANAGERIMPL_H
#define GENERATORMANAGERIMPL_H

#include "Interfaces/INumberGenerator.h"
#include "Interfaces/IGeneratorManager.h"
#include <list>

class GeneratorManagerImpl : public plugin::interfaces::IGeneratorManager
{
public:
    GeneratorManagerImpl();

    void addNumberGenerator(std::shared_ptr<plugin::interfaces::INumberGenerator> gen)
    {
        m_gens.push_back(gen);
    }

private:
    void generateNumbers();

private:
    std::list<std::shared_ptr<plugin::interfaces::INumberGenerator> > m_gens;
};

#endif // GENERATORMANAGERIMPL_H

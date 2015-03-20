#ifndef GENERATORMANAGERIMPL_H
#define GENERATORMANAGERIMPL_H
#include <QTextEdit>
#include <Interfaces/inumbergenerator.h>
#include <Interfaces/igeneratormanager.h>

class GeneratorManagerImpl: public QObject, public plugin::interfaces::IGeneratorManager
{
    Q_OBJECT
public:
    GeneratorManagerImpl();
    ~GeneratorManagerImpl();
    QWidget* widget();

    void addNumberGenerator(QSharedPointer<plugin::interfaces::INumberGenerator> gen)
    {
        m_gens.append(gen);
    }

public slots:
    void generateNumbers();

private:
    QWidget *m_root;
    QTextEdit *m_textEdit;
    QList< QSharedPointer< plugin::interfaces::INumberGenerator> > m_gens;
};

#endif // GENERATORMANAGERIMPL_H

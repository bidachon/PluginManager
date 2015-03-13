#include "generatormanagerimpl.h"
#include <QtWidgets>
#include <QObject>

GeneratorManagerImpl::GeneratorManagerImpl()
{
    m_root = new QWidget();
    QVBoxLayout *vl =new QVBoxLayout(m_root);
    QPushButton *genBtn = new QPushButton(m_root);
    connect(genBtn,SIGNAL(clicked()),this,SLOT(generateNumbers()));
    genBtn->setText("Generate numbers");
    m_textEdit = new QTextEdit(m_root);
    vl->addWidget(genBtn);
    vl->addWidget(m_textEdit);
    m_root->setLayout(vl);

}

GeneratorManagerImpl::~GeneratorManagerImpl()
{

}

void GeneratorManagerImpl::generateNumbers()
{
    qDebug() << "GeneratorManagerImpl::generateNumbers()";
    foreach(QSharedPointer< plugin::interfaces::INumberGenerator> ng, m_gens)
    {
        m_textEdit->append(QString::number(ng->number()));
    }


}

QWidget* GeneratorManagerImpl::widget()
{
    return m_root;
}


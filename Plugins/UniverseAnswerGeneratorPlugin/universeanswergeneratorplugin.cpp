#include "universeanswergeneratorplugin.h"
#include <QDebug>

static QSharedPointer<NumberGeneratorImpl> numberGenerator()
{
  static QSharedPointer<NumberGeneratorImpl> theNumberGenerator;
    if ( !theNumberGenerator ) {
      theNumberGenerator.reset( new NumberGeneratorImpl() );
    }

  return theNumberGenerator;
}

NumberGeneratorPlugin::NumberGeneratorPlugin()
{
    qDebug() << "NumberGeneratorPlugin Constructor called";
    m_extensions.push_back(new plugin::Extension(numberGenerator()));
}

NumberGeneratorPlugin::~NumberGeneratorPlugin()
{
}

 void NumberGeneratorPlugin::connectExtension(QSharedPointer<plugin::interfaces::IPluginInterface> iface)
{

}

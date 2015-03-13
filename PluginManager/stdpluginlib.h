#ifndef STDPLUGINLIB_H
#define STDPLUGINLIB_H

#include <string>
#include <list>
#include <assert.h>
#include <QDebug>
#include <Interfaces/ipluginlib.h>

namespace plugin {


class StdPluginLib: public interfaces::IPluginLib
{
public:
    StdPluginLib(){}

    // Virtual Destructor
    virtual ~StdPluginLib()
    {
      for ( std::list<Extension *>::iterator it = m_extensions.begin(); it != m_extensions.end(); ++it)
        delete (*it);
      for ( std::list<Dependency *>::iterator it = m_dependencies.begin(); it != m_dependencies.end(); ++it)
        delete (*it);
    }

    void connectExtension(QSharedPointer<plugin::interfaces::IPluginInterface> iface)
    {
      assert(0);
    }


    const std::list<Extension *> &extensions() const
    {
      return m_extensions;
    }

    const std::list<Dependency *> &dependencies() const
    {
      return m_dependencies;
    }

    Extension* getExtension(const plugin::InterfaceId& extIfaceName) const
    {
      for (std::list<Extension*>::const_iterator it = m_extensions.begin(); it!= m_extensions.end(); ++it)
      {
        Extension* ext = *it;
        qDebug() << "Extension: " << ext->interface()->id().name().c_str();
        if ( ext->interface()->rttiMatch( extIfaceName.name().c_str() ) )
        {
          return ext;
        }
      }
      return NULL;
    }

protected:
  std::list<Extension *> m_extensions;
  std::list<Dependency *> m_dependencies;
};

/**
 * Standard Implementation class for IPluginLib objects
 */

}

#endif // STDPLUGINLIB_H

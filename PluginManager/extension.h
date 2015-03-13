#ifndef EXTENSION_H
#define EXTENSION_H

#include <QSharedPointer>

namespace plugin {


namespace interfaces {
// Forward decl
class IPluginInterface;
}


/**
 * Defines a description of a plugin extension.  An extension provides an
 * interface that is connected to an extension point.
 */
class Extension
{
public:



  /**
  * Constructor for an Extension that is initialized with an interface.
  *
  * @param interface the interface that the extension provides. Note that
  * this reference is stored and used and as such, the parent must be
  * responsible for managing the lifetime of this interface in a way that
  * does not corrupt this object.
  */
  Extension(QSharedPointer<interfaces::IPluginInterface> interface)
    :
    m_interface(interface)
  {
  }




  /**
   * Returns a reference to the interface
   */
  QSharedPointer<interfaces::IPluginInterface> interface() const
  {
    return m_interface;
  }


protected:



  /**
   * the plugin interface pointer
   */
  QSharedPointer<interfaces::IPluginInterface> m_interface;
};

}

#endif // EXTENSION_H


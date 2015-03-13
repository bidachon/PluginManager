#ifndef DEPENDENCY_H
#define DEPENDENCY_H


#include <limits.h>

#include <string>

#include "InterfaceId.h"

namespace plugin {

const int DEPENDENCY_UNLIMITED = INT_MAX;

/**
 * Defines a description of a plugin extension point.  An extension point
 * defines an interface that is needed (possibly optional) interface that is
 * connected to an extension.
 */
class Dependency
{
public:

  /**
   * Constructor initializes an Extension Point from the constructor
   * argument.
   *
   * @param min the minimum number of extensions that must be connected to the
   *            extension point
   * @param max the maximum number of extensions that may be connected to
   *            extension point
   * @param interfaceId the id of the interface associated with the
   *            extension point
   */
  Dependency(int min, int max, const InterfaceId& id)
      :

  m_min(min),
  m_max(max),
  m_id(id)
  {
  }

  /**
   * Convenience constructor which initializes an Extension Point from the constructor
   * arguments.
   *
   * @param min the minimum number of extensions that must be connected to the
   *            extension point
   * @param max the maximum number of extensions that may be connected to
   *            extension point
   * @param ifaceRtti the rtti of the interface associated with the
   *            extension point
   */
  Dependency(int min, int max, const char * ifaceRtti)
      :

  m_min(min),
  m_max(max),
  m_id(ifaceRtti)
  {
  }

  /**
   * Destructor
   */
  ~Dependency(void)
  {
  }


  /**
   * Returns the minimum number of extensions that must be connected to this
   * extension point
   */
  int minExt() const
  {
    return m_min;
  }

  /**
   * Returns the maximum number of extensions that may be connected to this
   * extension point
   */
  int maxExt() const
  {
    return m_max;
  }

  /**
   * Returns the interface name associated with this extension point
   */
  const InterfaceId& interfaceId() const
  {
    return m_id;
  }

  /**
   * Compares one Extension Point to another
   *
   * @param other the other extension point to compare to
   */
  bool operator==(const Dependency &other) const
  {
    return
      m_min == other.m_min &&
      m_max == other.m_max &&
      m_id == other.m_id;
  }


protected:


  /**
   * The minimum number of connected extensions required
   */
  int m_min;

  /**
   * The maximum number of connecte extensions allowed
   */
  int m_max;

  /**
   * The ID of the interface associated with this extension point
   */
  InterfaceId m_id;
};

}

#endif // DEPENDENCY_H


#ifndef INTERFACEID
#define INTERFACEID

namespace plugin {

/**
 * Provides a unique identifier for interface names. The current
 * implementation is based on a simple string.
 */
class InterfaceId
{
public:

   /**
   * Constructor
   */
  InterfaceId(const std::string& name)
    : m_name(name)
  {
  }

  /**
   * Get the name of the interface id
   */
  const std::string &name() const
  {
    return m_name;
  }

  bool isValid()
  {
    //Only requirement for interface names currently is that it is non-zero length;
    return m_name.length() > 0;
  }




 /**
  * Compares one id to another for an exact match
  *
  * @param other the other id to compare to
  */
  bool operator==(const InterfaceId &other) const
  {
  return m_name == other.m_name;
  }

protected:

  /**
   * The string  associated with the id
   */
  const std::string m_name;


private:


  /**
  * Compares one id to another
  *
  * @param other the other id to compare to
  */
  bool operator!=(const InterfaceId &other) const
  {
    return m_name != other.m_name;
  }


};

}

#endif // INTERFACEID


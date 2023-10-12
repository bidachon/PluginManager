#ifndef INTERFACEID_H_1C772332_4C69_4D22_B866_9E03B228FAA7
#define INTERFACEID_H_1C772332_4C69_4D22_B866_9E03B228FAA7

#include <stdexcept>
#include <string>

namespace plugin {

    /// \brief Provides a unique identifier for interface names.
    ///
    /// The current implementation is based on a simple string.
    ///
    class InterfaceId
    {
    public:
        /// Constructs an InterfaceId with the given name
        ///
        /// \param name The name of the interface, cannot be empty
        ///
        /// \throw std::runtime_error if an invalid name is provided
        ///
        /// \todo Come up w/ a better exception type for this. This should
        ///       never happen
        explicit InterfaceId(const std::string& name)
            : m_name(name)
        {
            if(name.empty())
            {
                throw std::runtime_error("Invalid IntefaceId, interface name cannot be empty.");
            }
        }

        /// Gets the name of the interface id
        std::string GetName() const { return m_name; }

    private:

        /// The string associated with the id
        const std::string m_name;
    };

    /// Compares one id to another for an exact match
    ///
    /// \param i1 an InterfaceId to compare
    /// \param i2 the other InterfaceId to compare
    ///
    inline bool operator==(InterfaceId const& i1, InterfaceId const& i2)
    {
        return i1.GetName() == i2.GetName();
    }

    /// Compares one id to another for an ordered sort
    ///
    /// \param i1 an InterfaceId to compare
    /// \param i2 the other InterfaceId to compare
    ///
    inline bool operator<(InterfaceId const& i1, InterfaceId const& i2)
    {
        return i1.GetName() < i2.GetName();
    }
}

#endif // INTERFACEID_H_1C772332_4C69_4D22_B866_9E03B228FAA7


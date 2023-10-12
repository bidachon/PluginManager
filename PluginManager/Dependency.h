#ifndef DEPENDENCY_H_C7CA5030_E489_43E8_BF22_BDA78F7901F7
#define DEPENDENCY_H_C7CA5030_E489_43E8_BF22_BDA78F7901F7

#include "InterfaceId.h"

#include <limits>


namespace plugin {

    const int DEPENDENCY_UNLIMITED = std::numeric_limits<int>::max();

    /// \brief  Defines a description of a plugin extension point.  
    ///
    /// An extension point defines an interface that is needed (possibly
    /// optional) interface that is connected to an extension.
    ///
    class Dependency
    {
    public:
        /// \brief Constructor, initializes an Extension Point
        ///
        /// \param min the minimum number of extensions that must be connected
        ///            to the extension point
        ///
        /// \param max the maximum number of extensions that may be connected to
        ///            extension point
        ///
        /// \param interfaceId the id of the interface associated with the
        ///                    extension point
        ///
        Dependency(int min, int max, const InterfaceId& id)
            : m_min(min)
            , m_max(max)
            , m_id(id)
        {
        }

        /**
         * Returns the minimum number of extensions that must be
         * connected to this extension point
         */
        int GetMinExt() const { return m_min; }

        /**
         * Returns the maximum number of extensions that may be
         * connected to this extension point
         */
        int GetMaxExt() const { return m_max; }

        /**
         * Returns the interface ID associated with this extension point
         */
        const InterfaceId& GetInterfaceId() const { return m_id; }

        /**
         * Compares one Extension Point to another
         *
         * @param other the other extension point to compare to
         */
        bool operator==(const Dependency& other) const
        {
            return m_min == other.m_min && m_max == other.m_max
                && m_id == other.m_id;
        }


    protected:
        /**
         * The minimum number of connected extensions required
         */
        int m_min;

        /**
         * The maximum number of connected extensions allowed
         */
        int m_max;

        /**
         * The ID of the interface associated with this extension point
         */
        InterfaceId m_id;
    };
}


#endif // DEPENDENCY_H_C7CA5030_E489_43E8_BF22_BDA78F7901F7


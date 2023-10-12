#ifndef IPLUGININTERFACE_H_0775622F_D57F_46C9_AB93_0A7609EC487B
#define IPLUGININTERFACE_H_0775622F_D57F_46C9_AB93_0A7609EC487B

#include <InterfaceId.h>

#include <cassert>
#include <memory>

namespace plugin {

    // Aliasing pointers to plugin interfaces as "ExtensionPtr"s.
    namespace interfaces { class IPluginInterface; }
    typedef std::shared_ptr<interfaces::IPluginInterface> ExtensionPtr;

    namespace interfaces {

        /// Common base class for all plugins
        class IPluginInterface
        {

        public:
            virtual ~IPluginInterface() = default;

            virtual InterfaceId GetId() const = 0;

            /// Checks whether the concrete interface is of the given type
            ///
            /// \param id The InterfaceId that you are looking for
            ///
            /// \note This function is virtual so that it can be overridden
            ///       with different checking behavior, but it seems unlikely
            ///       that would ever be necessary.
            virtual bool RttiMatch(InterfaceId id) const { return id == GetId(); }

            /// Helper method to check whether an interface is of a given type
            ///
            /// \tparam IFACETYPE The type of interface that you want to check
            ///                   to see if this one is
            ///
            /// \tparam OFTYPE (optional) Checks to see if it's also of this
            ///                derived type.
            ///
            /// \note In debug mode this helper functions checks both that if
            ///       the ID matches, the dynamic cast will succeed, and that
            ///       if it doesn't match, a dynamic cast will NOT succeed.
            ///
            /// Usage:
            ///                                                                       /code
            ///    void MyPlugin::ConnectExtension(plugin::ExtensionPtr iface)
            ///    {
            ///         if(iface->IsAn<ISomeDependency>()) {
            ///             auto const dep = polymorphic_cast<ISomeDependency>(iface);
            ///             m_someImpl->ConnectDependency(dep);
            ///             return;
            ///         }
            ///
            ///         assert(!"Did you add a dependency but forget to handle it?");
            ///    }
            ///                                                                       /endcode
            ///
            template<typename IFACETYPE, typename OFTYPE = IFACETYPE>
                bool IsAn() const
                {
                    bool const match = ( IFACETYPE::GetInterfaceId() == GetId() );

                    assert( (match &&  dynamic_cast<IFACETYPE const*>(this)) ||
                            (!match && !dynamic_cast<IFACETYPE const*>(this)) );

                    return match && dynamic_cast<OFTYPE const*>(this);
                }
        };
    }
}

#endif // IPLUGININTERFACE_H_0775622F_D57F_46C9_AB93_0A7609EC487B

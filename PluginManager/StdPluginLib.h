#ifndef STDPLUGINLIB_H
#define STDPLUGINLIB_H

#include "Dependency.h"
#include "IPluginLib.h"
#include "IPluginInterface.h"

#include <vector>

namespace plugin {

    class StdPluginLib : public interfaces::IPluginLib
    {
    public:
        std::vector<ExtensionPtr> GetExtensions() const override { return m_extensions; }
        std::vector<std::shared_ptr<Dependency>> GetDependencies() const override { return m_dependencies; }

        bool HasExtension(const plugin::InterfaceId& interface) const override
        {
            for(auto const& extension : m_extensions) {
                if(extension->RttiMatch(interface)) {
                    return true;
                }
            }

            return false;
        }


        // PLUGIN MANAGER REVIEW:  The way this is written, it seems that the
        // PLUGIN MANAGER REVIEW:  desire is to allow plugin libraries to
        // PLUGIN MANAGER REVIEW:  provide multiple interfaces, e.g. IDoStuff,
        // PLUGIN MANAGER REVIEW:  and IDoOtherStuff.  That's potentially
        // PLUGIN MANAGER REVIEW:  useful, but this implementation limits each
        // PLUGIN MANAGER REVIEW:  plugin to only provide one of each
        // PLUGIN MANAGER REVIEW:  interface type per library, which seems
        // PLUGIN MANAGER REVIEW:  like an artificial limitation.  Wouldn't it
        // PLUGIN MANAGER REVIEW:  be better to get back a list of extensions
        // PLUGIN MANAGER REVIEW:  of that type?
        // PLUGIN MANAGER REVIEW:
        // PLUGIN MANAGER REVIEW:  Note that GetExtensions returns the whole
        // PLUGIN MANAGER REVIEW:  list w/o any such limitation, and plugin
        // PLUGIN MANAGER REVIEW:  manager adds them all to its internal map,
        // PLUGIN MANAGER REVIEW:  meaning that it's possible for plugin
        // PLUGIN MANAGER REVIEW:  manager to return them, but this class
        // PLUGIN MANAGER REVIEW:  cannot.

        ExtensionPtr const GetExtension(const plugin::InterfaceId& interface) const override
        {
            for(auto const& extension : m_extensions)
            {
                if(extension->RttiMatch(interface))
                {
                    return extension;
                }
            }

            return nullptr;
        }

        void ConnectExtension(plugin::ExtensionPtr /*iface*/) override {
            assert(!"Did you add a new dependency and forget to handle it?");
        }

    protected:
        /// Adds a dependency specification to the plugin
        ///
        /// Call this from the ctor of the derived plugin class to specify a dependency.
        ///
        /// \tparam IFACE the interface that your plugin depends on
        ///
        /// \param min The minimum number of instances required
        ///
        /// \param max The maximum number of instances that can exist
        ///
        /// \note See \ref plugin::Dependency::Dependency to understand the
        ///                                               min/max parameters
        ///
        template<typename IFACE>
        void AddDependency(int min, int max)
        {
            m_dependencies.push_back(std::make_shared<plugin::Dependency>(min, max, IFACE::GetInterfaceId()));
        }

        /// Adds an extension to the plugin
        ///
        /// Call this from the ctor of the derived plugin class to specify
        /// which concrete implementations the plugin provides
        ///
        /// \tparam IFACEIMPL The _concrete implementation_ of the interface
        ///                   provided by the plugin (must be default
        ///                   constructable by this class)
        ///
        template<typename IFACEIMPL>
            std::shared_ptr<IFACEIMPL> AddExtension()
        {
            // Using operator new instead of std::make_shared because
            // interface instances have private constructors, and a friend
            // relationship to allow this function to construct them.
            std::shared_ptr<IFACEIMPL> const instance { new IFACEIMPL };
            m_extensions.push_back(instance);
            return instance;
       }

    private:
        std::vector<ExtensionPtr>  m_extensions;
        std::vector<std::shared_ptr<Dependency>> m_dependencies;
    };
}


/// Macro for defining method for Plugin Manager to create the object instance
///
/// A single instance of this macro must exist within each plugin, usually
/// within the  Plugin*.cpp file.
///
/// Example:
///                                                           \code
///     CREATE_PLUGIN_INSTANCE(MyPlugin::PluginMyPlugin)
///                                                           \endcode
///
#define CREATE_PLUGIN_INSTANCE(TYPE) \
    extern "C" { \
    __attribute__((visibility("default"))) \
    plugin::interfaces::IPluginLib *plugin_creator() { \
        return new TYPE; }}


#endif // STDPLUGINLIB_H

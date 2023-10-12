#ifndef IPLUGINLIB
#define IPLUGINLIB

#include "IPluginInterface.h"

#include <vector>

namespace plugin {

    class Dependency;
    class InterfaceId;

    namespace interfaces {

        class IPluginLib
        {

        public:
            virtual ~IPluginLib() = default;

            /**
             * Provides an optional entry point for second phase initialization.
             * This method will be called after all plugins have been loaded and 
             * default-constructed, but before any dependencies are processed.
             * This can be helpful in situations where there are initialization
             * steps that for some reason cannot be done in a default constructor,
             * but need to be done before dependencies are processed.  Also, it
             * can be helpful for plugins that do not have any dependencies, but need
             * an extension point for a second phase initialization.
             */
            virtual void Initialize() {}

             /**
             * Provides an entry point for intialization AFTER dependencies are processed for loaded plugins.
             * Use this when initialization cannot be done in the constructor or by using the above method;
             * basically use this when the plugin's dependencies are needed for initialization. 
             */ 
            virtual void PostDependencyInit() {}

            /**
             * Returns a list of extensions
             */
            virtual std::vector<ExtensionPtr> GetExtensions() const = 0;

            virtual bool HasExtension(const plugin::InterfaceId& interface) const = 0;

            /**
             * Returns a list of extension points
             */
            virtual std::vector<std::shared_ptr<Dependency>> GetDependencies() const = 0;

            /**
             * Adds an extension interface pointer to an Dependency.
             *
             * @param iface the interface pointer for the extension that will be
             *              connected to this extension point
             */
            virtual void ConnectExtension(ExtensionPtr /*iface*/) {};

            virtual ExtensionPtr const GetExtension(const InterfaceId& id) const = 0;
        };
    }
}

#endif // IPLUGINLIB

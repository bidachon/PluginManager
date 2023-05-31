#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "IPluginInterface.h"
#include "IPluginLib.h"
#include "InterfaceId.h"

#include <map>
#include <string>
#include <vector>

#include <stdexcept>
#include <memory>

typedef plugin::interfaces::IPluginLib *(*creator_ptr)();

namespace plugin {

    class PluginManager;

    namespace Container
    {
        /// Constructs the plugin manager from a list of configuration files
        ///
        /// \param filenames Vector of fully qualified filenames of files
        ///                  containing the plugin configuration represented by
        ///                  this plugin manager.
        ///
        /// \throw PluginError if unable to parse config or load plugins
        ///
        /// \note if a previous configuration file has been loaded, the plugin
        ///       manager object is destroyed and a new instance is created.
        ///
        void LoadPluginConfigurationFiles(std::vector<std::string> filenames);

        /// Constructs the plugin manager with no plugins loaded.
        ///
        /// \note If a previous plugin manager has already been loaded,
        ///       the plugin manager object is destroyed and a new instance
        ///       is created.
        ///
        void LoadWithoutPlugins();

        /// Unloads the Plugin Manager object (for shutdown, unit tests, etc)
        ///
        /// \note Any plugins that were kept in a shared pointer will be kept alive
        ///
        void UnloadPluginManager();

        /// Gets the plugin manager instance
        ///
        /// \throw std::logic_error if there is no plugin manager loaded
        ///        (UnloadPluginManager has been called, 
        ///         LoadPluginConfigurationFile was not called, 
        ///         or loading failed)
        ///
        /// \return reference to a plugin manager instance
        ///
        plugin::PluginManager& GetPluginManager();

        /// Checks whether a plugin manager instance is loaded or not.
        ///
        /// \return true, if a plugin manager instance is loaded otherwise return false.
        ///
        bool Loaded();
    };

    namespace predicates {

        constexpr bool anyNumber(int)     { return true;   }

        template<int N>
        constexpr bool exactly(int n)     { return n == N; }

        template<int N>
        constexpr bool greaterThan(int n) { return n > N;  }

        template<int N>
        constexpr bool lessThan(int n)    { return n < N;  }

        // inclusive
        template<int M, int N>
        constexpr bool between(int n)     { return n >= M && n <= N; }
    }

    //======================================================================
    class PluginManager final
    {
    public:
        /// Constructor
        ///
        /// \param filenames List of plugin configuration files to load
        ///
        /// \throw PluginError if unable to parse config or load plugins
        ///
        PluginManager(std::vector<std::string> filenames);

        /// Constructor
        ///
        /// \note Used for explicitely empty containers
        ///
        PluginManager() = default;

        ~PluginManager();

        PluginManager(PluginManager const&) = delete;
        PluginManager& operator=(PluginManager const&) = delete;

        /// Instructs the PIM to fail hard at shutdown in debug mode if plugins remain cached
        ///
        /// \note This function has no effect on release runs, only debug runs
        ///
        void FailHardAtShutdownIfCachedPluginsRemain();

        /// Gets a list of interfaces with the given ID
        ///
        /// \tparam INTERFACE_TYPE The type of the abstract interface that the
        ///                        interface ID represents
        ///
        /// \tparam FILTERED_TYPE [optional] The types that you want to filter
        ///            for return.  For example, if you KNOW that the type that
        ///            you want is a procedure specific type (e.g. Bronch* only
        ///            works with dependency of type Bronch*), then you can ask
        ///            for it specifically by specifying the subclass (derived
        ///            type) here.  Another use is if all instances of an
        ///            interface have an intermediate class in their
        ///            inheritance heirarchy for some reason, such as
        ///            AbstractMessageHandler, which has template functions
        ///            that cannot be in IMessageHandler.  If not specified,
        ///            then all implementations of INTERFACE_TYPE are returned.
        ///
        /// \tparam ENFORCEMENT_PREDICATE [auto deduced] Unary predicate to
        ///            enforce expectations about the number of plugins with
        ///            the given Id available.
        ///
        ///        \note the predicate check only considers the number of
        ///            interfaces of type FILTERED_TYPE
        ///
        /// \param predicate [optional] A callable w/ the signature bool(void),
        ///            can be an instance of a struct/class with an operator(),
        ///            a free function, a lamdbda, etc.  The default, if not
        ///            provided, is to allow any number of plugins (0 or more)
        ///            of the requested type.
        ///
        /// \throw PluginError if the predicate is violated (the predicate
        ///                       returns false)
        ///
        /// \return A QVector of interface instances of the requested type
        ///
        /// Example usages:
        ///
        ///      // Any number of IMyInterfaceInstances
        ///      auto ifaces = GetInterfaceInstances<IMyInterface>();
        ///
        ///      // One, and only one instance of IMyInterfaceInstances should be found
        ///      auto ifaces = GetInterfacesInstances<IMyInterfaceInstances>(predicates::exactly<1>);
        ///
        ///      // At least two instances of IMyInterfaceInstances should be found
        ///      auto ifaces = GetInterfacesInstances<IMyInterfaceInstances>(predicates::greaterThan<1>);
        ///
        ///      // Between 4 and 7 (inclusive)
        ///      auto ifaces = GetInterfacesInstances<IMyInterfaceInstances>(predicates::between<4,7>);
        ///
        ///      // Or some abitrary predicate to determine the number of instances
        ///      auto ifaces = GetInterfacesInstances<IMyInterfaceInstances>([](int i){ return i < 4 || i > 7; });
        ///
        template<class INTERFACE_TYPE, class FILTERED_TYPE = INTERFACE_TYPE, class ENFORCEMENT_PREDICATE = decltype(predicates::anyNumber)>
            std::vector<std::shared_ptr<FILTERED_TYPE>> GetInterfaceInstances(
                    ENFORCEMENT_PREDICATE predicate = predicates::anyNumber) const
        {
            const auto id = INTERFACE_TYPE::GetInterfaceId();
            const auto idString = id.GetName();

            auto const hasExtension = cend(m_extensionMap) != m_extensionMap.find(id);

            auto const extensions = hasExtension ? m_extensionMap.at(id) : std::vector<ExtensionPtr>{};

            std::vector<std::shared_ptr<FILTERED_TYPE>> interfaceInstances;

            for(auto const& e : extensions) {
                auto const asIface = std::dynamic_pointer_cast<INTERFACE_TYPE>(e);
                auto const asType  = std::dynamic_pointer_cast<FILTERED_TYPE>(e);

                if(!asIface) {
                    throw PluginError("A plugin with id '" + idString +
                            "' was not of the expected type, dynamic cast failed "
                            "(do multiple plugin interfaces use the same ID string?)");
                }

                if(!asType) {
                    // Not the requested type, skip this one...
                    continue;
                }

                interfaceInstances.push_back(asType);
            }

            if(!predicate(interfaceInstances.size())) {
                throw PluginError(
                        "Did not find the expected number of plugins of type " +
                        idString + "\nNumber of instances: " +
                        std::to_string(interfaceInstances.size()));
            }

            return interfaceInstances;
        }

        /// Given a config filename with no path, figure out the full path.
        /// The resolution is in this order, by priority descending (i.e. stuff
        /// above trumps the stuff below):
        ///   - Absolute paths (always honored, never overriden/changed)
        ///   - Env var PLUGIN_CONFIG_PATH (used as a prefix if set)
        ///   - Default prefix, path to application/test binary
        ///
        /// \see GTestPluginManager.cpp
        ///
        /// Made public for testing
        static std::string ResolveConfigPath(std::string filename);

        /// Given a plugin filename with no path, figure out the full path.
        /// The resolution is in this order, by priority descending (i.e. stuff
        /// above trumps the stuff below):
        ///   - Absolute paths (always honored, never overriden/changed)
        ///   - Env var PLUGIN_PATH (used as a prefix if set)
        ///   - Default prefix ./plugins relative to application/test binary
        ///
        /// \see GTestPluginManager.cpp
        ///
        /// Made public for testing
        static std::string ResolvePluginPath(std::string filename);


    private:

        /// Loads the configuration from file
        ///
        /// \param filenames the input files describing the plugins to load
        ///
        /// \throw PluginError if unable to parse config or load plugins
        ///
        /// \note  This method is private because calling load
        ///        multiple times could lead to violation of the max
        ///        constraints for some plugins.  For now, if multiple
        ///        plugin configurations are desired it will be
        ///        necessary to have multiple PluginManager instances.
        void Load(std::vector<std::string> filenames);

        /// Internal method to resolve path
        /// \param filename Input file name
        /// \param envVarOverride Environment variable that overrides the prefix
        /// \param defaultPrefix Default path prefix to use if filename is
        ///        relative and env var is not set.
        static std::string ResolvePathInternal(std::string filename,
                                              const char* envVarOverride,
                                              std::string defaultPrefix);

        std::map<InterfaceId, std::vector<ExtensionPtr> > m_extensionMap;

        bool m_failHardOnShutdown { false };
    };

    // helper functions to clean up client code using common patterns
    namespace helpers {
        /// Gets a plugin from the provided plugin manager, enforces "one, and
        /// only one" instance of the requested interface
        ///
        /// \tparam INTERFACE_TYPE See \ref GetInterfacesInstances
        ///
        /// \tparam FILTERED_TYPE  See \ref GetInterfacesInstances
        ///
        /// \param pim PluginManager object from which to get the plugin
        ///
        /// \throw PluginError if the wrong number of plugins are found (!= 1 plugin)
        ///
        /// \return A pointer to the interface implementation.  It is safe to
        ///         assume that the pointer is valid.
        ///
        /// \note This function enforces the == 1 rule on the FILTERED_TYPE
        ///
        /// \note In general you'll want to call the parameterless overload of
        ///       this function as it's uncommon that you'll want to use any
        ///       other than the PluginManager in the container.
        ///
        template<class INTERFACE_TYPE, class FILTERED_TYPE = INTERFACE_TYPE>
            std::shared_ptr<FILTERED_TYPE> GetSinglePlugin(PluginManager const& pim)
        {
            return pim.GetInterfaceInstances<INTERFACE_TYPE, FILTERED_TYPE>(predicates::exactly<1>).front();
        }

        /// Gets a plugin from the default plugin manager, enforcing "one, and
        /// only one" instance of the requested interface
        ///
        ///  \ref GetSinglePlugin(PluginManager const& pim) for information on
        ///       the parameters, exeptions, and return value
        ///
        template<class INTERFACE_TYPE, class FILTERED_TYPE = INTERFACE_TYPE>
            std::shared_ptr<FILTERED_TYPE> GetSinglePlugin()
        {
            auto const& pim = Container::GetPluginManager();
            return GetSinglePlugin<INTERFACE_TYPE, FILTERED_TYPE>(pim);
        }

        /// Gets a plugin from the provided plugin manager, enforces "no more than
        /// one" instance of the requested interface
        ///
        /// \tparam INTERFACE_TYPE See \ref GetInterfacesInstances
        ///
        /// \tparam FILTERED_TYPE  See \ref GetInterfacesInstances
        ///
        /// \param pim Plugin manager from which to get the plugin
        ///
        /// \throw PluginError if > 1 plugins are found
        ///
        /// \return A pointer to the interface implementation.  The pointer
        ///         might be null if none were found.
        ///
        /// \note This function enforces the <= 1 rule on the FILTERED_TYPE
        ///
        /// \note In general you'll want to call the parameterless overload of
        ///       this function as it's uncommon that you'll want to use any
        ///       other than the PluginManager in the container.
        template<class INTERFACE_TYPE, class FILTERED_TYPE = INTERFACE_TYPE>
            std::shared_ptr<FILTERED_TYPE> GetOptionalPlugin(PluginManager const& pim)
        {
            auto const plugins = pim.GetInterfaceInstances<INTERFACE_TYPE, FILTERED_TYPE>(predicates::lessThan<2>);
            return plugins.empty() ? std::shared_ptr<FILTERED_TYPE>{} : plugins.front();
        }

        /// Gets a plugin from the default plugin manager, if it exists
        ///
        ///  \ref GetOptionalPlugin(PluginManager const& pim)
        ///       for information on the parameters, exceptions, and return
        ///       value
        ///
        template<class INTERFACE_TYPE, class FILTERED_TYPE = INTERFACE_TYPE>
            std::shared_ptr<FILTERED_TYPE> GetOptionalPlugin()
        {
            auto const& pim = Container::GetPluginManager();
            return GetOptionalPlugin<INTERFACE_TYPE, FILTERED_TYPE>(pim);
        }
    }

}

#endif // PLUGINMANAGER_H

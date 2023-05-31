#include "PluginManager.h"
#include "PluginConfigurationParser.h"
#include "PluginManagerExceptions.h"

#include "IPluginLib.h"
#include "Dependency.h"

#include "PluginUtils.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <utility>


namespace plugin
{
    // This is a helper class to handle plugin loading
    struct PluginPtr {
        plugin::interfaces::IPluginLib    *m_libPtr = nullptr;
        void                              *m_loader = nullptr;

        /// Default constructor
        ///
        /// \param libPtr   Pointer to library
        /// \param loader   Pointer to loader
        ///
        PluginPtr(plugin::interfaces::IPluginLib *libPtr, void *loader)
            : m_libPtr(libPtr)
            , m_loader(loader)
        {

        }

        ~PluginPtr()
        {
            delete m_libPtr;
            if (m_loader) {
                detail::libraryClose(m_loader);
            }
        }

    private:
        PluginPtr(const PluginPtr&) = delete;
        PluginPtr& operator=(const PluginPtr&) = delete;
    };

    namespace Container
    {
        // This function is here to put the pointer in a function rather
        // than at namespace scope to avoid static order-of-init issues.  It'll
        // get initialized (to null) in a thread-safe way the first time this
        // method is called, then the LoadPluginConfigurationFiles function will
        // set its value.
        std::unique_ptr<PluginManager>& instance()
        {
            static std::unique_ptr<PluginManager> pluginManager;
            return pluginManager;
        }

        void LoadPluginConfigurationFiles(std::vector<std::string> filenames)
        {
            // Force the old PIM to be shut down before creating a new one,
            // unloading existing plugins that aren't kept alive by shared pointers
            // elsewhere (empty reset call forces deletion of old PIM before
            // construction of new one)
            UnloadPluginManager();
            instance().reset(new plugin::PluginManager{filenames});
        }

        void LoadWithoutPlugins()
        {
            // Force the old PIM to be shut down before creating a new one,
            // unloading existing plugins that aren't kept alive by shared pointers
            // elsewhere (empty reset call forces deletion of old PIM before
            // construction of new one)
            UnloadPluginManager();
            instance().reset(new plugin::PluginManager{});
        }

        void UnloadPluginManager()
        {
            instance().reset();
        }

        plugin::PluginManager& GetPluginManager()
        {
            if(!instance()) {
                throw std::logic_error("There is no plugin manager, "
                        "did you call LoadPluginConfigurationFiles first?");
            }

            return *instance();
        }

        bool Loaded()
        {
            return instance() != nullptr;
        }
    }

    //======================================================================

    PluginManager::PluginManager(std::vector<std::string> filenames)
    {
        Load(filenames);
    }

    PluginManager::~PluginManager()
    {
        for(auto const& extVect : m_extensionMap) {
            for(auto const& ext : extVect.second) {

                auto const remainingInstances = ext.use_count() - 1;

                if(remainingInstances > 0) {
                    LOG_TODO_ERROR( "There are still " << remainingInstances << " instances of the "
                            << ext->GetId().GetName() << " interface still cached when destructing the PluginManager");

                    if(m_failHardOnShutdown) {
                        assert(!"Failing hard due to left-over cached plugins, please fix this before merging.");
                    }
                }
            }
        }
    }

    void PluginManager::FailHardAtShutdownIfCachedPluginsRemain()
    {
        m_failHardOnShutdown = true;
    }

    void PluginManager::Load(std::vector<std::string> filesToParse)
    {
        LOG_TODO_INFO("PluginManager: using configuration files: " + [&filesToParse]()->std::string{
                       std::string msgStr;
                       for(auto const& file : filesToParse) { msgStr += (file + ", "); }
                       return msgStr;
                    }());

        std::vector<std::string> alreadyParsedFiles;

        std::vector<std::string> plugins;
        std::vector<std::string> skippedPlugins;

        do
        {
            auto nextFile = filesToParse.back();
            filesToParse.pop_back();

            if(cend(alreadyParsedFiles) != std::find(cbegin(alreadyParsedFiles), cend(alreadyParsedFiles), nextFile))
            {
                LOG_TODO_INFO("Found duplicate plugin config file, skipping:  " << nextFile);
                continue;
            }

            alreadyParsedFiles.push_back(nextFile);

            // Resolve path according to documented heuristic
            nextFile = ResolveConfigPath(nextFile);

            LOG_TODO_INFO("Loading plugin configuration file:  " << nextFile);

            auto const configuration = detail::ParseConfiguration(nextFile);

            detail::AppendVector(filesToParse,   configuration.includeFiles);
            detail::AppendVector(plugins,        configuration.pluginList);
            detail::AppendVector(skippedPlugins, configuration.skippedPlugins);
        }
        while(!filesToParse.empty());


        std::vector<std::shared_ptr<PluginPtr>> pluginLibs;

        for (auto const& pluginName : plugins) {

            if(cend(skippedPlugins) != std::find(cbegin(skippedPlugins), cend(skippedPlugins), pluginName)) {
                LOG_TODO_INFO("Plugin has been skipped, not loading plugin:  " << pluginName);
                continue;
            }

            // NOTE:  There is no check for duplicate plugin files as that's
            //        allowed -- if you mention a plugin more than once when it
            //        should only be loaded once that's a configuration error, not
            //        something that the PluginManager should prevent.

            // Resolve path according to documented heuristic
            std::string plName = ResolvePluginPath(pluginName);

            LOG_TODO_INFO( "Loading plugin " << plName );

            auto pl = detail::libraryOpen(plName.c_str());
            if (!pl) {
                throw exceptions::PluginError{ "Error loading " + plName +": " + dlerror() };
            }

            void *raw_loader = detail::librarySymbol(pl, "plugin_creator");
            if (!raw_loader) {
                throw exceptions::PluginManagerException{ "Error loading plugin creator. Did you forget to call "
                                  "CREATE_PLUGIN_INSTANCE(MyPlugin::PluginMyPlugin) macro?" };
            }

            auto creator = reinterpret_cast<creator_ptr>(raw_loader);

            auto ngplugin = creator();
            if (!ngplugin) {
                throw exceptions::PluginError{ "This plugin does not contain a "
                        "valid IPluginLib implementation:  " + plName };
            }

            pluginLibs.push_back(std::make_shared<PluginPtr>(ngplugin, pl));

            for(auto extension : ngplugin->GetExtensions()) {
                // Some magic to get reference count from PluginPtr to be used
                // in extensions : it replaces counter of extension with a
                // counter to a pair that consist of extension and library with
                // implementation. Struct is used because in std::pair order of
                // destruction is not specified
                struct {
                    std::shared_ptr<PluginPtr> plug;
                    decltype(extension) ext;
                } con = {pluginLibs.back(), extension};
                auto connection = std::make_shared<decltype(con)>(con);
                ExtensionPtr ext(connection, connection->ext.get());

                m_extensionMap[ext->GetId()].push_back(ext);
            }

        }

        for (auto const& pl : pluginLibs) {
            pl->m_libPtr->Initialize();
        }

        for (auto const& pl : pluginLibs) {

            for (auto const dep : pl->m_libPtr->GetDependencies()) {

                auto const id = dep->GetInterfaceId();
                auto const& extensionVect = m_extensionMap[id];

                if ((ssize_t) extensionVect.size() < dep->GetMinExt()) {
                    throw exceptions::DependencyError{ "This plugin configuration could not provide "
                        "enough extensions of type " + id.GetName() };
                }

                if ((ssize_t) extensionVect.size() > dep->GetMaxExt()) {
                    throw exceptions::DependencyError{ "This plugin configuration provided too many "
                        "extensions of type " + id.GetName() };
                }

                for (auto const& pi : extensionVect) {
                    pl->m_libPtr->ConnectExtension(pi);
                }
            }
        }

        for (auto const& pl : pluginLibs) {
            pl->m_libPtr->PostDependencyInit();
        }
    }

    std::string PluginManager::ResolveConfigPath(std::string filename)
    {
        return ResolvePathInternal(filename, "PLUGIN_CONFIG_PATH", "");
    }

    std::string PluginManager::ResolvePluginPath(std::string filename)
    {
        return ResolvePathInternal(filename, "PLUGIN_PATH", "plugins/");
    }

    std::string PluginManager::ResolvePathInternal(std::string filename,
                                               const char* envVarOverride,
                                               std::string defaultPrefix)
    {
        if(filename.empty()) {
            throw std::logic_error("Received invalid filename in ResolvePathInternal");
        }

        std::ifstream file(filename.c_str());

        // Respect absolute paths. We assume that client passed an absolute
        // path because they know the exact location which is fixed.
        if (file.is_open() || filename[0] == '/') {
            return filename;
        }

        // Check environment variable to override the default location
        const char *pluginDir = std::getenv(envVarOverride);
        if (pluginDir) {
            return std::string(pluginDir) + "/" + filename;
        }

        // Fallback onto default, which is path to application binary
        std::string appBinPath = detail::GetApplicationPath();
        return appBinPath + "/" + defaultPrefix + filename;
    }
}


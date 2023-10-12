#ifndef PLUGINCONFIGURATIONPARSER_H_ABC92D9F_43FB_4BC3_AC99_266A8263893F
#define PLUGINCONFIGURATIONPARSER_H_ABC92D9F_43FB_4BC3_AC99_266A8263893F

#include <filesystem>
#include <string>
#include <vector>

namespace plugin {
    namespace detail {

        struct ConfigData
        {
            std::vector<std::string> pluginList;
            std::vector<std::string> skippedPlugins;
            std::vector<std::string> includeFiles;
        };

        //==================================================
        /// Parses a configuration, returning a list of loaded plugins
        /// Only for PluginManager + tests, not to be used by other client code
        ///
        /// \param file The configuration file to parse
        ///
        /// \return PluginConfiguration struct containing loaded configuration
        ///
        ConfigData ParseConfiguration(std::filesystem::path file);
    }
}

#endif // PLUGINCONFIGURATIONPARSER_H_ABC92D9F_43FB_4BC3_AC99_266A8263893F

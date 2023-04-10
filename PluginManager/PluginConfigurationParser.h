#ifndef PLUGINCONFIGURATIONPARSER_H_ABC92D9F_43FB_4BC3_AC99_266A8263893F
#define PLUGINCONFIGURATIONPARSER_H_ABC92D9F_43FB_4BC3_AC99_266A8263893F

#include <vector>
#include <string>

namespace plugin {
    namespace detail {

        //==================================================
        /// Parses a configuration, returning a list of loaded plugins
        /// Only for PluginManager + tests, not to be used by other client code
        ///
        /// \param filename The configuration file to parse
        ///
        /// \return PluginConfiguration struct containing loaded configuration
        ///
        std::vector<std::string> ParseConfiguration(std::string filename);
    }
}

#endif // PLUGINCONFIGURATIONPARSER_H_ABC92D9F_43FB_4BC3_AC99_266A8263893F

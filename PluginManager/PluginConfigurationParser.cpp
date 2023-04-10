#include "PluginConfigurationParser.h"
#include "PluginManagerExceptions.h"

#include <fstream>
#include <regex>
#include <string>
#include <vector>

namespace
{
    /// Checks for configuration lines that should be ignored (blank, or comments starting with #)
    ///
    /// \return bool indicating whether the line should be ignored 
    ///
    bool IsIgnoredLine(std::string const& configLine)
    {
        std::regex const ignoredLineRegex{ R"(^\s*#|^\s*$)" };
        return std::regex_search(configLine, ignoredLineRegex);
    }

    /// Check whether the line is a `plugin:` line, if so it returns the name of the plugin
    std::string ExtractPluginName(std::string const& filename, std::string const& configLine)
    {
        // Plugins are specified with the leader, "plugin:", and can have
        // trailing comments -- leading and trailing whitespace should be
        // ignored
        //
        // RKTODO:  Fix regex to not treat `plugin: abc def` as "abc", but
        //          instead as an error -- for some reason replacing the
        //          trailing .* with [/s#]* isn't working as I'd expect it to.
        //          Also consider rewriting the regex to requirie the plugin
        //          name to be in quotes to allow spaces in filenames (yuck!)
        //          as well as the # character.
        //
        std::regex const pluginLineRegex{ R"(^(\s*plugin:\s*)([^\s#]+).*)" };

        std::smatch match;

        // note:  per the docs, the size = number of sub-expressions + 1
        if(std::regex_match(configLine, match, pluginLineRegex)
                && match.size() == 3)
        {
            return match[2];
        }

        throw plugin::exceptions::ConfigurationError{ filename, configLine };
    }
}


namespace plugin {
    namespace detail {

        //----------------------------------------------------------------------
        std::vector<std::string> ParseConfiguration(std::string filename)
        {
            std::ifstream ifs{ filename.c_str(), std::ifstream::in };

            if (!ifs.is_open()) {
                throw exceptions::PluginManagerException{ "Couldn't open file for reading:  " + filename };
            }

            std::vector<std::string> pluginList;

            while(ifs)
            {
                std::string configLine;
                std::getline(ifs, configLine);

                if(IsIgnoredLine(configLine))
                {
                    // Ignoring comments and blank lines
                    continue;
                }
                else if(auto pluginName = ExtractPluginName(filename, configLine); !pluginName.empty())
                {
                    pluginList.emplace_back(std::move(pluginName));
                }
                else
                {
                    throw exceptions::ConfigurationError{ filename, configLine };
                }
            }

            return pluginList;
        }
    }
}

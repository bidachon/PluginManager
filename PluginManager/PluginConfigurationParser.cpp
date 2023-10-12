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

    std::string ExtractRegex(std::string const& line_prefix, std::string const& configLine)
    {
        // RKTODO:  Fix regexex to not treat `plugin: abc def` as "abc", but
        //          instead as an error -- for some reason replacing the
        //          trailing .* with [/s#]* isn't working as I'd expect it to.
        //          Also consider rewriting the regex to requirie the plugin
        //          name to be in quotes to allow spaces in filenames (yuck!)
        //          as well as the # character.
        //

        std::regex const lineRegex{ R"(^(\s*)" + line_prefix + R"(:\s*)([^\s#]+).*)" };

        std::smatch match;

        // note:  per the docs, the size = number of sub-expressions + 1
        if(std::regex_match(configLine, match, lineRegex)
                && match.size() == 3)
        {
            return match[2];
        }

        return {};
    }

    std::string ExtractPluginName(std::string const& configLine)
    {
        return ExtractRegex("load_plugin", configLine);
    }

    std::string ExtractIncludeFile(std::string const& configLine)
    {
        return ExtractRegex("include_file", configLine);
    }

    std::string ExtractSkippedPlugin(std::string const& configLine)
    {
        return ExtractRegex("skip_plugin", configLine);
    }
}


namespace plugin {
    namespace detail {

        //----------------------------------------------------------------------
        ConfigData ParseConfiguration(std::filesystem::path file)
        {
            std::ifstream ifs{ file.c_str(), std::ifstream::in };

            if (!ifs.is_open())
            {
                throw exceptions::PluginManagerException{ "Couldn't open file for reading:  " + file.native() };
            }

            ConfigData data;

            while(ifs)
            {
                std::string configLine;
                std::getline(ifs, configLine);

                if(IsIgnoredLine(configLine))
                {
                    // Ignoring comments and blank lines
                    continue;
                }
                else if(auto loadedPlugin = ExtractPluginName(configLine); !loadedPlugin.empty())
                {
                    data.pluginList.emplace_back(std::move(loadedPlugin));
                }
                else if(auto skippedPlugin = ExtractSkippedPlugin(configLine); !skippedPlugin.empty())
                {
                    data.skippedPlugins.emplace_back(std::move(skippedPlugin));
                }
                else if(auto includeFile = ExtractIncludeFile(configLine); !includeFile.empty())
                {
                    data.includeFiles.emplace_back(std::move(includeFile));
                }
                else
                {
                    throw exceptions::ConfigurationError{ file.native(), configLine };
                }
            }

            return data;
        }
    }
}

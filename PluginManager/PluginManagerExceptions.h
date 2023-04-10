#ifndef PLUGINMANAGEREXCEPTIONS_H_A308364A_413C_4571_A9CA_FD07014A532D
#define PLUGINMANAGEREXCEPTIONS_H_A308364A_413C_4571_A9CA_FD07014A532D

#include <stdexcept>

namespace plugin::exceptions
{
    /// Base class for all PluginManager errors, thrown when there's a problem w/ the plugin manager itself
    struct PluginManagerException : std::runtime_error { using std::runtime_error::runtime_error; };

    /// Thrown when there is a problem w/ the implementation or construction of a plugin
    struct PluginError : PluginManagerException { using PluginManagerException::PluginManagerException; };

    /// Thrown when there is a problem parsing the configuration file
    struct ConfigurationError : PluginManagerException
    {
        explicit ConfigurationError(std::string const& filename, std::string const& configLine)
            : PluginManagerException{ "Error in plugin configuration file, " + filename +
                                      " invalid configuration line:  " + configLine }
            , m_filename{ filename }
            , m_configLine{ configLine }
        {
        }

        std::string m_filename;
        std::string m_configLine;
    };

    /// Thrown when there is a problem trying to fulfill the dependency requirements
    struct DependencyError : PluginManagerException { using PluginManagerException::PluginManagerException; };
}

#endif // PLUGINMANAGEREXCEPTIONS_H_A308364A_413C_4571_A9CA_FD07014A532D


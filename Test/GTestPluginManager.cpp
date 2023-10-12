#include "Plugins/Interfaces/IGeneratorManager.h"
#include "Plugins/Interfaces/INumberGenerator.h"
#include "Plugins/Interfaces/IStatefulPluginInterface.h"

#include "PluginManager.h"
#include "PluginManagerExceptions.h"
#include "PluginUtils.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdlib> // setenv()
#include <memory>
#include <regex>
#include <string>
#include <utility>


using namespace testing;

namespace
{
    auto IsEqual = [](auto const& a, auto const& b) { return a == b; };

    /// Checks whether a value exists in a collection.
    ///
    /// \param value The value to be checked for.
    ///
    /// \param container The container in which the value need to be searched for.
    ///
    /// \param pred A custom binary predicate.
    ///
    /// \note For the custom binary predicate (pred) the first value is the
    ///       type and value from the container class (container), and the
    ///       second value is the type and value of the element being compared
    ///       (value).
    ///
    /// \return true if value is in the container else false.
    ///
    template <typename T, typename C, typename PREDICATE=decltype(IsEqual)>
    bool IsIn(T const& value, C const& container, PREDICATE pred = IsEqual)
    {
        using std::cbegin;
        using std::cend;
        return cend(container) != std::find_if(cbegin(container), cend(container), [&value, &pred](auto const& v){ return pred(v, value); });
    }

    template <typename T, typename ILData, typename PREDICATE=decltype(IsEqual)>
    bool IsIn(T const& value, std::initializer_list<ILData> const& container, PREDICATE pred = IsEqual)
    {
        using std::cbegin;
        using std::cend;
        return cend(container) != std::find_if(cbegin(container), cend(container), [&value, &pred](auto const& v){ return pred(v, value); });
    }
}


#define EXPECT_EXCEPTION_TEXT(l, t, exc_type) \
    try { \
        l; \
        FAIL() << "The function did not throw an exception as expected."; \
    } catch(exc_type const& e) { \
        const auto msg = e.what(); \
        std::cmatch cm; \
        EXPECT_TRUE(std::regex_search(msg,cm, std::regex(t))) << e.what();  \
    } \
    catch(std::exception const& e) { \
        FAIL() << "The function threw an exception of the wrong type (" << typeid(e).name() << " vs. expected " << #exc_type << "), with text:\n       " << e.what(); \
    } \
    catch(...) { \
        FAIL() << "The function threw an exception of the wrong type, not derived from std::exception."; \
    }



TEST(TestPluginManager, invalidPluginfile)
{
    EXPECT_EXCEPTION_TEXT(plugin::PluginManager pm("invalidpluginfile.pb.txt"),
                          ".*invalidpluginfile.pb.txt.*invalid configuration line.*",
                          plugin::exceptions::ConfigurationError);
}

TEST(TestPluginManager, notEnoughExtensions)
{
    EXPECT_EXCEPTION_TEXT(plugin::PluginManager pm("notenoughextensions.pb.txt"),
                          "This plugin configuration could not provide "
                          "enough extensions of type INumberGenerator",
                          plugin::exceptions::DependencyError);
}

TEST(TestPluginManager, tooManyExtensions)
{
    EXPECT_EXCEPTION_TEXT(plugin::PluginManager pm("toomanyextensions.pb.txt"),
                          "This plugin configuration provided too many "
                          "extensions of type INumberGenerator",
                          plugin::exceptions::DependencyError);
}

TEST(TestPluginManager, nominalPluginList)
{
    plugin::PluginManager pm("pluginlist.pb.txt");

    // Get plugin, ensure no exception is thrown
    EXPECT_NE(nullptr, plugin::helpers::GetSinglePlugin<plugin::interfaces::IGeneratorManager>(pm));

    // Get existing plugin with "optional" interface, ensure no exception is thrown
    EXPECT_NE(nullptr, plugin::helpers::GetOptionalPlugin<plugin::interfaces::IGeneratorManager>(pm));
}

TEST(TestPluginManager, requestUnlistedPlugin)
{
    plugin::PluginManager pm("pluginlist_onlyone.pb.txt");

    // Get plugin that doesn't exist, ensure exception thrown
    EXPECT_THROW(plugin::helpers::GetSinglePlugin<plugin::interfaces::IGeneratorManager>(pm), plugin::exceptions::PluginError);

    // Get plugin that doesn't exist, ensure no exception thrown
    EXPECT_EQ(nullptr, plugin::helpers::GetOptionalPlugin<plugin::interfaces::IGeneratorManager>(pm));
}

TEST(TestPluginManager, statefulPluginReload)
{
    auto pm = std::make_unique<plugin::PluginManager>("statefulplugintest.pb.txt");

    std::weak_ptr<plugin::interfaces::IStatefulPluginInterface> wp = plugin::helpers::GetSinglePlugin<plugin::interfaces::IStatefulPluginInterface>(*pm);

    { // artificial scope to ensure that the shared pointers go out of scope
        auto const sp = wp.lock();

        EXPECT_EQ(plugin::interfaces::IStatefulPluginInterface::DEFAULT_VALUE, sp->GetNumber()) << "The initial value is not what was expected";

        auto const testValue = 42;
        sp->SetNumber(testValue);
        EXPECT_EQ(testValue, sp->GetNumber()) << "The new value is not what was expected";

        auto const sp2 = plugin::helpers::GetSinglePlugin<plugin::interfaces::IStatefulPluginInterface>(*pm);
        EXPECT_EQ(sp.get(), sp2.get()) << "Getting the interface again does NOT return the same shared pointer";
        EXPECT_EQ(testValue, sp2->GetNumber()) << "Getting another pointer to the same interface does NOT give the same internal state";
    }

    EXPECT_FALSE(wp.expired()) << "The plugin object was deleted, but should still exist.";

    // Unload the plugins by deleting the plugin manager instance
    pm.reset();
    EXPECT_TRUE(wp.expired()) << "The plugin object WAS NOT deleted after unloading the plugin manager.";

    // Load a new plugin manager
    pm = std::make_unique<plugin::PluginManager>("statefulplugintest.pb.txt");

    // .. and make sure that it gives fresh interface instances
    auto const sp = plugin::helpers::GetSinglePlugin<plugin::interfaces::IStatefulPluginInterface>(*pm);
    EXPECT_EQ(plugin::interfaces::IStatefulPluginInterface::DEFAULT_VALUE, sp->GetNumber()) << "The initial value is not what was expected after reloading the plugins";
}

//**********************************************************************
TEST(TestPluginManagerPathResolution, RespectsAbsolutePath_Plugin)
{
    std::string pluginFile("/path/to/some.plugin.so");

    EXPECT_THAT(plugin::PluginManager::ResolvePluginPath(pluginFile), Eq(pluginFile));
}

TEST(TestPluginManagerPathResolution, RespectsAbsolutePath_Config)
{
    std::string configFile("/path/to/some.pluginlist.pb.txt");

    EXPECT_THAT(plugin::PluginManager::ResolveConfigPath(configFile), Eq(configFile));
}

TEST(TestPluginManagerPathResolution, RespectsEnvironmentOverride_Plugin)
{
    setenv("PLUGIN_PATH", "/tmp/overridden", 1);

    EXPECT_THAT(plugin::PluginManager::ResolvePluginPath("some.plugin.so"),
                Eq("/tmp/overridden/some.plugin.so"));
}

TEST(TestPluginManagerPathResolution, RespectsEnvironmentOverride_Config)
{
    setenv("PLUGIN_CONFIG_PATH", "/tmp/overridden_config", 1);

    EXPECT_THAT(plugin::PluginManager::ResolveConfigPath("some.pluginlist.pb.txt"),
                Eq("/tmp/overridden_config/some.pluginlist.pb.txt"));
}

TEST(TestPluginManagerPathResolution, RespectsEnvironmentOverrideWithRelativePath_Plugin)
{
    setenv("PLUGIN_PATH", "/tmp/overridden", 1);

    EXPECT_THAT(plugin::PluginManager::ResolvePluginPath("../sub1/some.plugin.so"),
                Eq("/tmp/overridden/../sub1/some.plugin.so"));
}

TEST(TestPluginManagerPathResolution, RespectsEnvironmentOverrideWithRelativePath_Config)
{
    setenv("PLUGIN_CONFIG_PATH", "/tmp/overridden_config", 1);

    EXPECT_THAT(plugin::PluginManager::ResolveConfigPath("../sub1/some.pluginlist.pb.txt"),
                Eq("/tmp/overridden_config/../sub1/some.pluginlist.pb.txt"));
}

TEST(TestPluginManagerPathResolution, RespectsAbsolutePathEvenWhenEnvironmentSet_Plugin)
{
    setenv("PLUGIN_PATH", "/tmp/overridden", 1);
    std::string pluginFile("/path/to/some.plugin.so");

    EXPECT_THAT(plugin::PluginManager::ResolvePluginPath(pluginFile), Eq(pluginFile));
}

TEST(TestPluginManagerPathResolution, RespectsAbsolutePathEvenWhenEnvironmentSet_Config)
{
    setenv("PLUGIN_CONFIG_PATH", "/tmp/overridden_config", 1);
    std::string pluginConfig("/path/to/some.pluginlist.pb.txt");

    EXPECT_THAT(plugin::PluginManager::ResolveConfigPath(pluginConfig), Eq(pluginConfig));
}

TEST(TestPluginManagerPathResolution, FallsbackOnDefault_Plugin)
{
    unsetenv("PLUGIN_PATH");
    std::string pluginFile("plugin.so");
    auto const expectedDefaultPath = plugin::detail::GetApplicationPath() / "plugins" / pluginFile;
    auto const actual = plugin::PluginManager::ResolvePluginPath(pluginFile);

    EXPECT_EQ(expectedDefaultPath, actual);
}

TEST(TestPluginManagerPathResolution, FallsbackOnDefault_Config)
{
    unsetenv("PLUGIN_CONFIG_PATH");
    std::string const configFile{"pluginlist.pb.txt"};
    auto const expectedDefaultPath = plugin::detail::GetApplicationPath();
    auto const configPath = expectedDefaultPath / configFile;

    auto const resolvedPath = plugin::PluginManager::ResolveConfigPath(configFile);
    auto const resolvedPathCombined = plugin::detail::GetApplicationPath() / resolvedPath;

    auto const expectedPaths = {resolvedPath, resolvedPathCombined};
    EXPECT_TRUE(IsIn(configPath, expectedPaths));
}

TEST(TestPluginManagerPathResolution, FallsbackOnDefaultWithRelativePath_Plugin)
{
    unsetenv("PLUGIN_PATH");
    std::string pluginFile("sub2/test_plugin.so");
    auto const expectedDefaultPath = plugin::detail::GetApplicationPath() / "plugins";

    EXPECT_THAT(plugin::PluginManager::ResolvePluginPath(pluginFile),
                Eq(expectedDefaultPath / pluginFile));
}

TEST(TestPluginManagerPathResolution, FallsbackOnDefaultWithRelativePath_Config)
{
    unsetenv("PLUGIN_CONFIG_PATH");
    std::string configFile("sub2/test_pluginlist.pb.txt");
    auto const expectedDefaultPath = plugin::detail::GetApplicationPath();

    EXPECT_THAT(plugin::PluginManager::ResolveConfigPath(configFile),
            Eq(expectedDefaultPath / configFile));
}


#include "PluginConfigurationParser.h"
#include "PluginManagerExceptions.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <filesystem>
#include <fstream>
#include <regex>
#include <stdexcept>
#include <string>

namespace {
    std::string invalidConfigStr = R"(
nonexistent_field: dummy.so
)";

    //==================================================
    struct TestPluginConfigurationParser : ::testing::Test
    {
        std::filesystem::path GetCorruptFile() {
            auto const corruptFile = std::filesystem::temp_directory_path() / "invalid.pb.txt";
            std::ofstream ofs(corruptFile, std::ofstream::trunc);
            if (!ofs.is_open())
            {
                throw std::runtime_error{ "Failed to open file " + corruptFile.native() + " for writing." };
            }
            ofs << invalidConfigStr;
            return corruptFile;
        }
    };

} // namespace

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

//==================================================
TEST_F(TestPluginConfigurationParser, FailsWithNonexistentFile)
{
    EXPECT_EXCEPTION_TEXT(plugin::detail::ParseConfiguration("nonexistent.file"),
            "Couldn't open file for reading.*",
            plugin::exceptions::PluginManagerException);
}

//--------------------------------------------------
TEST_F(TestPluginConfigurationParser, FailsWithInvalidFile)
{
    EXPECT_EXCEPTION_TEXT(plugin::detail::ParseConfiguration(GetCorruptFile()),
            "Error in plugin configuration file.*invalid configuration.*",
            plugin::exceptions::ConfigurationError);
}


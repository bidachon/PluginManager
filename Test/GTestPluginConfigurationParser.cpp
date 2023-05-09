#include "PluginConfigurationParser.h"

#include <gtest/gtest.h>
// #include <gmock/gmock.h>

#include <fstream>
#include <string>

namespace {
#if 0
    string invalidConfigStr = R"(
nonexistent_field: "dummy.so"
)";
#endif

    //==================================================
    struct TestPluginConfigurationParser : ::testing::Test
    {
#if 0
        string GetCorruptFile() {
            string corruptFile(Locator::GetTempDirectory() + "/invalid.pb.txt");
            ofstream ofs(corruptFile, ofstream::trunc);
            if (!ofs.is_open()) {
                throw std::runtime_error("Failed to open file " + corruptFile
                                         + " for writing.");
            }
            ofs << invalidConfigStr;
            return string(corruptFile);
        }
#endif
    };

} // namespace


//==================================================
TEST_F(TestPluginConfigurationParser, FailsWithNonexistentFile)
{
#if 0
    auto result = ParseConfiguration("nonexistent.file");

    EXPECT_FALSE(result.valid);
    EXPECT_TRUE(result.pluginList.empty());
#endif
}

//--------------------------------------------------
TEST_F(TestPluginConfigurationParser, FailsWithInvalidFile)
{
#if 0
    auto result = ParseConfiguration(GetCorruptFile());

    EXPECT_FALSE(result.valid);
    EXPECT_TRUE(result.pluginList.empty());
#endif
}


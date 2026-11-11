#include "SaveConfig.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <string>
#include <system_error>

class SaveConfigTESTS : public ::testing::Test
{
protected:
    auto TearDown() -> void override
    {
        std::error_code errorCode;
        std::filesystem::remove_all("test_saves_dir", errorCode);
    }
};

TEST_F(SaveConfigTESTS, GetSaveDirectoryReturnsNonEmptyPath)
{
    EXPECT_FALSE(SaveConfig::GetSaveDirectory().empty());
}

TEST_F(SaveConfigTESTS, GetAutoSaveDirectoryReturnsNonEmptyPath)
{
    EXPECT_FALSE(SaveConfig::GetAutoSaveDirectory().empty());
}

TEST_F(SaveConfigTESTS, AutoSaveDirectoryIsSubpathOfSaveDirectory)
{
    const auto save = std::string(SaveConfig::GetSaveDirectory());
    const auto autoSave = std::string(SaveConfig::GetAutoSaveDirectory());

    EXPECT_NE(autoSave.find(save), std::string::npos);
}

TEST_F(SaveConfigTESTS, CreateDirectoryIfNotExistsCreatesNewDirectory)
{
    const auto path = std::filesystem::path("test_saves_dir");

    ASSERT_FALSE(std::filesystem::exists(path));
    EXPECT_TRUE(SaveConfig::CreateDirectoryIfNotExists(path.string()));
    EXPECT_TRUE(std::filesystem::exists(path));
}

TEST_F(SaveConfigTESTS, CreateDirectoryIfNotExistsReturnsTrueIfAlreadyExists)
{
    const auto path = std::filesystem::path("test_saves_dir");
    std::filesystem::create_directories(path);

    EXPECT_TRUE(SaveConfig::CreateDirectoryIfNotExists(path.string()));
}

TEST_F(SaveConfigTESTS, CreateDirectoryIfNotExistsCreatesNestedPath)
{
    const auto path = std::filesystem::path("test_saves_dir/nested/deep");

    EXPECT_TRUE(SaveConfig::CreateDirectoryIfNotExists(path.string()));
    EXPECT_TRUE(std::filesystem::exists(path));
}

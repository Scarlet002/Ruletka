#include "SaveConfig.h"
#include <cstdio>
#include <filesystem>
#include <print>
#include <string_view>

auto SaveConfig::CreateDirectoryIfNotExists(std::string_view path) -> bool
{
    try
    {
        return std::filesystem::exists(path) || std::filesystem::create_directories(path);
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::println(stderr, "Directory creation error {}: {}", path, e.what());
        return false;
    }
}

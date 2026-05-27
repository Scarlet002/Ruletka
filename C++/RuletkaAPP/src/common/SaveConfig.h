#pragma once
#include <filesystem>
#include <iostream>
#include <string>

class SaveConfig
{
public:
	SaveConfig() = delete;

    [[nodiscard]] static std::string GetSaveDirectory() noexcept { return "data/saves"; }

    [[nodiscard]] static std::string GetAutoSaveDirectory() noexcept{ return "data/saves/autosaves"; }

    [[nodiscard]] static bool CreateDirectoryIfNotExists(const std::string& path) noexcept
    {
        try
        {
            if (!std::filesystem::exists(path)) { return std::filesystem::create_directories(path); }
            return true;
        }
        catch (const std::filesystem::filesystem_error& e)
        {
            std::cerr << "Blad tworzenia katalogu " << path << ": " << e.what() << '\n';
            return false;
        }
    }
};
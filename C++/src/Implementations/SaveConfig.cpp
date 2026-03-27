#include "SaveConfig.h"
#include <filesystem>
#include <iostream>
#include <string>

std::string SaveConfig::GetSaveDirectory() { return "data/saves"; }
std::string SaveConfig::GetAutoSaveDirectory() { return "data/saves/autosaves"; }
bool SaveConfig::CreateDirectoryIfNotExists(const std::string& path)
{
    try
    {
        if (!std::filesystem::exists(path)) { return std::filesystem::create_directories(path); }
        return true;
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cout << "Blad tworzenia katalogu " << path << ": " << e.what() << '\n';
        return false;
    }
}
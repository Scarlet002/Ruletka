#include "SaveConfig.h"
#include <filesystem>
#include <iostream>
#include <string>

using std::string;

namespace fs = std::filesystem;

using std::cout;
using std::endl;

const string SaveConfig::GetSaveDirectory()
{
    return "data/saves";
}

const string SaveConfig::GetAutoSaveDirectory()
{
    return "data/saves/autosaves";
}

bool SaveConfig::CreateDirectoryIfNotExists(const std::string& path)
{
    try
    {
        if (!fs::exists(path))
        {
            return fs::create_directories(path);
        }
        return true;
    }
    catch (const fs::filesystem_error& e)
    {
        cout << "Blad tworzenia katalogu " << path << ": " << e.what() << endl;
        return false;
    }
}
#pragma once
#include <string>

class SaveConfig
{
public:
	SaveConfig() = delete;

    static std::string GetSaveDirectory();
    static std::string GetAutoSaveDirectory();
    static bool CreateDirectoryIfNotExists(const std::string& path);
};
#pragma once
#include <string>

using std::string;

class SaveConfig
{
public:
    static const string GetSaveDirectory();
    static const string GetAutoSaveDirectory();
    static bool CreateDirectoryIfNotExists(const string& path);
};
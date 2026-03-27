#pragma once
#include "ForwardDeclarations.h"
#include <string>
#include <regex>
#include <iostream>

class InputValidatorManager
{
public:
    InputValidatorManager() = delete;

    static bool IsValidFileName(const std::string& fileName);
    static bool IsValidMenuChoice(const std::string& input);
    static bool IsValidItemChoice(const std::string& input);
    static bool IsValidYesNo(const std::string& input);
    static bool IsValidDifficultyChoice(const std::string& input);
    static std::string GetValidatedInput(const std::string& prompt,
        bool (*validator)(const std::string&));
};
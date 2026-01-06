#pragma once
#include "ForwardDeclarations.h"
#include <string>
#include <regex>
#include <iostream>

using std::string;

class InputValidatorManager
{
public:
    InputValidatorManager() {};

    static bool IsValidFileName(const string& fileName);
    static bool IsValidMenuChoice(const string& input);
    static bool IsValidItemChoice(const string& input);
    static bool IsValidYesNo(const string& input);
    static bool IsValidDifficultyChoice(const string& input);
    static string GetValidatedInput(const string& prompt, bool (*validator)(const string&));

    ~InputValidatorManager() {};
};
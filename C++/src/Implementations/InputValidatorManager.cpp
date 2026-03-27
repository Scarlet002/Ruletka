#include "InputValidatorManager.h"
#include <iostream>
#include <string>
#include <regex>

bool InputValidatorManager::IsValidFileName(const std::string& fileName)
{
    std::regex pattern("^[a-zA-Z0-9_-]{1,30}$");
    return regex_match(fileName, pattern);
}
bool InputValidatorManager::IsValidMenuChoice(const std::string& input)
{
    std::regex pattern("^[0-6]$");
    return regex_match(input, pattern);
}
bool InputValidatorManager::IsValidItemChoice(const std::string& input)
{
    std::regex pattern("^[0-6]$");
    return regex_match(input, pattern);
}
bool InputValidatorManager::IsValidYesNo(const std::string& input)
{
    std::regex pattern("^[tTnN]$");
    return regex_match(input, pattern);
}
bool InputValidatorManager::IsValidDifficultyChoice(const std::string& input)
{
    std::regex pattern("^[0-2]$");
    return regex_match(input, pattern);
}
std::string InputValidatorManager::GetValidatedInput(const std::string& prompt,
    bool (*validator)(const std::string&))
{
    std::string input;
    while (true)
    {
        std::cout << prompt;
        std::cin >> input;

        if (validator(input)) {
            return input;
        }
        std::cout << "Nieprawidlowe dane! Sprobuj ponownie." << '\n';
    }
}
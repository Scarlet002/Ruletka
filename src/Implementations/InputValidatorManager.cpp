#include "InputValidatorManager.h"
#include <string>
#include <regex>
#include <iostream>

using std::regex;
using std::cin;
using std::string;
using std::cout;
using std::endl;

    bool InputValidatorManager::IsValidFileName(const string& fileName) {
        regex pattern("^[a-zA-Z0-9_-]{1,30}$");
        return regex_match(fileName, pattern);
    }

    bool InputValidatorManager::IsValidMenuChoice(const string& input) {
        regex pattern("^[0-6]$");
        return regex_match(input, pattern);
    }

    bool InputValidatorManager::IsValidItemChoice(const string& input) {
        regex pattern("^[0-6]$");
        return regex_match(input, pattern);
    }

    bool InputValidatorManager::IsValidYesNo(const string& input) {
        regex pattern("^[tTnN]$");
        return regex_match(input, pattern);
    }

    bool InputValidatorManager::IsValidDifficultyChoice(const string& input) {
        regex pattern("^[0-2]$");
        return regex_match(input, pattern);
    }

    string InputValidatorManager::GetValidatedInput(const string& prompt, bool (*validator)(const string&)) {
        string input;
        while (true) {
            cout << prompt;
            cin >> input;

            if (validator(input)) {
                return input;
            }
            cout << "Nieprawidlowe dane! Sprobuj ponownie." << endl;
        }
    }
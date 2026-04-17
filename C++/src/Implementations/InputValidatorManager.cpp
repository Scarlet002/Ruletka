#include "InputValidatorManager.h"
#include "GameEnums.h"
#include <iostream>
#include <string>
#include <regex>
#include <thread>
#include <conio.h>

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
    std::regex pattern("^[0-1]$");
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
    while (_kbhit()) _getch();

    std::cout << prompt << std::flush;
    std::string input = "";
    while (true) 
    {
        if (_kbhit()) 
        {
            char ch = _getch();
            if (ch == 13) 
            {
                std::cout << '\n';
                if (validator(input))
                {
                    while (_kbhit()) _getch();
                    return input;
                }
                else
                {
                    input = "";
                    std::cout << "Nieprawidlowy wybor. Sprobuj ponownie: ";
                }
            }
            else if (ch == 8 && !input.empty()) 
            {
                input.pop_back();
                std::cout << "\b \b";
            }
            else if (ch >= 32 && ch < 127) 
            {
                input += ch;
                std::cout << ch;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}
#pragma once
#include "ForwardDeclarations.h"
#include "GameEnums.h"
#include <iostream>
#include <string>
#include <regex>
#include <thread>
#include <conio.h>

class InputValidatorManager
{
public:
    InputValidatorManager() = delete;
    
    [[nodiscard]] static bool IsValidFileName(const std::string& fileName) noexcept
    {
        std::regex pattern("^[a-zA-Z0-9_-]{1,30}$");
        return regex_match(fileName, pattern);
    }

    [[nodiscard]] static bool IsValidMainUIChoice(const std::string& input) noexcept
    {
        std::regex pattern("^[1-2]$");
        return regex_match(input, pattern);
    }

    [[nodiscard]] static bool IsValidMainSerializationChoice(const std::string& input) noexcept
    {
        std::regex pattern("^[1-2]$");
        return regex_match(input, pattern);
    }

    [[nodiscard]] static bool IsValidMainDifficultyChoice(const std::string& input) noexcept
    {
        std::regex pattern("^[1-3]$");
        return regex_match(input, pattern);
    }

    [[nodiscard]] static bool IsValidMenuChoice(const std::string& input) noexcept
    {
        std::regex pattern("^[0-7]$");
        return regex_match(input, pattern);
    }

    [[nodiscard]] static bool IsValidItemChoice(const std::string& input) noexcept
    {
        std::regex pattern("^[0-6]$");
        return regex_match(input, pattern);
    }

    [[nodiscard]] static bool IsValidYesNo(const std::string& input) noexcept
    {
        std::regex pattern("^[0-1]$");
        return regex_match(input, pattern);
    }

    [[nodiscard]] static bool IsValidDifficultyChoice(const std::string& input) noexcept
    {
        std::regex pattern("^[0-2]$");
        return regex_match(input, pattern);
    }

    [[nodiscard]] static bool IsValidSerializationChoice(const std::string& input) noexcept
    {
        std::regex pattern("^[0-1]$");
        return regex_match(input, pattern);
    }

    [[nodiscard]] static std::string GetValidatedInput(const std::string& prompt,
        bool (*validator)(const std::string&)) noexcept
    {
        #ifdef _WIN32
            while (_kbhit()) _getch();

            std::cout << prompt << std::flush;
            std::string input = "";
            while (true)
            {
                if (_kbhit())
                {
                    char charInput = _getch();
                    if (charInput == 13)
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
                    else if (charInput == 8 && !input.empty())
                    {
                        input.pop_back();
                        std::cout << "\b \b";
                    }
                    else if (charInput >= 32 && charInput < 127)
                    {
                        input += charInput;
                        std::cout << charInput;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
            }
        #else
            std::cout << prompt << std::flush;
            std::string input = "";
            while (true)
            {
                std::getline(std::cin, input);
                if (validator(input)) 
                { 
                    return input;
                }
                else { std::cout << "Nieprawidlowy wybor. Sprobuj ponownie: "; }
            }
        #endif
    }
};
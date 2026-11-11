#pragma once

#include "GameConfig.h"
#include <algorithm>
#include <cctype>
#include <string_view>

class InputValidator final
{
public:
    InputValidator() = delete;

    [[nodiscard]]
    static constexpr auto IsValidNumericInput(int input, int lowerBand, int upperBand) -> bool
    {
        return input >= lowerBand && input <= upperBand;
    }

    [[nodiscard]]
    static auto IsValidFileName(std::string_view filename) -> bool
    {
        return !filename.empty() && filename.size() <= GameConfig::MAX_FILENAME_LENGTH &&
               std::ranges::all_of(filename, [](char character) -> bool {
                   return std::isalnum(static_cast<unsigned char>(character)) || character == '_' || character == '-';
               });
    }
};

#include "ConsoleProvider.h"
#include "DecisionState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "InputValidator.h"
#include <cstdint>
#include <iostream>
#include <print>
#include <string>
#include <string_view>

ConsoleProvider::ConsoleProvider(DecisionState& decision, const GameLoopState& gameLoop)
    : m_decision(decision), m_gameLoop(gameLoop)
{
}

auto ConsoleProvider::InputDifficultyLevel() -> void
{
    std::print("Your choice (0 - 2): ");
    const auto input = GetValidatedInput(0, 2, InputValidator::IsValidNumericInput);
    m_decision.SetDifficultyChoice(static_cast<GameEnums::Difficulty>(input));
}

auto ConsoleProvider::InputSerializationType() -> void
{
    std::print("Your choice (0 - 1): ");
    const auto input = GetValidatedInput(0, 1, InputValidator::IsValidNumericInput);
    m_decision.SetSerializationChoice(static_cast<GameEnums::SerializationFormat>(input));
}

auto ConsoleProvider::InputItemChoice() -> void
{
    std::print("Your choice (0 - 6): ");
    const auto input = GetValidatedInput(0, 6, InputValidator::IsValidNumericInput);
    m_decision.SetItemChoice(static_cast<GameEnums::ItemType>(input));
}

auto ConsoleProvider::InputRestartChoice() -> void
{
    std::print("Your choice (0 - 1): ");
    const auto input = GetValidatedInput(0, 1, InputValidator::IsValidNumericInput);
    m_decision.SetYesNoChoice(static_cast<GameEnums::YesNo>(input));
}

auto ConsoleProvider::InputMainChoice() -> void
{
    std::print("Your choice (0 - 7): ");
    const auto input = GetValidatedInput(0, 7, InputValidator::IsValidNumericInput);
    m_decision.SetMainChoice(static_cast<GameEnums::MainChoice>(input));
}

auto ConsoleProvider::InputFilenameChoice() -> void
{
    using namespace GameEnums;
    std::print("Enter file name: ");
    const auto input = GetValidatedInput(InputValidator::IsValidFileName);
    m_decision.SetFilename(input);
    const auto action = m_gameLoop.GetCurrentMenu() == Window::SAVE_MENU ? MainChoice::SAVE : MainChoice::LOAD;
    m_decision.SetMainChoice(action);
}

auto ConsoleProvider::InputValidationFail() -> void
{
    std::print("Invalid choice. Try again: ");
    std::cout.flush();
}

auto ConsoleProvider::GetValidatedInput(bool (*validator)(std::string_view)) -> std::string
{
    std::string input;
    while (true)
    {
        std::getline(std::cin, input);
        if (validator(input))
        {
            return input;
        }
        InputValidationFail();
    }
}

auto ConsoleProvider::GetValidatedInput(int lowerBand, int upperBand, bool (*validator)(int, int, int)) -> uint8_t
{
    std::string input;
    while (true)
    {
        constexpr auto FIRST = 0U;
        std::getline(std::cin, input);
        if (input.size() == 1 && input[FIRST] >= '0' && input[FIRST] <= '9')
        {
            const int value = input[FIRST] - '0';
            if (validator(value, lowerBand, upperBand))
            {
                return static_cast<uint8_t>(value);
            }
        }
        InputValidationFail();
    }
}

auto ConsoleProvider::GetInput() -> void
{
    switch (m_gameLoop.GetCurrentMenu())
    {
    case GameEnums::Window::DIFFICULTY_MENU:
        InputDifficultyLevel();
        break;
    case GameEnums::Window::INVENTORY_MENU:
        InputItemChoice();
        break;
    case GameEnums::Window::SAVE_MENU:
    case GameEnums::Window::LOAD_MENU:
        InputFilenameChoice();
        break;
    case GameEnums::Window::SERIALIZATION_MENU:
        InputSerializationType();
        break;
    case GameEnums::Window::RESTART_MENU:
        InputRestartChoice();
        break;
    default:
    case GameEnums::Window::MAIN_MENU:
        InputMainChoice();
        break;
    }
}

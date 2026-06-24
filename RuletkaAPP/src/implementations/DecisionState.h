#pragma once
#include "GameEnums.h"
#include <cstdint>

class DecisionState
{
private:
    int8_t choice = GameEnums::NO_CHOICE;
    int8_t previousChoice = GameEnums::EXIT;
    uint8_t currentMenu = GameEnums::MAIN_MENU;
public:
    DecisionState() = default;

    DecisionState(const DecisionState&) = delete;
    DecisionState& operator=(const DecisionState&) = delete;

    DecisionState(DecisionState&&) = delete;
    DecisionState& operator=(DecisionState&&) = delete;

    void Reset()
    {
        choice = GameEnums::NO_CHOICE;
        previousChoice = GameEnums::EXIT;
        currentMenu = GameEnums::MAIN_MENU;
    }

    void SetChoice(int8_t newChoice)
    {
        previousChoice = choice;
        choice = newChoice;
    }

    void SetPreviousChoice(int8_t newPreviousChoice) { previousChoice = newPreviousChoice; }

    void SetCurrentMenu(uint8_t newMenu) { currentMenu = newMenu; }

    [[nodiscard]] int8_t GetChoice() const noexcept { return choice; }

    [[nodiscard]] int8_t GetPreviousChoice() const noexcept { return previousChoice; }

    [[nodiscard]] uint8_t GetCurrentMenu() const noexcept { return currentMenu; }

    ~DecisionState() = default;
};
#pragma once

#include "GameEnums.h"

class GameLoopState final
{
private:
    GameEnums::PlayerType m_starter = GameEnums::PlayerType::HUMAN;
    GameEnums::YesNo m_isInRestartMenu = GameEnums::YesNo::NO;
    GameEnums::YesNo m_isRunning = GameEnums::YesNo::YES;
    GameEnums::Window m_currentMenu = GameEnums::Window::MAIN_MENU;
    GameEnums::YesNo m_renderFlag = GameEnums::YesNo::YES;

public:
    auto Reset() noexcept -> void;
    auto SetStarter(GameEnums::PlayerType newStarter) noexcept -> void;
    auto SetIsInRestartMenu(GameEnums::YesNo newState) noexcept -> void;
    auto SetStateOfGameLoop(GameEnums::YesNo newState) noexcept -> void;
    auto RandomizeStarter() -> void;
    auto SetCurrentMenu(GameEnums::Window newMenu) noexcept -> void;
    auto SetRenderFlag(GameEnums::YesNo newRenderFlag) noexcept -> void;

    [[nodiscard]]
    auto GetRenderFlag() const noexcept -> GameEnums::YesNo;
    [[nodiscard]]
    auto GetIsInRestartMenu() const noexcept -> GameEnums::YesNo;
    [[nodiscard]]
    auto GetStateOfGameLoop() const noexcept -> GameEnums::YesNo;
    [[nodiscard]]
    auto GetStarter() const noexcept -> GameEnums::PlayerType;
    [[nodiscard]]
    auto GetCurrentMenu() const noexcept -> GameEnums::Window;
};

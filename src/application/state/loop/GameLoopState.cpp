#include "GameLoopState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "RNG.h"
#include <cstdint>

auto GameLoopState::Reset() noexcept -> void
{
    m_starter = GameEnums::PlayerType::HUMAN;
    m_isOnePlayerAlive = GameEnums::YesNo::NO;
    m_isRunning = GameEnums::YesNo::YES;
    m_currentMenu = GameEnums::Window::MAIN_MENU;
    m_renderFlag = GameEnums::YesNo::YES;
}

auto GameLoopState::SetRenderFlag(GameEnums::YesNo newRenderFlag) noexcept -> void
{
    m_renderFlag = newRenderFlag;
}

auto GameLoopState::SetStarter(GameEnums::PlayerType newStarter) noexcept -> void
{
    m_starter = newStarter;
}

auto GameLoopState::SetIsOnePlayerAlive(GameEnums::YesNo newState) noexcept -> void
{
    m_isOnePlayerAlive = newState;
}

auto GameLoopState::SetStateOfGameLoop(GameEnums::YesNo newState) noexcept -> void
{
    m_isRunning = newState;
}

auto GameLoopState::RandomizeStarter() -> void
{
    const auto value = RNG::GetRN<uint8_t>(0U, GameConfig::MAX_PLAYERS);
    m_starter = static_cast<GameEnums::PlayerType>(value);
}

auto GameLoopState::SetCurrentMenu(GameEnums::Window newMenu) noexcept -> void
{
    m_currentMenu = newMenu;
}

auto GameLoopState::GetRenderFlag() const noexcept -> GameEnums::YesNo
{
    return m_renderFlag;
}

[[nodiscard]]
auto GameLoopState::GetIsOnePlayerAlive() const noexcept -> GameEnums::YesNo
{
    return m_isOnePlayerAlive;
}

[[nodiscard]]
auto GameLoopState::GetStateOfGameLoop() const noexcept -> GameEnums::YesNo
{
    return m_isRunning;
}

[[nodiscard]]
auto GameLoopState::GetStarter() const noexcept -> GameEnums::PlayerType
{
    return m_starter;
}

[[nodiscard]]
auto GameLoopState::GetCurrentMenu() const noexcept -> GameEnums::Window
{
    return m_currentMenu;
}

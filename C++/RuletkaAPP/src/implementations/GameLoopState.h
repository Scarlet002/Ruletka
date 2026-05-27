#pragma once
#include "GameEnums.h"
#include "GameConfig.h"
#include "RNG.h"
#include <cstdint>

class GameLoopState
{
private:
    uint8_t starter = GameEnums::HUMAN;
    bool isOnePlayerAlive = false;
    bool isRunning = true;
public:
    GameLoopState() = default;

    GameLoopState(const GameLoopState&) = delete;
    GameLoopState& operator=(const GameLoopState&) = delete;

    GameLoopState(GameLoopState&&) = delete;
    GameLoopState& operator=(GameLoopState&&) = delete;

    void Reset()
    {
        starter = GameEnums::HUMAN;
        isOnePlayerAlive = false;
        isRunning = true;
    }

    void SetStarter(uint8_t newStarter) { starter = newStarter; }

    void SetIsOnePlayerAlive(bool newState) { isOnePlayerAlive = newState; }

    void SetStateOfGameLoop(bool newState) { isRunning = newState; }

    [[nodiscard]] bool GetIsOnePlayerAlive() const noexcept { return isOnePlayerAlive; }

    [[nodiscard]] bool GetStateOfGameLoop() const noexcept { return isRunning; }

    [[nodiscard]] uint8_t GetStarter() const noexcept { return starter; }

    [[nodiscard]] uint8_t RandomizeStarter() noexcept { return starter = RNG::GetRN<uint8_t>(0, GameConfig::maxPlayers); }

    ~GameLoopState() = default;
};
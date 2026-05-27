#pragma once
#include "GameConfig.h"
#include <cstdint>

class AIState
{
private:
    int8_t difficulty = GameConfig::defaultDifficulty;
    uint8_t recentDifficulty = GameConfig::defaultDifficulty;
public:
    AIState() = default;

    AIState(const AIState&) = delete;
    AIState& operator=(const AIState&) = delete;

    AIState(AIState&&) = delete;
    AIState& operator=(AIState&&) = delete;

    void Reset()
    {
        difficulty = GameConfig::defaultDifficulty;
        recentDifficulty = GameConfig::defaultDifficulty;
    }

    void SetDifficulty(int8_t newDifficulty) { difficulty = newDifficulty; }

    void SetRecentDifficulty(uint8_t newDifficulty) { recentDifficulty = newDifficulty; }

    [[nodiscard]] int8_t GetDifficulty() const noexcept { return difficulty; }

    [[nodiscard]] uint8_t GetRecentDifficulty() const noexcept { return recentDifficulty; }

    ~AIState() = default;
};
#pragma once

#include "GameConfig.h"
#include "GameEnums.h"

class AIState final
{
private:
    GameEnums::Difficulty m_difficulty = GameConfig::DEFAULT_DIFFICULTY;

public:
    auto Reset() noexcept -> void;
    auto SetDifficulty(GameEnums::Difficulty newDifficulty) noexcept -> void;

    [[nodiscard]]
    auto GetDifficulty() const noexcept -> GameEnums::Difficulty;
};

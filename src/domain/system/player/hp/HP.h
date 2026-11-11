#pragma once

#include "GameConfig.h"
#include <cstdint>

class HP final
{
private:
    uint8_t m_currentHP = GameConfig::MAX_PLAYER_HP;

public:
    auto SetHP(uint8_t newHP) noexcept -> void;
    auto LoseHP(uint8_t damage) noexcept -> void;
    auto RegainHP() noexcept -> void;
    auto ResetHP() noexcept -> void;

    [[nodiscard]]
    auto GetHP() const noexcept -> uint8_t;
};

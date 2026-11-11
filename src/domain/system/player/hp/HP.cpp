#include "HP.h"
#include "GameConfig.h"
#include <cstdint>

auto HP::SetHP(uint8_t newHP) noexcept -> void
{
    if (newHP >= GameConfig::MAX_PLAYER_HP)
    {
        m_currentHP = GameConfig::MAX_PLAYER_HP;
    }
    else
    {
        m_currentHP = newHP;
    }
}

auto HP::LoseHP(uint8_t damage) noexcept -> void
{
    if (m_currentHP <= damage)
    {
        m_currentHP = GameConfig::MIN_PLAYER_HP;
    }
    else
    {
        m_currentHP -= damage;
    }
}

auto HP::RegainHP() noexcept -> void
{
    if (m_currentHP < GameConfig::MAX_PLAYER_HP)
    {
        m_currentHP++;
    }
}

auto HP::ResetHP() noexcept -> void
{
    m_currentHP = GameConfig::MAX_PLAYER_HP;
}

auto HP::GetHP() const noexcept -> uint8_t
{
    return m_currentHP;
}

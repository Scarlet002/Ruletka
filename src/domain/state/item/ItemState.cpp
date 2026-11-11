#include "ItemState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include <cstdint>

auto ItemState::Reset() noexcept -> void
{
    m_damage = GameConfig::DEFAULT_DAMAGE;
    m_wereHandCuffsUsed = GameEnums::YesNo::NO;
    m_wasMagnifierUsed = GameEnums::YesNo::NO;
    m_wasCellPhoneUsed = GameEnums::YesNo::NO;
    m_wasInverterUsed = GameEnums::YesNo::NO;
}

auto ItemState::ResetDamage() noexcept -> void
{
    m_damage = GameConfig::DEFAULT_DAMAGE;
}

auto ItemState::SetDamage(uint8_t newDamage) noexcept -> void
{
    if (newDamage <= GameConfig::SAW_DAMAGE && newDamage > 0U)
    {
        m_damage = newDamage;
    }
}

auto ItemState::SetStateOfHandCuffs(GameEnums::YesNo newState) noexcept -> void
{
    m_wereHandCuffsUsed = newState;
}

auto ItemState::SetStateOfMagnifier(GameEnums::YesNo newState) noexcept -> void
{
    m_wasMagnifierUsed = newState;
}

auto ItemState::SetStateOfCellPhone(GameEnums::YesNo newState) noexcept -> void
{
    m_wasCellPhoneUsed = newState;
}

auto ItemState::SetStateOfInverter(GameEnums::YesNo newState) noexcept -> void
{
    m_wasInverterUsed = newState;
}

[[nodiscard]]
auto ItemState::GetDamage() const noexcept -> uint8_t
{
    return m_damage;
}

[[nodiscard]]
auto ItemState::GetStateOfHandCuffs() const noexcept -> GameEnums::YesNo
{
    return m_wereHandCuffsUsed;
}

[[nodiscard]]
auto ItemState::GetStateOfMagnifier() const noexcept -> GameEnums::YesNo
{
    return m_wasMagnifierUsed;
}

[[nodiscard]]
auto ItemState::GetStateOfCellPhone() const noexcept -> GameEnums::YesNo
{
    return m_wasCellPhoneUsed;
}

[[nodiscard]]
auto ItemState::GetStateOfInverter() const noexcept -> GameEnums::YesNo
{
    return m_wasInverterUsed;
}

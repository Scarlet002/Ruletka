#pragma once

#include "GameConfig.h"
#include "GameEnums.h"
#include <cstdint>

class ItemState final
{
private:
    uint8_t m_damage = GameConfig::DEFAULT_DAMAGE;
    GameEnums::YesNo m_wereHandCuffsUsed = GameEnums::YesNo::NO;
    GameEnums::YesNo m_wasMagnifierUsed = GameEnums::YesNo::NO;
    GameEnums::YesNo m_wasCellPhoneUsed = GameEnums::YesNo::NO;
    GameEnums::YesNo m_wasInverterUsed = GameEnums::YesNo::NO;

public:
    auto Reset() noexcept -> void;
    auto ResetDamage() noexcept -> void;
    auto SetDamage(uint8_t newDamage) noexcept -> void;
    auto SetStateOfHandCuffs(GameEnums::YesNo newState) noexcept -> void;
    auto SetStateOfMagnifier(GameEnums::YesNo newState) noexcept -> void;
    auto SetStateOfCellPhone(GameEnums::YesNo newState) noexcept -> void;
    auto SetStateOfInverter(GameEnums::YesNo newState) noexcept -> void;

    [[nodiscard]]
    auto GetDamage() const noexcept -> uint8_t;
    [[nodiscard]]
    auto GetStateOfHandCuffs() const noexcept -> GameEnums::YesNo;
    [[nodiscard]]
    auto GetStateOfMagnifier() const noexcept -> GameEnums::YesNo;
    [[nodiscard]]
    auto GetStateOfCellPhone() const noexcept -> GameEnums::YesNo;
    [[nodiscard]]
    auto GetStateOfInverter() const noexcept -> GameEnums::YesNo;
};

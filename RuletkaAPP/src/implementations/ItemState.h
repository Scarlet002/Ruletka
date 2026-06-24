#pragma once
#include "GameConfig.h"
#include "GameEnums.h"
#include <cstdint>

class ItemState
{
private:
    uint8_t damage = GameConfig::defaultDamage;
    bool wereHandCuffsUsed = GameEnums::ITEM_NOT_USED;
    bool wasMagnifierUsed = GameEnums::ITEM_NOT_USED;
    bool wasCellPhoneUsed = GameEnums::ITEM_NOT_USED;
public:
    ItemState() = default;

    ItemState(const ItemState&) = delete;
    ItemState& operator=(const ItemState&) = delete;

    ItemState(ItemState&&) = delete;
    ItemState& operator=(ItemState&&) = delete;

    void Reset()
    {
        damage = GameConfig::defaultDamage;
        wereHandCuffsUsed = GameEnums::ITEM_NOT_USED;
        wasMagnifierUsed = GameEnums::ITEM_NOT_USED;
        wasCellPhoneUsed = GameEnums::ITEM_NOT_USED;
    }

    void ResetDamage() { damage = GameConfig::defaultDamage; }

    void SetDamage(uint8_t newDamage) { damage = newDamage; }

    void SetStateOfHandCuffs(bool newState) { wereHandCuffsUsed = newState; }

    void SetStateOfMagnifier(bool newState) { wasMagnifierUsed = newState; };

    void SetStateOfCellPhone(bool newState) { wasCellPhoneUsed = newState; };

    [[nodiscard]] uint8_t GetDamage() const noexcept { return damage; }

    [[nodiscard]] bool GetStateOfHandCuffs() const noexcept { return wereHandCuffsUsed; }

    [[nodiscard]] bool GetStateOfMagnifier() const noexcept { return wasMagnifierUsed; }

    [[nodiscard]] bool GetStateOfCellPhone() const noexcept { return wasCellPhoneUsed; }

    ~ItemState() = default;
};
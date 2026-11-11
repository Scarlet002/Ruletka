#pragma once

#include "GameEnums.h"
#include <cstdint>
#include <unordered_map>

class Inventory final
{
private:
    std::unordered_map<GameEnums::ItemType, uint8_t> m_items;

public:
    auto GetRandomItems() -> void;
    auto UseItem(GameEnums::ItemType itemType) -> void;
    auto ResetInventory() -> void;
    auto AddItemType(GameEnums::ItemType itemType, uint8_t itemCount) -> void;
    auto SetItemCount(GameEnums::ItemType itemType, uint8_t newItemCount) -> void;

    [[nodiscard]]
    auto GetItemCount(GameEnums::ItemType itemType) const noexcept -> uint8_t;
    [[nodiscard]]
    auto GetItemsCount() const noexcept -> uint8_t;
};

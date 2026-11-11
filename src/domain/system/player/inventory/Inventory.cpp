#include "Inventory.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "RNG.h"
#include <cstdint>
#include <utility>

auto Inventory::UseItem(GameEnums::ItemType itemType) -> void
{
    const auto iterator = m_items.find(itemType);
    if (iterator != m_items.end() && iterator->second > GameConfig::MIN_ITEMS)
    {
        iterator->second--;
    }
}

auto Inventory::GetRandomItems() -> void
{
    using namespace GameConfig;
    if (GetItemsCount() < MAX_ITEMS)
    {
        for (auto iteration = 0UZ; iteration < GameConfig::MAX_ITEMS_GAINED; ++iteration)
        {
            const auto value = RNG::GetRN(MIN_ITEM_TYPE_RNG, MAX_ITEM_TYPE_RNG);
            const auto itemType = static_cast<GameEnums::ItemType>(value);
            const auto iterator = m_items.find(itemType);
            if (iterator != m_items.end() && iterator->second < MAX_ITEMS)
            {
                iterator->second++;
            }
        }
    }
}

auto Inventory::ResetInventory() -> void
{
    for (auto& item : m_items)
    {
        item.second = GameConfig::MIN_ITEMS;
    }
}

auto Inventory::AddItemType(GameEnums::ItemType itemType, uint8_t itemCount) -> void
{
    if (m_items.contains(itemType))
    {
        return;
    }

    const auto newTotal = GetItemsCount() + itemCount;
    if (std::cmp_less_equal(newTotal, GameConfig::MAX_ITEMS))
    {
        m_items[itemType] = itemCount;
    }
}

auto Inventory::SetItemCount(GameEnums::ItemType itemType, uint8_t newItemCount) -> void
{
    if (newItemCount > GameConfig::MAX_ITEMS)
    {
        return;
    }

    const auto newTotal = static_cast<uint8_t>(GetItemsCount() - GetItemCount(itemType) + newItemCount);
    if (newTotal <= GameConfig::MAX_ITEMS)
    {
        m_items[itemType] = newItemCount;
    }
}

auto Inventory::GetItemCount(GameEnums::ItemType itemType) const noexcept -> uint8_t
{
    const auto iterator = m_items.find(itemType);
    return (iterator != m_items.end()) ? iterator->second : GameConfig::MIN_ITEMS;
}

auto Inventory::GetItemsCount() const noexcept -> uint8_t
{
    auto total = GameConfig::MIN_ITEMS;
    for (const auto& item : m_items)
    {
        total += item.second;
    }
    return total;
}

#include "GameConfig.h"
#include "GameEnums.h"
#include "Inventory.h"
#include <gtest/gtest.h>

namespace
{
inline auto InitializeInventory(Inventory& inventory) -> void
{
    for (const auto& item : GameConfig::ITEM_TYPES)
    {
        inventory.AddItemType(item.second, GameConfig::MIN_ITEMS);
    }
}
} // namespace

TEST(InventoryTESTS, GetItemsCountReturnsCorrectNumbers)
{
    auto inventory = Inventory();
    InitializeInventory(inventory);
    constexpr auto ITEM_COUNT = 1U;
    constexpr auto EXPECTED_RETURN = 2U;
    inventory.SetItemCount(GameEnums::ItemType::BEER, ITEM_COUNT);
    inventory.SetItemCount(GameEnums::ItemType::SAW, ITEM_COUNT);

    EXPECT_EQ(inventory.GetItemsCount(), EXPECTED_RETURN);
}

TEST(InventoryTESTS, SetItemCountAndGetItemCountSetsAndReturnsItemCount)
{
    auto inventory = Inventory();
    InitializeInventory(inventory);
    constexpr auto ITEM_COUNT = 1U;
    constexpr auto EXPECTED_RETURN = 1U;
    inventory.SetItemCount(GameEnums::ItemType::BEER, ITEM_COUNT);

    EXPECT_EQ(inventory.GetItemCount(GameEnums::ItemType::BEER), EXPECTED_RETURN);
}

TEST(InventoryTESTS, SetItemCountDoesNotExceedMax)
{
    auto inventory = Inventory();
    InitializeInventory(inventory);
    constexpr auto ITEM_COUNT = 100U;
    inventory.SetItemCount(GameEnums::ItemType::BEER, ITEM_COUNT);

    EXPECT_EQ(inventory.GetItemCount(GameEnums::ItemType::BEER), GameConfig::MIN_ITEMS);
}

TEST(InventoryTESTS, ResetInventorySetsEveryItemCountToDefault)
{
    auto inventory = Inventory();
    InitializeInventory(inventory);
    constexpr auto ITEM_COUNT = 3U;

    for (const auto& item : GameConfig::ITEM_TYPES)
    {
        inventory.SetItemCount(item.second, ITEM_COUNT);
    }

    inventory.ResetInventory();

    for (const auto& item : GameConfig::ITEM_TYPES)
    {
        EXPECT_EQ(inventory.GetItemCount(item.second), GameConfig::MIN_ITEMS);
    }
}

TEST(InventoryTESTS, GetRandomItemsAddsItemIfConditionsAreMet)
{
    auto inventory = Inventory();
    InitializeInventory(inventory);
    constexpr auto ITEMS_COUNT = 2U;
    constexpr auto EXPECTED_RETURN = ITEMS_COUNT + 1U;
    inventory.SetItemCount(GameEnums::ItemType::BEER, ITEMS_COUNT);
    inventory.GetRandomItems();

    EXPECT_EQ(inventory.GetItemsCount(), EXPECTED_RETURN);
}

TEST(InventoryTESTS, GetRandomItemsDoesNotAddIfInventoryIsFull)
{
    auto inventory = Inventory();
    InitializeInventory(inventory);
    constexpr auto ITEM_COUNT = GameConfig::MAX_ITEMS;
    inventory.SetItemCount(GameEnums::ItemType::BEER, ITEM_COUNT);
    inventory.GetRandomItems();

    EXPECT_EQ(inventory.GetItemsCount(), GameConfig::MAX_ITEMS);
}

TEST(InventoryTESTS, UseItemDecrementsItemCount)
{
    auto inventory = Inventory();
    InitializeInventory(inventory);
    constexpr auto ITEM_COUNT = GameConfig::MAX_ITEMS;
    constexpr auto EXPECTED_RETURN = ITEM_COUNT - 1U;
    inventory.SetItemCount(GameEnums::ItemType::BEER, ITEM_COUNT);
    inventory.UseItem(GameEnums::ItemType::BEER);

    EXPECT_EQ(inventory.GetItemsCount(), EXPECTED_RETURN);
}

TEST(InventoryTESTS, UseItemDoesNotDecrementItemCountIfThereIsNoItems)
{
    auto inventory = Inventory();
    InitializeInventory(inventory);
    constexpr auto ITEM_COUNT = GameConfig::MIN_ITEMS;
    inventory.SetItemCount(GameEnums::ItemType::BEER, ITEM_COUNT);
    inventory.UseItem(GameEnums::ItemType::BEER);

    EXPECT_EQ(inventory.GetItemsCount(), GameConfig::MIN_ITEMS);
}

TEST(InventoryTESTS, AddItemTypeAddsNewItem)
{
    auto inventory = Inventory();
    inventory.AddItemType(GameEnums::ItemType::SAW, GameConfig::MAX_ITEMS);

    EXPECT_EQ(inventory.GetItemCount(GameEnums::ItemType::SAW), GameConfig::MAX_ITEMS);
    EXPECT_EQ(inventory.GetItemCount(GameEnums::ItemType::BEER), GameConfig::MIN_ITEMS);
}

TEST(InventoryTESTS, CloneReturnsNewInstanceWithSameItemCount)
{
    auto inventory = Inventory();
    InitializeInventory(inventory);
    inventory.SetItemCount(GameEnums::ItemType::SAW, GameConfig::MAX_ITEMS_GAINED);
    inventory.SetItemCount(GameEnums::ItemType::MAGNIFIER, GameConfig::MAX_ITEMS_GAINED);
    const auto itemCount = inventory.GetItemsCount();
    const auto clonedInventory = inventory;
    EXPECT_NE(&clonedInventory, &inventory);
    EXPECT_EQ(clonedInventory.GetItemsCount(), itemCount);
}

TEST(InventoryTESTS, SetItemCountAllowsDecreasing)
{
    auto inventory = Inventory();
    InitializeInventory(inventory);
    inventory.SetItemCount(GameEnums::ItemType::BEER, GameConfig::MAX_ITEMS);

    inventory.SetItemCount(GameEnums::ItemType::BEER, 2U);

    EXPECT_EQ(inventory.GetItemCount(GameEnums::ItemType::BEER), 2U);
}

TEST(InventoryTESTS, SetItemCountToZeroResetsItem)
{
    auto inventory = Inventory();
    InitializeInventory(inventory);
    inventory.SetItemCount(GameEnums::ItemType::BEER, 3U);

    inventory.SetItemCount(GameEnums::ItemType::BEER, 0U);

    EXPECT_EQ(inventory.GetItemCount(GameEnums::ItemType::BEER), GameConfig::MIN_ITEMS);
}

TEST(InventoryTESTS, AddItemTypeWithDuplicateKeyDoesNotOverwrite)
{
    auto inventory = Inventory();
    inventory.AddItemType(GameEnums::ItemType::SAW, 2U);
    inventory.AddItemType(GameEnums::ItemType::SAW, 4U);

    EXPECT_EQ(inventory.GetItemCount(GameEnums::ItemType::SAW), 2U);
}

TEST(InventoryTESTS, AddItemTypeWithTooManyItemsIsRejected)
{
    auto inventory = Inventory();
    constexpr auto NEW_ITEM_COUNT = 10U;
    inventory.AddItemType(GameEnums::ItemType::SAW, NEW_ITEM_COUNT);

    EXPECT_EQ(inventory.GetItemCount(GameEnums::ItemType::SAW), GameConfig::MIN_ITEMS);
}

TEST(InventoryTESTS, GetItemCountForUnknownTypeReturnsMinItems)
{
    auto inventory = Inventory();
    EXPECT_EQ(inventory.GetItemCount(GameEnums::ItemType::NOTHING), GameConfig::MIN_ITEMS);
}

TEST(InventoryTESTS, UseItemWithNothingDoesNothing)
{
    auto inventory = Inventory();
    InitializeInventory(inventory);

    EXPECT_NO_THROW(inventory.UseItem(GameEnums::ItemType::NOTHING));
    EXPECT_EQ(inventory.GetItemsCount(), GameConfig::MIN_ITEMS);
}

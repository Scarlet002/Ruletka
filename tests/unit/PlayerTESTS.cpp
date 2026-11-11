#include "GameConfig.h"
#include "GameEnums.h"
#include "HP.h"
#include "Inventory.h"
#include "Player.h"
#include <gtest/gtest.h>
#include <utility>

namespace
{
inline auto ArrangePlayer() -> Player
{
    auto playerHP = HP();
    auto playerInventory = Inventory();
    constexpr auto NAME = "xyz";
    constexpr auto TYPE = GameEnums::PlayerType::COMPUTER;
    return {NAME, playerHP, std::move(playerInventory), TYPE};
}
} // namespace

TEST(PlayerTESTS, IsAliveReturnsNoIfNotAlive)
{
    auto player = ArrangePlayer();
    auto& playerHP = player.GetHP();
    playerHP.SetHP(GameConfig::MIN_PLAYER_HP);

    EXPECT_EQ(player.IsAlive(), GameEnums::YesNo::NO);
}

TEST(PlayerTESTS, IsAliveReturnsYesIfAlive)
{
    auto player = ArrangePlayer();
    auto& playerHP = player.GetHP();
    playerHP.SetHP(GameConfig::MAX_PLAYER_HP);

    EXPECT_EQ(player.IsAlive(), GameEnums::YesNo::YES);
}

TEST(PlayerTESTS, SetNameAndGetNameSetsAndReturnsName)
{
    auto player = ArrangePlayer();
    constexpr auto NAME = "xyz";

    player.SetName(NAME);

    EXPECT_EQ(player.GetName(), NAME);
}

TEST(PlayerTESTS, SetTypeAndGetTypeSetsAndReturnsType)
{
    auto player = ArrangePlayer();
    constexpr auto TYPE = GameEnums::PlayerType::COMPUTER;

    player.SetType(TYPE);

    EXPECT_EQ(player.GetType(), TYPE);
}

TEST(PlayerTESTS, GetTypeStringReturnsTypeInString)
{
    auto player = ArrangePlayer();
    constexpr auto TYPE = GameEnums::PlayerType::COMPUTER;
    constexpr auto TYPE_STRING = "computer";

    player.SetType(TYPE);

    EXPECT_EQ(player.GetTypeString(), TYPE_STRING);
}

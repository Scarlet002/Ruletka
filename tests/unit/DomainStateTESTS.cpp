#include "DomainState.h"
#include "GameBuilder.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "HP.h"
#include "Inventory.h"
#include "ItemState.h"
#include "Magazine.h"
#include "Player.h"
#include <array>
#include <gtest/gtest.h>

namespace
{
using BufferMagazine = std::array<GameEnums::MagazineChamber, GameConfig::MAX_BULLETS>;
} //namespace

TEST(DomainStateTESTS, ConstructorStoresPlayersWithCorrectTypes)
{
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");

    EXPECT_EQ(domain.GetHuman().GetName(), "Human");
    EXPECT_EQ(domain.GetComputer().GetName(), "Computer");
    EXPECT_EQ(domain.GetHuman().GetType(), GameEnums::PlayerType::HUMAN);
    EXPECT_EQ(domain.GetComputer().GetType(), GameEnums::PlayerType::COMPUTER);
}

TEST(DomainStateTESTS, GetHumanReturnsMutableRef)
{
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    auto& human = domain.GetHuman();
    human.SetName("Changed");

    EXPECT_EQ(domain.GetHuman().GetName(), "Changed");
}

TEST(DomainStateTESTS, GetComputerReturnsMutableRef)
{
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    auto& computer = domain.GetComputer();
    computer.SetName("Changed");

    EXPECT_EQ(domain.GetComputer().GetName(), "Changed");
}

TEST(DomainStateTESTS, GetHumanHPReflectsChangesViaPlayer)
{
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    domain.GetHumanHP().LoseHP(2U);

    EXPECT_EQ(domain.GetHumanHP().GetHP(), GameConfig::MAX_PLAYER_HP - 2U);
    EXPECT_EQ(domain.GetHuman().GetHP().GetHP(), GameConfig::MAX_PLAYER_HP - 2U);
}

TEST(DomainStateTESTS, GetComputerHPReflectsChangesViaPlayer)
{
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    domain.GetComputerHP().LoseHP(3U);

    EXPECT_EQ(domain.GetComputerHP().GetHP(), GameConfig::MAX_PLAYER_HP - 3U);
    EXPECT_EQ(domain.GetComputer().GetHP().GetHP(), GameConfig::MAX_PLAYER_HP - 3U);
}

TEST(DomainStateTESTS, GetHumanInventoryReflectsChanges)
{
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    domain.GetHumanInventory().SetItemCount(GameEnums::ItemType::BEER, 2U);

    EXPECT_EQ(domain.GetHumanInventory().GetItemCount(GameEnums::ItemType::BEER), 2U);
    EXPECT_EQ(domain.GetHuman().GetInventory().GetItemCount(GameEnums::ItemType::BEER), 2U);
}

TEST(DomainStateTESTS, GetMagazineReturnsFreshEmptyMagazine)
{
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");

    EXPECT_TRUE(domain.GetMagazine().IsEmpty());
    EXPECT_EQ(domain.GetMagazine().GetMagazineSize(), GameConfig::MIN_BULLETS);
}

TEST(DomainStateTESTS, GetMagazineReturnsMutableRef)
{
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    constexpr auto BUFFER = BufferMagazine{GameEnums::MagazineChamber::LIVE};
    domain.GetMagazine().SetMagazine({.m_magazine = BUFFER, .m_head = 0U});

    EXPECT_FALSE(domain.GetMagazine().IsEmpty());
    EXPECT_EQ(domain.GetMagazine().GetMagazineSize(), 1U);
}

TEST(DomainStateTESTS, GetItemStateReturnsMutableRef)
{
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    domain.GetItemState().SetDamage(GameConfig::SAW_DAMAGE);

    EXPECT_EQ(domain.GetItemState().GetDamage(), GameConfig::SAW_DAMAGE);
}

TEST(DomainStateTESTS, ConstOverloadsCompileAndReturnConst)
{
    const auto domain = GameBuilder::BuildDomainState("Human", "Computer");

    const auto& human = domain.GetHuman();
    const auto& computer = domain.GetComputer();
    const auto& humanInventory = domain.GetHumanInventory();
    const auto& humanHP = domain.GetHumanHP();
    const auto& computerHP = domain.GetComputerHP();
    const auto& magazine = domain.GetMagazine();
    const auto& itemState = domain.GetItemState();

    EXPECT_EQ(human.GetName(), "Human");
    EXPECT_EQ(computer.GetName(), "Computer");
    EXPECT_EQ(humanInventory.GetItemsCount(), GameConfig::MIN_ITEMS);
    EXPECT_EQ(humanHP.GetHP(), GameConfig::MAX_PLAYER_HP);
    EXPECT_EQ(computerHP.GetHP(), GameConfig::MAX_PLAYER_HP);
    EXPECT_TRUE(magazine.IsEmpty());
    EXPECT_EQ(itemState.GetDamage(), GameConfig::DEFAULT_DAMAGE);
}

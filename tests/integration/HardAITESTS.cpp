#include "DecisionState.h"
#include "DomainState.h"
#include "GameBuilder.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "HP.h"
#include "HardAI.h"
#include "Inventory.h"
#include "Magazine.h"
#include "TestsHelper.hpp"
#include <array>
#include <gtest/gtest.h>

namespace
{
using BufferMagazine = std::array<GameEnums::MagazineChamber, GameConfig::MAX_BULLETS>;
} //namespace

TEST(HardAITESTS, GetInputReturnsShootChoiceWhenConditionsAreMet)
{
    auto domain = GameBuilder::BuildDomainState("Player1", "Player2");
    auto decison = DecisionState();
    auto hardAI = HardAI(decison, domain);
    const auto newMagazine = BufferMagazine{GameEnums::MagazineChamber::LIVE};
    domain.GetMagazine().SetMagazine({.m_magazine = newMagazine, .m_head = 0U});

    hardAI.GetInput();

    TestsHelper::AssertForAI(decison, GameEnums::MainChoice::SHOOT);
}

TEST(HardAITESTS, GetInputReturnsHealChoiceWhenConditionsAreMet)
{
    auto domain = GameBuilder::BuildDomainState("Player1", "Player2");
    auto decison = DecisionState();
    auto hardAI = HardAI(decison, domain);
    const auto newMagazine = BufferMagazine{GameEnums::MagazineChamber::BLANK};
    domain.GetMagazine().SetMagazine({.m_magazine = newMagazine, .m_head = 0U});

    hardAI.GetInput();

    TestsHelper::AssertForAI(decison, GameEnums::MainChoice::HEAL);
}

TEST(HardAITESTS, GetInputReturnsUseItemChoiceWhenConditionsAreMetForSawUsage)
{
    auto domain = GameBuilder::BuildDomainState("Player1", "Player2");
    auto decison = DecisionState();
    auto hardAI = HardAI(decison, domain);
    const auto newMagazine = BufferMagazine{GameEnums::MagazineChamber::LIVE};
    domain.GetMagazine().SetMagazine({.m_magazine = newMagazine, .m_head = 0U});
    constexpr auto EXPECTED_RETURN = 1U;
    domain.GetComputerInventory().SetItemCount(GameEnums::ItemType::SAW, EXPECTED_RETURN);

    hardAI.GetInput();

    TestsHelper::AssertForAI(decison, GameEnums::MainChoice::USE_ITEM);
}

TEST(HardAITESTS, GetInputReturnsUseItemChoiceWhenConditionsAreMetForBeerUsage)
{
    auto domain = GameBuilder::BuildDomainState("Player1", "Player2");
    auto decison = DecisionState();
    auto hardAI = HardAI(decison, domain);
    const auto newMagazine = BufferMagazine{GameEnums::MagazineChamber::BLANK, GameEnums::MagazineChamber::BLANK};
    domain.GetMagazine().SetMagazine({.m_magazine = newMagazine, .m_head = 0U});
    constexpr auto EXPECTED_RETURN = 1U;
    domain.GetComputerInventory().SetItemCount(GameEnums::ItemType::BEER, EXPECTED_RETURN);
    domain.GetHumanHP().SetHP(GameConfig::MAX_PLAYER_HP);
    domain.GetComputerHP().SetHP(GameConfig::MAX_PLAYER_HP);

    hardAI.GetInput();

    TestsHelper::AssertForAI(decison, GameEnums::MainChoice::USE_ITEM);
}

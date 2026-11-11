#include "DecisionState.h"
#include "DomainState.h"
#include "GameBuilder.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "HP.h"
#include "Inventory.h"
#include "Magazine.h"
#include "NormalAI.h"
#include "TestsHelper.hpp"
#include <array>
#include <gtest/gtest.h>

namespace
{
using BufferMagazine = std::array<GameEnums::MagazineChamber, GameConfig::MAX_BULLETS>;
} //namespace

TEST(NormalAITESTS, GetInputReturnsShootActionWhenConditionsAreMet)
{
    auto domain = GameBuilder::BuildDomainState("Player1", "Player2");
    auto decison = DecisionState();
    auto normalAI = NormalAI(decison, domain);
    const auto newMagazine = BufferMagazine{GameEnums::MagazineChamber::LIVE};
    auto& magazine = domain.GetMagazine();

    magazine.SetMagazine({.m_magazine = newMagazine, .m_head = 0U});
    magazine.CalculateHitProbability();

    normalAI.GetInput();

    TestsHelper::AssertForAI(decison, GameEnums::MainChoice::SHOOT);
}

TEST(NormalAITESTS, GetInputReturnsHealActionWhenConditionsAreMet)
{
    auto domain = GameBuilder::BuildDomainState("Player1", "Player2");
    auto decison = DecisionState();
    auto normalAI = NormalAI(decison, domain);
    const auto newMagazine = BufferMagazine{GameEnums::MagazineChamber::BLANK};
    auto& magazine = domain.GetMagazine();
    magazine.SetMagazine({.m_magazine = newMagazine, .m_head = 0U});
    magazine.CalculateHitProbability();

    normalAI.GetInput();

    TestsHelper::AssertForAI(decison, GameEnums::MainChoice::HEAL);
}

TEST(NormalAITESTS, GetInputReturnsUseItemChoiceWhenConditionsAreMetForSawUsage)
{
    auto domain = GameBuilder::BuildDomainState("Player1", "Player2");
    auto decison = DecisionState();
    auto normalAI = NormalAI(decison, domain);
    const auto newMagazine = BufferMagazine{GameEnums::MagazineChamber::LIVE};
    auto& magazine = domain.GetMagazine();
    magazine.SetMagazine({.m_magazine = newMagazine, .m_head = 0U});
    magazine.CalculateHitProbability();
    constexpr auto EXPECTED_RETURN = 1U;
    domain.GetComputerInventory().SetItemCount(GameEnums::ItemType::SAW, EXPECTED_RETURN);

    normalAI.GetInput();

    TestsHelper::AssertForAI(decison, GameEnums::MainChoice::USE_ITEM);
}

TEST(NormalAITESTS, GetInputReturnsUseItemChoiceWhenConditionsAreMetForBeerUsage)
{
    auto domain = GameBuilder::BuildDomainState("Player1", "Player2");
    auto decison = DecisionState();
    auto normalAI = NormalAI(decison, domain);
    const auto newMagazine = BufferMagazine{GameEnums::MagazineChamber::BLANK, GameEnums::MagazineChamber::BLANK};
    auto& magazine = domain.GetMagazine();
    magazine.SetMagazine({.m_magazine = newMagazine, .m_head = 0U});
    magazine.CalculateHitProbability();
    constexpr auto EXPECTED_RETURN = 1U;
    domain.GetComputerInventory().SetItemCount(GameEnums::ItemType::BEER, EXPECTED_RETURN);
    domain.GetHumanHP().SetHP(GameConfig::MAX_PLAYER_HP);
    domain.GetComputerHP().SetHP(GameConfig::MAX_PLAYER_HP);

    normalAI.GetInput();

    TestsHelper::AssertForAI(decison, GameEnums::MainChoice::USE_ITEM);
}

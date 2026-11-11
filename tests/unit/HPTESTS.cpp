#include "GameConfig.h"
#include "HP.h"
#include <cstdint>
#include <gtest/gtest.h>

TEST(HPTESTS, SetHPAndGetHPSetsAndReturnsHP)
{
    constexpr auto NEW_HP = 3U;
    auto hpSystem = HP();
    hpSystem.SetHP(NEW_HP);
    EXPECT_EQ(hpSystem.GetHP(), NEW_HP);
}

TEST(HPTESTS, SetHPAndGetHPZeroHPSetCheck)
{
    constexpr auto NEW_HP = GameConfig::MIN_PLAYER_HP;
    auto hpSystem = HP();
    hpSystem.SetHP(NEW_HP);
    EXPECT_EQ(hpSystem.GetHP(), NEW_HP);
}

TEST(HPTESTS, LoseHPReducesHP)
{
    constexpr auto DAMAGE = 2U;
    auto hpSystem = HP();
    const auto initialHp = hpSystem.GetHP();
    hpSystem.LoseHP(DAMAGE);
    EXPECT_EQ(hpSystem.GetHP(), initialHp - DAMAGE);
}

TEST(HPTESTS, LoseHPDamageIsZero)
{
    constexpr auto DAMAGE = 0U;
    auto hpSystem = HP();
    const auto initialHp = hpSystem.GetHP();
    hpSystem.LoseHP(DAMAGE);
    EXPECT_EQ(hpSystem.GetHP(), initialHp - DAMAGE);
}

TEST(HPTESTS, RegainHPIncreasesHP)
{
    constexpr auto DAMAGE = 2U;
    constexpr auto HP_GAIN = 1U;
    auto hpSystem = HP();
    const auto initialHp = hpSystem.GetHP();
    hpSystem.LoseHP(DAMAGE);
    hpSystem.RegainHP();
    EXPECT_EQ(hpSystem.GetHP(), initialHp - DAMAGE + HP_GAIN);
}

TEST(HPTESTS, ResetHPResetsHP)
{
    constexpr auto DAMAGE = 2U;
    auto hpSystem = HP();
    const auto initialHp = hpSystem.GetHP();
    hpSystem.LoseHP(DAMAGE);
    hpSystem.ResetHP();
    EXPECT_EQ(hpSystem.GetHP(), initialHp);
}

TEST(HPTESTS, CloneReturnsNewInstanceWithSameHP)
{
    auto hpSystem = HP();
    constexpr auto DAMAGE = 2U;
    hpSystem.LoseHP(DAMAGE);
    const auto expectedReturn = hpSystem.GetHP();
    const auto clonedHpSystem = hpSystem;
    EXPECT_NE(&clonedHpSystem, &hpSystem);
    EXPECT_EQ(clonedHpSystem.GetHP(), expectedReturn);
}

TEST(HPTESTS, LoseHPDoesNotGoBelowZero)
{
    auto hpSystem = HP();
    const auto damage = static_cast<uint8_t>(hpSystem.GetHP() + 10U);
    hpSystem.LoseHP(damage);
    EXPECT_EQ(hpSystem.GetHP(), GameConfig::MIN_PLAYER_HP);
}

TEST(HPTESTS, RegainHPDoesNotExceedHPLimit)
{
    constexpr auto LOOPS = 10U;
    auto hpSystem = HP();
    for (auto index = 0UZ; index < LOOPS; ++index)
    {
        hpSystem.RegainHP();
    }
    EXPECT_EQ(hpSystem.GetHP(), GameConfig::MAX_PLAYER_HP);
}

TEST(HPTESTS, SetHPDoesNotExceedHPLimit)
{
    auto hpSystem = HP();
    hpSystem.SetHP(GameConfig::MAX_PLAYER_HP + GameConfig::MAX_PLAYER_HP);
    EXPECT_EQ(hpSystem.GetHP(), GameConfig::MAX_PLAYER_HP);
}

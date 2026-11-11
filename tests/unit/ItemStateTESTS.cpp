#include "GameConfig.h"
#include "GameEnums.h"
#include "ItemState.h"
#include <gtest/gtest.h>

TEST(ItemStateTESTS, DefaultConstructorInitializesDefaults)
{
    const auto state = ItemState();
    EXPECT_EQ(state.GetDamage(), GameConfig::DEFAULT_DAMAGE);
    EXPECT_EQ(state.GetStateOfHandCuffs(), GameEnums::YesNo::NO);
    EXPECT_EQ(state.GetStateOfMagnifier(), GameEnums::YesNo::NO);
    EXPECT_EQ(state.GetStateOfCellPhone(), GameEnums::YesNo::NO);
    EXPECT_EQ(state.GetStateOfInverter(), GameEnums::YesNo::NO);
}

TEST(ItemStateTESTS, SetDamageAndGetDamageWork)
{
    auto state = ItemState();
    state.SetDamage(GameConfig::SAW_DAMAGE);
    EXPECT_EQ(state.GetDamage(), GameConfig::SAW_DAMAGE);
}

TEST(ItemStateTESTS, SetDamageBackToDefaultWorks)
{
    auto state = ItemState();
    state.SetDamage(GameConfig::SAW_DAMAGE);
    state.SetDamage(GameConfig::DEFAULT_DAMAGE);
    EXPECT_EQ(state.GetDamage(), GameConfig::DEFAULT_DAMAGE);
}

TEST(ItemStateTESTS, SetStateOfHandCuffsAndGetWork)
{
    auto state = ItemState();
    state.SetStateOfHandCuffs(GameEnums::YesNo::YES);
    EXPECT_EQ(state.GetStateOfHandCuffs(), GameEnums::YesNo::YES);

    state.SetStateOfHandCuffs(GameEnums::YesNo::NO);
    EXPECT_EQ(state.GetStateOfHandCuffs(), GameEnums::YesNo::NO);
}

TEST(ItemStateTESTS, SetStateOfMagnifierAndGetWork)
{
    auto state = ItemState();
    state.SetStateOfMagnifier(GameEnums::YesNo::YES);
    EXPECT_EQ(state.GetStateOfMagnifier(), GameEnums::YesNo::YES);
}

TEST(ItemStateTESTS, SetStateOfCellPhoneAndGetWork)
{
    auto state = ItemState();
    state.SetStateOfCellPhone(GameEnums::YesNo::YES);
    EXPECT_EQ(state.GetStateOfCellPhone(), GameEnums::YesNo::YES);
}

TEST(ItemStateTESTS, SetStateOfInverterAndGetWork)
{
    auto state = ItemState();
    state.SetStateOfInverter(GameEnums::YesNo::YES);
    EXPECT_EQ(state.GetStateOfInverter(), GameEnums::YesNo::YES);
}

TEST(ItemStateTESTS, ResetRestoresAllDefaults)
{
    auto state = ItemState();
    state.SetDamage(GameConfig::SAW_DAMAGE);
    state.SetStateOfHandCuffs(GameEnums::YesNo::YES);
    state.SetStateOfMagnifier(GameEnums::YesNo::YES);
    state.SetStateOfCellPhone(GameEnums::YesNo::YES);
    state.SetStateOfInverter(GameEnums::YesNo::YES);

    state.Reset();

    EXPECT_EQ(state.GetDamage(), GameConfig::DEFAULT_DAMAGE);
    EXPECT_EQ(state.GetStateOfHandCuffs(), GameEnums::YesNo::NO);
    EXPECT_EQ(state.GetStateOfMagnifier(), GameEnums::YesNo::NO);
    EXPECT_EQ(state.GetStateOfCellPhone(), GameEnums::YesNo::NO);
    EXPECT_EQ(state.GetStateOfInverter(), GameEnums::YesNo::NO);
}

TEST(ItemStateTESTS, ResetDamageOnlyResetsDamage)
{
    auto state = ItemState();
    state.SetDamage(GameConfig::SAW_DAMAGE);
    state.SetStateOfHandCuffs(GameEnums::YesNo::YES);
    state.SetStateOfMagnifier(GameEnums::YesNo::YES);
    state.SetStateOfCellPhone(GameEnums::YesNo::YES);
    state.SetStateOfInverter(GameEnums::YesNo::YES);

    state.ResetDamage();

    EXPECT_EQ(state.GetDamage(), GameConfig::DEFAULT_DAMAGE);
    EXPECT_EQ(state.GetStateOfHandCuffs(), GameEnums::YesNo::YES);
    EXPECT_EQ(state.GetStateOfMagnifier(), GameEnums::YesNo::YES);
    EXPECT_EQ(state.GetStateOfCellPhone(), GameEnums::YesNo::YES);
    EXPECT_EQ(state.GetStateOfInverter(), GameEnums::YesNo::YES);
}

TEST(ItemStateTESTS, CopyPreservesAllFields)
{
    auto state = ItemState();
    state.SetDamage(GameConfig::SAW_DAMAGE);
    state.SetStateOfHandCuffs(GameEnums::YesNo::YES);

    const auto copy = state;

    EXPECT_EQ(copy.GetDamage(), state.GetDamage());
    EXPECT_EQ(copy.GetStateOfHandCuffs(), state.GetStateOfHandCuffs());
}

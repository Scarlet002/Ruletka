#include "DecisionState.h"
#include "EasyAI.h"
#include "GameEnums.h"
#include "TestsHelper.h"
#include <gtest/gtest.h>

TEST(EasyAITESTS, GetInputReturnsHealOrShootChoice)
{
    using GameEnums::MainChoice;
    auto decisionState = DecisionState();
    auto easyAI = EasyAI(decisionState);

    easyAI.GetInput();

    TestsHelper::AssertForAI(decisionState, MainChoice::HEAL, MainChoice::SHOOT);
}

#pragma once

#include "DecisionState.h"
#include <gtest/gtest.h>
#include <optional>
#include <type_traits>

class TestsHelper final
{
public:
    TestsHelper() = delete;

    template <typename... Args>
        requires(sizeof...(Args) > 0U) && (std::is_enum_v<Args> && ...)
    static void AssertForAI(const DecisionState& decision, const Args... assertedChoice)
    {
        const auto choice = decision.GetMainChoice();
        ASSERT_TRUE(choice.has_value());
        // NOLINTNEXTLINE(bugprone-unchecked-optional-access)
        const auto result = choice.value();
        EXPECT_TRUE((... || (result == assertedChoice)));
    }
};

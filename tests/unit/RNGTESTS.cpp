#include "RNG.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(RNGTESTS, GetRNIsInRange)
{
    constexpr auto MIN = 10U;
    constexpr auto MAX = 14U;
    constexpr auto SAMPLE = 10000UZ;

    for (auto index = 0UZ; index < SAMPLE; ++index)
    {
        const auto value = RNG::GetRN(MIN, MAX);
        EXPECT_GE(value, MIN);
        EXPECT_LE(value, MAX);
    }
}

TEST(RNGTESTS, GetRNReturnLowerbandIfLowerbandEqualsUpperband)
{
    constexpr auto MIN = 10U;
    constexpr auto MAX = MIN;

    const auto result = RNG::GetRN(MIN, MAX);

    EXPECT_EQ(result, MIN);
}

TEST(RNGTESTS, GetRNThrowInvalidArgument)
{
    constexpr auto MIN = 10U;
    constexpr auto MAX = 1U;

    EXPECT_THROW(static_cast<void>(RNG::GetRN(MIN, MAX)), std::invalid_argument);
}

#include "GameConfig.h"
#include "GameEnums.h"
#include "Magazine.h"
#include <algorithm>
#include <array>
#include <gtest/gtest.h>
#include <stdexcept>

namespace
{
using BufferMagazine = std::array<GameEnums::MagazineChamber, GameConfig::MAX_BULLETS>;
} //namespace

TEST(ShotgunMagazineTESTS, CloneCopiesWholeMagazineWithAllPropertiesAndState)
{
    using namespace GameEnums;
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{
        GameEnums::MagazineChamber::LIVE,  GameEnums::MagazineChamber::LIVE,  GameEnums::MagazineChamber::BLANK,
        GameEnums::MagazineChamber::BLANK, GameEnums::MagazineChamber::BLANK,
    };

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});
    const auto magazineClone = magazine;

    EXPECT_TRUE(std::ranges::equal(magazine.GetMagazine().m_magazine, magazineClone.GetMagazine().m_magazine));
    EXPECT_EQ(magazine.GetMagazineSize(), magazineClone.GetMagazineSize());
    EXPECT_EQ(magazine.GetBullets(MagazineChamber::LIVE), magazineClone.GetBullets(MagazineChamber::LIVE));
    EXPECT_EQ(magazine.GetBullets(MagazineChamber::BLANK), magazineClone.GetBullets(MagazineChamber::BLANK));
    EXPECT_FLOAT_EQ(magazine.GetHitProbability(), magazineClone.GetHitProbability());
}

TEST(ShotgunMagazineTESTS, GetBulletsReturnsCorrectValueWhenFullAreCounted)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{
        GameEnums::MagazineChamber::LIVE,  GameEnums::MagazineChamber::LIVE,  GameEnums::MagazineChamber::BLANK,
        GameEnums::MagazineChamber::BLANK, GameEnums::MagazineChamber::BLANK,
    };

    constexpr auto EXPECTED_RETURN = 2U;

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});

    EXPECT_EQ(magazine.GetBullets(GameEnums::MagazineChamber::LIVE), EXPECTED_RETURN);
}

TEST(ShotgunMagazineTESTS, GetBulletsReturnsCorrectValueWhenEmptyAreCounted)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{
        GameEnums::MagazineChamber::LIVE,  GameEnums::MagazineChamber::LIVE,  GameEnums::MagazineChamber::BLANK,
        GameEnums::MagazineChamber::BLANK, GameEnums::MagazineChamber::BLANK,
    };
    constexpr auto EXPECTED_RETURN = 3U;

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});

    EXPECT_EQ(magazine.GetBullets(GameEnums::MagazineChamber::BLANK), EXPECTED_RETURN);
}

TEST(ShotgunMagazineTESTS, GetBulletsReturnsCorrectValueWhenFullAreCountedInEmptyMagazine)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{};
    constexpr auto EXPECTED_RETURN = 0U;

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});

    EXPECT_EQ(magazine.GetBullets(GameEnums::MagazineChamber::LIVE), EXPECTED_RETURN);
}

TEST(ShotgunMagazineTESTS, ReloadReloadsMagazineObeyingConfigLimitsCorrectly)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{};

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});
    magazine.Reload();

    const auto magazineSize = magazine.GetMagazineSize();
    EXPECT_FALSE(std::ranges::equal(magazine.GetMagazine().m_magazine, NEW_MAGAZINE));
    EXPECT_GE(magazineSize, GameConfig::MIN_BULLETS_RNG);
    EXPECT_LE(magazineSize, GameConfig::MAX_BULLETS_RNG);
}

TEST(ShotgunMagazineTESTS, DecreaseBulletCountIfMagazineIsNotEmpty)
{
    auto magazine = Magazine();
    auto newMagazine = BufferMagazine{
        GameEnums::MagazineChamber::LIVE,
        GameEnums::MagazineChamber::BLANK,
        GameEnums::MagazineChamber::LIVE,
        GameEnums::MagazineChamber::LIVE,
    };

    magazine.SetMagazine({.m_magazine = newMagazine, .m_head = 0U});
    newMagazine[magazine.GetMagazine().m_head] = GameEnums::MagazineChamber::EMPTY;
    magazine.DecreaseBulletCount();

    EXPECT_TRUE(std::ranges::equal(magazine.GetMagazine().m_magazine, newMagazine));
}

TEST(ShotgunMagazineTESTS, DecreaseBulletCountIfMagazineHasOneBullet)
{
    auto magazine = Magazine();
    auto newMagazine = BufferMagazine{GameEnums::MagazineChamber::LIVE};

    magazine.SetMagazine({.m_magazine = newMagazine, .m_head = 0U});
    newMagazine[magazine.GetMagazine().m_head] = GameEnums::MagazineChamber::EMPTY;
    magazine.DecreaseBulletCount();

    EXPECT_TRUE(std::ranges::equal(magazine.GetMagazine().m_magazine, newMagazine));
}

TEST(ShotgunMagazineTESTS, DecreaseBulletCountDoesNotThrowIfMagazineIsEmpty)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{};

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});

    EXPECT_NO_THROW(magazine.DecreaseBulletCount());
}

TEST(ShotgunMagazineTESTS, IsEmptyReturnsTrueWhenMagazineIsEmpty)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{};

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});

    EXPECT_TRUE(magazine.IsEmpty());
}

TEST(ShotgunMagazineTESTS, IsEmptyReturnsFalseWhenMagazineIsNotEmpty)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{GameEnums::MagazineChamber::LIVE, GameEnums::MagazineChamber::BLANK};

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});

    EXPECT_FALSE(magazine.IsEmpty());
}

TEST(ShotgunMagazineTESTS, SetMagazineAndGetMagazineWorkTogetherCorrectly)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{
        GameEnums::MagazineChamber::LIVE,
        GameEnums::MagazineChamber::BLANK,
        GameEnums::MagazineChamber::LIVE,
    };

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});

    EXPECT_TRUE(std::ranges::equal(magazine.GetMagazine().m_magazine, NEW_MAGAZINE));
}

TEST(ShotgunMagazineTESTS, InvertMagazineChamberWhenBulletIsEmpty)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{GameEnums::MagazineChamber::BLANK};

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});
    magazine.InvertBulletType();

    EXPECT_TRUE(magazine.CheckMagazineChamber(magazine.GetMagazine().m_head) == GameEnums::MagazineChamber::LIVE);
}

TEST(ShotgunMagazineTESTS, InvertMagazineChamberWhenBulletIsFull)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{GameEnums::MagazineChamber::LIVE};

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});
    magazine.InvertBulletType();

    EXPECT_TRUE(magazine.CheckMagazineChamber(magazine.GetMagazine().m_head) == GameEnums::MagazineChamber::BLANK);
}

TEST(ShotgunMagazineTESTS, InvertMagazineChamberWhenMagazineIsEmpty)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{};

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});
    magazine.InvertBulletType();

    EXPECT_TRUE(magazine.CheckMagazineChamber(magazine.GetMagazine().m_head) == GameEnums::MagazineChamber::EMPTY);
}

TEST(ShotgunMagazineTESTS, GetMagazineSizeReturnsCorrectValueWhenLive)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{
        GameEnums::MagazineChamber::LIVE,
        GameEnums::MagazineChamber::BLANK,
        GameEnums::MagazineChamber::LIVE,
    };

    constexpr auto SIZE = NEW_MAGAZINE.size() - std::ranges::count_if(NEW_MAGAZINE, [](const auto& bullet) -> auto {
                              return bullet == GameEnums::MagazineChamber::EMPTY;
                          });

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});

    EXPECT_EQ(magazine.GetMagazineSize(), SIZE);
}

TEST(ShotgunMagazineTESTS, CheckMagazineChamberReturnsCorrectValueTrueWhenBlank)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{GameEnums::MagazineChamber::BLANK};

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});

    EXPECT_FALSE(magazine.CheckMagazineChamber(magazine.GetMagazine().m_head) == GameEnums::MagazineChamber::LIVE);
}

TEST(ShotgunMagazineTESTS, CheckMagazineChamberReturnsCorrectValueTrue)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{GameEnums::MagazineChamber::LIVE};

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});

    EXPECT_TRUE(magazine.CheckMagazineChamber(magazine.GetMagazine().m_head) == GameEnums::MagazineChamber::LIVE);
}

TEST(ShotgunMagazineTESTS, CheckMagazineChamberDoesNotThrow)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{};

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});

    EXPECT_NO_THROW(static_cast<void>(magazine.CheckMagazineChamber(magazine.GetMagazine().m_head)));
}

TEST(ShotgunMagazineTESTS, SetHitProbabilityAndGetHitProbabilityWorkTogetherCorrectly)
{
    auto magazine = Magazine();
    constexpr auto EXPECTED_RETURN = 0.5;

    magazine.SetHitProbability(EXPECTED_RETURN);

    EXPECT_FLOAT_EQ(magazine.GetHitProbability(), EXPECTED_RETURN);
}

TEST(ShotgunMagazineTESTS, CalculateHitProbabilityReturns0WhenAllBulletsAreEmpty)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{
        GameEnums::MagazineChamber::BLANK,
        GameEnums::MagazineChamber::BLANK,
        GameEnums::MagazineChamber::BLANK,
        GameEnums::MagazineChamber::BLANK,
    };

    constexpr auto EXPECTED_RETURN = 0.0;

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});
    magazine.CalculateHitProbability();

    EXPECT_FLOAT_EQ(magazine.GetHitProbability(), EXPECTED_RETURN);
}

TEST(ShotgunMagazineTESTS, CalculateHitProbabilityReturnsPoint5WhenHalfBulletsAreFull)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{
        GameEnums::MagazineChamber::LIVE,
        GameEnums::MagazineChamber::BLANK,
        GameEnums::MagazineChamber::LIVE,
        GameEnums::MagazineChamber::BLANK,
    };
    constexpr auto EXPECTED_RETURN = 0.5;

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});
    magazine.CalculateHitProbability();

    EXPECT_FLOAT_EQ(magazine.GetHitProbability(), EXPECTED_RETURN);
}

TEST(ShotgunMagazineTESTS, CalculateHitProbabilityReturns1WhenAllBulletsAreFull)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{
        GameEnums::MagazineChamber::LIVE,
        GameEnums::MagazineChamber::LIVE,
        GameEnums::MagazineChamber::LIVE,
        GameEnums::MagazineChamber::LIVE,
    };
    constexpr auto EXPECTED_RETURN = 1.0;

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});
    magazine.CalculateHitProbability();

    EXPECT_FLOAT_EQ(magazine.GetHitProbability(), EXPECTED_RETURN);
}

TEST(ShotgunMagazineTESTS, CalculateHitProbabilityReturns0WhenMagazineIsEmpty)
{
    auto magazine = Magazine();
    constexpr auto NEW_MAGAZINE = BufferMagazine{};
    constexpr auto EXPECTED_RETURN = 0.0;

    magazine.SetMagazine({.m_magazine = NEW_MAGAZINE, .m_head = 0U});
    magazine.CalculateHitProbability();

    EXPECT_FLOAT_EQ(magazine.GetHitProbability(), EXPECTED_RETURN);
}

TEST(ShotgunMagazineTESTS, CalculateHitProbabilityResetsToZeroWhenMagazineBecomesEmpty)
{
    auto magazine = Magazine();
    constexpr auto FULL_MAGAZINE = BufferMagazine{GameEnums::MagazineChamber::LIVE};
    magazine.SetMagazine({.m_magazine = FULL_MAGAZINE, .m_head = 0U});
    magazine.CalculateHitProbability();
    EXPECT_FLOAT_EQ(magazine.GetHitProbability(), 1.0);

    constexpr auto EMPTY_MAGAZINE = BufferMagazine{};
    magazine.SetMagazine({.m_magazine = EMPTY_MAGAZINE, .m_head = 0U});
    magazine.CalculateHitProbability();

    EXPECT_FLOAT_EQ(magazine.GetHitProbability(), 0.0);
}

TEST(ShotgunMagazineTESTS, SetMagazineThrowsWhenHeadOutOfRange)
{
    auto magazine = Magazine();
    constexpr auto BUFFER = BufferMagazine{};

    EXPECT_THROW(magazine.SetMagazine({.m_magazine = BUFFER, .m_head = GameConfig::MAX_BULLETS}), std::out_of_range);
}

TEST(ShotgunMagazineTESTS, CheckMagazineChamberThrowsWhenIndexOutOfRange)
{
    const auto magazine = Magazine();

    EXPECT_THROW(static_cast<void>(magazine.CheckMagazineChamber(GameConfig::MAX_BULLETS)), std::out_of_range);
}

TEST(ShotgunMagazineTESTS, ReloadResetsHeadToZero)
{
    auto magazine = Magazine();
    constexpr auto BUFFER = BufferMagazine{GameEnums::MagazineChamber::LIVE, GameEnums::MagazineChamber::LIVE};
    magazine.SetMagazine({.m_magazine = BUFFER, .m_head = 1U});

    magazine.Reload();

    EXPECT_EQ(magazine.GetMagazine().m_head, GameConfig::MIN_BULLETS);
}

TEST(ShotgunMagazineTESTS, ReloadSetsSizeInRngRange)
{
    auto magazine = Magazine();
    constexpr auto SAMPLE = 100UZ;
    for (auto iteration = 0UZ; iteration < SAMPLE; ++iteration)
    {
        magazine.Reload();
        const auto size = magazine.GetMagazineSize();
        EXPECT_GE(size, GameConfig::MIN_BULLETS_RNG);
        EXPECT_LE(size, GameConfig::MAX_BULLETS_RNG);
    }
}

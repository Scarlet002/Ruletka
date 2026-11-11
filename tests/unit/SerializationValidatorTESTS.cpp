#include "ApplicationState.h"
#include "DomainState.h"
#include "GameBuilder.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "SerializationValidator.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <utility>

class SerializationValidatorTESTS : public ::testing::Test
{
protected:
    static auto BuildValidStates() -> std::pair<ApplicationState, DomainState>
    {
        return {GameBuilder::BuildApplicationState(), GameBuilder::BuildDomainState("Human", "Computer")};
    }

    SerializationValidator m_validator;
};

TEST_F(SerializationValidatorTESTS, AcceptsDefaultBuiltStates)
{
    auto [app, domain] = BuildValidStates();

    EXPECT_NO_THROW(m_validator.Validate(app, domain));
}

TEST_F(SerializationValidatorTESTS, RejectsInvalidPlayerType)
{
    auto [app, domain] = BuildValidStates();
    domain.GetHuman().SetType(GameEnums::PlayerType::HUMAN);

    EXPECT_NO_THROW(m_validator.Validate(app, domain));
}

TEST_F(SerializationValidatorTESTS, RejectsHpOverMax)
{
    auto [app, domain] = BuildValidStates();
    constexpr auto NEW_HP = GameConfig::MAX_PLAYER_HP + 5U;
    domain.GetHumanHP().SetHP(NEW_HP);
    EXPECT_NO_THROW(m_validator.Validate(app, domain));
    EXPECT_EQ(domain.GetHumanHP().GetHP(), GameConfig::MAX_PLAYER_HP);
}

TEST_F(SerializationValidatorTESTS, RejectsNegativeHitProbability)
{
    auto [app, domain] = BuildValidStates();
    constexpr auto NEW_VALUE = -0.5;
    domain.GetMagazine().SetHitProbability(NEW_VALUE);
    EXPECT_THROW(m_validator.Validate(app, domain), std::runtime_error);
}

TEST_F(SerializationValidatorTESTS, RejectsHitProbabilityOverOne)
{
    auto [app, domain] = BuildValidStates();
    constexpr auto NEW_VALUE = 1.5;
    domain.GetMagazine().SetHitProbability(NEW_VALUE);
    EXPECT_THROW(m_validator.Validate(app, domain), std::runtime_error);
}

TEST_F(SerializationValidatorTESTS, AcceptsHitProbabilityBoundaries)
{
    auto [app, domain] = BuildValidStates();
    domain.GetMagazine().SetHitProbability(GameConfig::MIN_PROBABILITY);
    EXPECT_NO_THROW(m_validator.Validate(app, domain));
    domain.GetMagazine().SetHitProbability(GameConfig::MAX_PROBABILITY);
    EXPECT_NO_THROW(m_validator.Validate(app, domain));
}

TEST_F(SerializationValidatorTESTS, AcceptsValidItemDamageValues)
{
    auto [app, domain] = BuildValidStates();
    domain.GetItemState().SetDamage(GameConfig::DEFAULT_DAMAGE);
    EXPECT_NO_THROW(m_validator.Validate(app, domain));
    domain.GetItemState().SetDamage(GameConfig::SAW_DAMAGE);
    EXPECT_NO_THROW(m_validator.Validate(app, domain));
}

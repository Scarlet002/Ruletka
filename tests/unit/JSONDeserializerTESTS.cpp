#include "ApplicationState.h"
#include "DomainState.h"
#include "GameBuilder.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "JSONDeserializer.h"
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <stdexcept>
#include <utility>

namespace
{
// NOLINTNEXTLINE(clang-diagnostic-padded)
class JSONDeserializerTESTS : public ::testing::Test
{
protected:
    JSONDeserializerTESTS()
        : m_app(GameBuilder::BuildApplicationState()), m_domain(GameBuilder::BuildDomainState("Human", "Computer"))
    {
    }

    ApplicationState m_app; // NOLINT(misc-non-private-member-variables-in-classes)
    DomainState m_domain;   // NOLINT(misc-non-private-member-variables-in-classes)
};

TEST_F(JSONDeserializerTESTS, DeserializeChoiceReturnsValueForValidKey)
{
    constexpr auto MAIN_CHOICE_VALUE = 1;
    const auto data = nlohmann::json{{"MainChoice", MAIN_CHOICE_VALUE}};
    const auto result = JSONDeserializer::DeserializeChoice<GameEnums::MainChoice>(data, "MainChoice");

    EXPECT_EQ(result, std::make_optional(GameEnums::MainChoice::SHOOT));
}

TEST_F(JSONDeserializerTESTS, DeserializeChoiceReturnsNulloptForMissingKey)
{
    const auto data = nlohmann::json::object();
    const auto result = JSONDeserializer::DeserializeChoice<GameEnums::MainChoice>(data, "MainChoice");

    EXPECT_EQ(result, std::nullopt);
}

TEST_F(JSONDeserializerTESTS, DeserializeChoiceReturnsNulloptForNonInteger)
{
    const auto data = nlohmann::json{{"MainChoice", "HEAL"}};
    const auto result = JSONDeserializer::DeserializeChoice<GameEnums::MainChoice>(data, "MainChoice");

    EXPECT_EQ(result, std::nullopt);
}

TEST_F(JSONDeserializerTESTS, DeserializeChoiceReturnsNulloptForSpecialValue)
{
    const auto nothing = std::to_underlying(GameEnums::SpecialValues::NOTHING);
    const auto data = nlohmann::json{{"ItemChoice", nothing}};
    const auto result = JSONDeserializer::DeserializeChoice<GameEnums::ItemType>(data, "ItemChoice");

    EXPECT_EQ(result, std::nullopt);
}

TEST_F(JSONDeserializerTESTS, DeserializePlayerParsesAllFields)
{
    constexpr auto EXPECTED_HP = 3;
    constexpr auto EXPECTED_HANDCUFFS = 2;
    constexpr auto EXPECTED_BEERS = 1;
    constexpr auto PLAYER_TYPE_HUMAN = 1;
    const auto data = nlohmann::json{
        {"human_name", "Jan"},
        {"human_type", PLAYER_TYPE_HUMAN},
        {"human_HP", EXPECTED_HP},
        {"human_handcuffs", EXPECTED_HANDCUFFS},
        {"human_beers", EXPECTED_BEERS},
        {"human_magnifiers", 0},
        {"human_saws", 0},
        {"human_cellphones", 0},
        {"human_inverters", 0},
    };
    auto& human = m_domain.GetHuman();

    JSONDeserializer::DeserializePlayer(data, human);

    EXPECT_EQ(human.GetName(), "Jan");
    EXPECT_EQ(human.GetType(), GameEnums::PlayerType::HUMAN);
    EXPECT_EQ(human.GetHP().GetHP(), EXPECTED_HP);
    EXPECT_EQ(human.GetInventory().GetItemCount(GameEnums::ItemType::HANDCUFFS), EXPECTED_HANDCUFFS);
    EXPECT_EQ(human.GetInventory().GetItemCount(GameEnums::ItemType::BEER), EXPECTED_BEERS);
}

TEST_F(JSONDeserializerTESTS, DeserializeMagazineParsesValidData)
{
    constexpr auto LIVE_BULLET = static_cast<int>(std::to_underlying(GameEnums::MagazineChamber::LIVE));
    constexpr auto BLANK_BULLET = static_cast<int>(std::to_underlying(GameEnums::MagazineChamber::BLANK));
    constexpr auto EMPTY_BULLET = static_cast<int>(std::to_underlying(GameEnums::MagazineChamber::EMPTY));
    constexpr auto EXPECTED_HEAD = 0U;
    constexpr auto EXPECTED_PROBABILITY = 0.5;
    const auto data = nlohmann::json{
        {"magazine",
         {
             BLANK_BULLET,
             LIVE_BULLET,
             BLANK_BULLET,
             EMPTY_BULLET,
             EMPTY_BULLET,
             EMPTY_BULLET,
             EMPTY_BULLET,
             EMPTY_BULLET,
         }},
        {"magazineHead", EXPECTED_HEAD},
        {"hitProbability", EXPECTED_PROBABILITY},
    };
    auto& magazine = m_domain.GetMagazine();

    JSONDeserializer::DeserializeMagazine(data, magazine);

    const auto restored = magazine.GetMagazine();
    EXPECT_EQ(restored.m_head, EXPECTED_HEAD);
    EXPECT_EQ(restored.m_magazine[0], GameEnums::MagazineChamber::BLANK);
    EXPECT_EQ(restored.m_magazine[1], GameEnums::MagazineChamber::LIVE);
    EXPECT_DOUBLE_EQ(magazine.GetHitProbability(), EXPECTED_PROBABILITY);
}

TEST_F(JSONDeserializerTESTS, DeserializeMagazineRejectsWrongArraySize)
{
    constexpr auto LIVE_BULLET = static_cast<int>(std::to_underlying(GameEnums::MagazineChamber::LIVE));
    constexpr auto BLANK_BULLET = static_cast<int>(std::to_underlying(GameEnums::MagazineChamber::BLANK));
    const auto data = nlohmann::json{
        {"magazine", {LIVE_BULLET, BLANK_BULLET}},
        {"magazineHead", 0},
    };
    auto& magazine = m_domain.GetMagazine();
    const auto originalHead = magazine.GetMagazine().m_head;

    EXPECT_NO_THROW(JSONDeserializer::DeserializeMagazine(data, magazine));
    EXPECT_EQ(magazine.GetMagazine().m_head, originalHead);
}

TEST_F(JSONDeserializerTESTS, DeserializeMagazineRejectsOutOfRangeHead)
{
    constexpr auto LIVE_BULLET = static_cast<int>(std::to_underlying(GameEnums::MagazineChamber::LIVE));
    constexpr auto BLANK_BULLET = static_cast<int>(std::to_underlying(GameEnums::MagazineChamber::BLANK));
    constexpr auto EMPTY_BULLET = static_cast<int>(std::to_underlying(GameEnums::MagazineChamber::EMPTY));
    constexpr auto OUT_OF_RANGE_HEAD = 99;
    const auto data = nlohmann::json{
        {"magazine",
         {
             LIVE_BULLET,
             BLANK_BULLET,
             EMPTY_BULLET,
             EMPTY_BULLET,
             EMPTY_BULLET,
             EMPTY_BULLET,
             EMPTY_BULLET,
             EMPTY_BULLET,
         }},
        {"magazineHead", OUT_OF_RANGE_HEAD},
    };
    auto& magazine = m_domain.GetMagazine();
    const auto originalHead = magazine.GetMagazine().m_head;

    EXPECT_NO_THROW(JSONDeserializer::DeserializeMagazine(data, magazine));
    EXPECT_EQ(magazine.GetMagazine().m_head, originalHead);
}

TEST_F(JSONDeserializerTESTS, DeserializeMagazineHandlesMissingKeysGracefully)
{
    const auto data = nlohmann::json::object();
    auto& magazine = m_domain.GetMagazine();

    EXPECT_NO_THROW(JSONDeserializer::DeserializeMagazine(data, magazine));
}

TEST_F(JSONDeserializerTESTS, DeserializeItemStateParsesAllFlags)
{
    constexpr auto EXPECTED_DAMAGE = 2;
    const auto data = nlohmann::json{
        {"damage", EXPECTED_DAMAGE}, {"wereHandCuffsUsed", 1}, {"wasMagnifierUsed", 1},
        {"wasCellPhoneUsed", 0},     {"wasInverterUsed", 1},
    };
    auto& itemState = m_domain.GetItemState();

    JSONDeserializer::DeserializeItemState(data, itemState);

    EXPECT_EQ(itemState.GetDamage(), EXPECTED_DAMAGE);
    EXPECT_EQ(itemState.GetStateOfHandCuffs(), GameEnums::YesNo::YES);
    EXPECT_EQ(itemState.GetStateOfMagnifier(), GameEnums::YesNo::YES);
    EXPECT_EQ(itemState.GetStateOfCellPhone(), GameEnums::YesNo::NO);
    EXPECT_EQ(itemState.GetStateOfInverter(), GameEnums::YesNo::YES);
}

TEST_F(JSONDeserializerTESTS, DeserializeGameLoopStateParsesFields)
{
    constexpr auto STARTER_COMPUTER = 0;
    constexpr auto MENU_INVENTORY = 2;
    const auto data = nlohmann::json{
        {"starter", STARTER_COMPUTER},
        {"isInRestartMenu", 1},
        {"stateOfGameLoop", 1},
        {"Menu", MENU_INVENTORY},
    };
    auto& loop = m_app.GetGameLoopState();

    JSONDeserializer::DeserializeGameLoopState(data, loop);

    EXPECT_EQ(loop.GetStarter(), GameEnums::PlayerType::COMPUTER);
    EXPECT_EQ(loop.GetIsInRestartMenu(), GameEnums::YesNo::YES);
    EXPECT_EQ(loop.GetCurrentMenu(), GameEnums::Window::INVENTORY_MENU);
}

TEST_F(JSONDeserializerTESTS, DeserializeAIStateParsesDifficulty)
{
    constexpr auto DIFFICULTY_HARD = 2;
    const auto data = nlohmann::json{{"difficulty", DIFFICULTY_HARD}};
    auto& aiState = m_app.GetAIState();

    JSONDeserializer::DeserializeAIState(data, aiState);

    EXPECT_EQ(aiState.GetDifficulty(), GameEnums::Difficulty::HARD);
}

TEST_F(JSONDeserializerTESTS, DeserializeDecisionStateParsesChoices)
{
    constexpr auto MAIN_CHOICE_SHOOT = 1;
    constexpr auto ITEM_CHOICE_MAGNIFIER = 3;
    constexpr auto DIFFICULTY_HARD = 2;
    constexpr auto YES = 1;
    constexpr auto UI_CONSOLE = 0;
    constexpr auto SERIALIZATION_JSON = 1;
    const auto data = nlohmann::json{
        {"MainChoice", MAIN_CHOICE_SHOOT},
        {"ItemChoice", ITEM_CHOICE_MAGNIFIER},
        {"DifficultyChoice", DIFFICULTY_HARD},
        {"YesNoChoice", YES},
        {"UIChoice", UI_CONSOLE},
        {"SerializationChoice", SERIALIZATION_JSON},
    };
    auto& decision = m_app.GetDecisionState();

    JSONDeserializer::DeserializeDecisionState(data, decision);

    EXPECT_EQ(decision.GetMainChoice(), std::make_optional(GameEnums::MainChoice::SHOOT));
    EXPECT_EQ(decision.GetItemChoice(), std::make_optional(GameEnums::ItemType::MAGNIFIER));
}

TEST_F(JSONDeserializerTESTS, DeserializeAllRejectsWrongVersion)
{
    const auto data = nlohmann::json{{"version", "0.0.1"}};

    EXPECT_THROW(JSONDeserializer::DeserializeAll(data, m_app, m_domain), std::runtime_error);
}

TEST_F(JSONDeserializerTESTS, DeserializeAllAcceptsCurrentVersion)
{
    const auto data = nlohmann::json{{"version", GameConfig::GAME_VERSION}};

    EXPECT_NO_THROW(JSONDeserializer::DeserializeAll(data, m_app, m_domain));
}

} // namespace

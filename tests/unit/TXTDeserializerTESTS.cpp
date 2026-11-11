#include "ApplicationState.h"
#include "DecisionState.h"
#include "DomainState.h"
#include "GameBuilder.h"
#include "GameEnums.h"
#include "Inventory.h"
#include "ItemState.h"
#include "Magazine.h"
#include "Player.h"
#include "TXTDeserializer.h"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

namespace
{

constexpr auto TEST_FILE = "test_txt_deserializer.tmp";

class TXTDeserializerTESTS : public ::testing::Test
{
protected:
    ApplicationState m_app = GameBuilder::BuildApplicationState();
    DomainState m_domain = GameBuilder::BuildDomainState("Human", "Computer");

    auto TearDown() -> void override
    {
        std::error_code errorCode;
        std::filesystem::remove(TEST_FILE, errorCode);
    }

    static auto WriteFile(std::string_view content) -> std::ifstream
    {
        std::ofstream out(TEST_FILE);
        out << content;
        out.close();
        return std::ifstream(TEST_FILE);
    }
};

TEST_F(TXTDeserializerTESTS, DeserializeChoiceReturnsValueForValidInput)
{
    auto stream = WriteFile("1");
    const auto result = TXTDeserializer::DeserializeChoice<GameEnums::MainChoice>(stream);

    EXPECT_EQ(result, std::make_optional(GameEnums::MainChoice::SHOOT));
}

TEST_F(TXTDeserializerTESTS, DeserializeChoiceReturnsNulloptForNothingValue)
{
    const auto nothing = std::to_underlying(GameEnums::SpecialValues::NOTHING);
    auto stream = WriteFile(std::to_string(nothing));
    const auto result = TXTDeserializer::DeserializeChoice<GameEnums::MainChoice>(stream);

    EXPECT_EQ(result, std::nullopt);
}

TEST_F(TXTDeserializerTESTS, DeserializePlayerParsesValidStream)
{
    constexpr auto EXPECTED_HP = 3;
    constexpr auto EXPECTED_HANDCUFFS = 2;
    constexpr auto EXPECTED_BEERS = 1;
    auto stream = WriteFile("Jan\n1\n3\n2\n1\n0\n0\n0\n0\n");
    auto& human = m_domain.GetHuman();

    TXTDeserializer::DeserializePlayer(stream, human);

    EXPECT_EQ(human.GetName(), "Jan");
    EXPECT_EQ(human.GetType(), GameEnums::PlayerType::HUMAN);
    EXPECT_EQ(human.GetHP().GetHP(), EXPECTED_HP);
    EXPECT_EQ(human.GetInventory().GetItemCount(GameEnums::ItemType::HANDCUFFS), EXPECTED_HANDCUFFS);
    EXPECT_EQ(human.GetInventory().GetItemCount(GameEnums::ItemType::BEER), EXPECTED_BEERS);
}

TEST_F(TXTDeserializerTESTS, DeserializePlayerFailsOnEmptyStream)
{
    auto stream = WriteFile("");
    auto& human = m_domain.GetHuman();

    TXTDeserializer::DeserializePlayer(stream, human);

    EXPECT_TRUE(stream.fail());
}

TEST_F(TXTDeserializerTESTS, DeserializeMagazineParsesValidStream)
{
    constexpr auto EXPECTED_HEAD = 2;
    constexpr auto EXPECTED_PROBABILITY = 0.5;
    auto stream = WriteFile("1 2 1 0 0 0 0 0\n2\n0.5\n");
    auto& magazine = m_domain.GetMagazine();

    TXTDeserializer::DeserializeMagazine(stream, magazine);

    const auto restored = magazine.GetMagazine();
    EXPECT_EQ(restored.m_head, EXPECTED_HEAD);
    EXPECT_DOUBLE_EQ(magazine.GetHitProbability(), EXPECTED_PROBABILITY);
}

TEST_F(TXTDeserializerTESTS, DeserializeItemStateParsesFlags)
{
    constexpr auto EXPECTED_DAMAGE = 2;
    auto stream = WriteFile("2 1 1 0 1\n");
    auto& itemState = m_domain.GetItemState();

    TXTDeserializer::DeserializeItemState(stream, itemState);

    EXPECT_EQ(itemState.GetDamage(), EXPECTED_DAMAGE);
    EXPECT_EQ(itemState.GetStateOfHandCuffs(), GameEnums::YesNo::YES);
    EXPECT_EQ(itemState.GetStateOfMagnifier(), GameEnums::YesNo::YES);
    EXPECT_EQ(itemState.GetStateOfCellPhone(), GameEnums::YesNo::NO);
    EXPECT_EQ(itemState.GetStateOfInverter(), GameEnums::YesNo::YES);
}

TEST_F(TXTDeserializerTESTS, DeserializeDecisionStateParsesChoices)
{
    auto stream = WriteFile("1 3 2 1 0 1\n");
    auto& decision = m_app.GetDecisionState();

    TXTDeserializer::DeserializeDecisionState(stream, decision);

    EXPECT_EQ(decision.GetMainChoice(), std::make_optional(GameEnums::MainChoice::SHOOT));
    EXPECT_EQ(decision.GetItemChoice(), std::make_optional(GameEnums::ItemType::MAGNIFIER));
}

TEST_F(TXTDeserializerTESTS, DeserializeDecisionStateParsesNothingAsNullopt)
{
    const auto nothing = std::to_underlying(GameEnums::SpecialValues::NOTHING);
    const auto line = std::to_string(nothing) + " " + std::to_string(nothing) + " " + std::to_string(nothing) + " " +
                      std::to_string(nothing) + " " + std::to_string(nothing) + " " + std::to_string(nothing) + "\n";
    auto stream = WriteFile(line);
    auto& decision = m_app.GetDecisionState();

    TXTDeserializer::DeserializeDecisionState(stream, decision);

    EXPECT_EQ(decision.GetMainChoice(), std::nullopt);
    EXPECT_EQ(decision.GetItemChoice(), std::nullopt);
}

} // namespace

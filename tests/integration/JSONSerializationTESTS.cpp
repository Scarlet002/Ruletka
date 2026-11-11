#include "ApplicationState.h"
#include "DomainState.h"
#include "GameBuilder.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "JSONDeserializer.h"
#include "JSONSerializer.h"
#include "SaveConfig.h"
#include "SerializationValidator.h"
#include <array>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <system_error>

class JSONSerializationTESTS : public ::testing::Test
{
protected:
    auto SetUp() -> void override
    {
        static_cast<void>(SaveConfig::CreateDirectoryIfNotExists(SaveConfig::GetSaveDirectory()));
    }

    auto TearDown() -> void override
    {
        std::error_code errorCode;
        std::filesystem::remove("data/saves/test_save.json", errorCode);
    }

    static auto BuildValidator() -> SerializationValidator
    {
        return {};
    }
};

TEST_F(JSONSerializationTESTS, SerializeCreatesFile)
{
    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    auto serializer = JSONSerializer();

    serializer.Serialize(app, domain, "test_save");

    EXPECT_TRUE(serializer.GetSerializationLog().empty());
    EXPECT_TRUE(std::filesystem::exists("data/saves/test_save.json"));
}

TEST_F(JSONSerializationTESTS, RoundTripPreservesPlayerFields)
{
    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");

    domain.GetHuman().GetHP().LoseHP(GameConfig::SAW_DAMAGE);
    domain.GetHumanInventory().SetItemCount(GameEnums::ItemType::SAW, 3);
    domain.GetHumanInventory().SetItemCount(GameEnums::ItemType::BEER, 1);

    auto serializer = JSONSerializer();
    serializer.Serialize(app, domain, "test_save");

    auto validator = BuildValidator();
    auto deserializer = JSONDeserializer(validator);
    auto app2 = GameBuilder::BuildApplicationState();
    auto domain2 = GameBuilder::BuildDomainState("Player", "AI");
    deserializer.Deserialize(app2, domain2, "test_save");

    EXPECT_TRUE(deserializer.GetDeserializationLog().empty());
    EXPECT_EQ(domain2.GetHuman().GetName(), "Human");
    EXPECT_EQ(domain2.GetHuman().GetType(), GameEnums::PlayerType::HUMAN);
    EXPECT_EQ(domain2.GetHuman().GetHP().GetHP(), GameConfig::MAX_PLAYER_HP - 2);
    EXPECT_EQ(domain2.GetHumanInventory().GetItemCount(GameEnums::ItemType::SAW), 3);
    EXPECT_EQ(domain2.GetHumanInventory().GetItemCount(GameEnums::ItemType::BEER), 1);
}

TEST_F(JSONSerializationTESTS, RoundTripPreservesMagazineState)
{
    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");

    constexpr auto BUFFER = std::array<GameEnums::MagazineChamber, GameConfig::MAX_BULLETS>{
        GameEnums::MagazineChamber::LIVE,
        GameEnums::MagazineChamber::BLANK,
        GameEnums::MagazineChamber::LIVE,
        GameEnums::MagazineChamber::EMPTY,
    };
    domain.GetMagazine().SetMagazine({.m_magazine = BUFFER, .m_head = 2});

    auto serializer = JSONSerializer();
    serializer.Serialize(app, domain, "test_save");

    auto validator = BuildValidator();
    auto deserializer = JSONDeserializer(validator);
    auto app2 = GameBuilder::BuildApplicationState();
    auto domain2 = GameBuilder::BuildDomainState("Human", "Computer");
    deserializer.Deserialize(app2, domain2, "test_save");

    const auto restored = domain2.GetMagazine().GetMagazine();
    EXPECT_EQ(restored.m_head, 2);
    EXPECT_EQ(restored.m_magazine[0], GameEnums::MagazineChamber::LIVE);
    EXPECT_EQ(restored.m_magazine[1], GameEnums::MagazineChamber::BLANK);
    EXPECT_EQ(restored.m_magazine[2], GameEnums::MagazineChamber::LIVE);
}

TEST_F(JSONSerializationTESTS, DeserializeRejectsWrongVersion)
{
    std::ofstream file("data/saves/test_save.json");
    file << R"({"version": "0.0.1"})";
    file.close();

    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    auto validator = BuildValidator();
    auto deserializer = JSONDeserializer(validator);

    deserializer.Deserialize(app, domain, "test_save");

    EXPECT_FALSE(deserializer.GetDeserializationLog().empty());
}

TEST_F(JSONSerializationTESTS, DeserializeHandlesMissingFile)
{
    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    auto validator = BuildValidator();
    auto deserializer = JSONDeserializer(validator);

    deserializer.Deserialize(app, domain, "does_not_exist");

    EXPECT_FALSE(deserializer.GetDeserializationLog().empty());
}

TEST_F(JSONSerializationTESTS, DeserializeHandlesMalformedJson)
{
    std::ofstream file("data/saves/test_save.json");
    file << "{ not valid json ]";
    file.close();

    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    auto validator = BuildValidator();
    auto deserializer = JSONDeserializer(validator);

    deserializer.Deserialize(app, domain, "test_save");

    EXPECT_FALSE(deserializer.GetDeserializationLog().empty());
}

TEST_F(JSONSerializationTESTS, DeserializeHandlesMissingMagazineGracefully)
{
    std::ofstream file("data/saves/test_save.json");
    file << R"({"version": "1.0.0"})";
    file.close();

    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    auto validator = BuildValidator();
    auto deserializer = JSONDeserializer(validator);

    EXPECT_NO_THROW(deserializer.Deserialize(app, domain, "test_save"));
}

#include "ApplicationState.h"
#include "DomainState.h"
#include "GameBuilder.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "SaveConfig.h"
#include "SerializationValidator.h"
#include "TXTDeserializer.h"
#include "TXTSerializer.h"
#include <array>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <system_error>

class TXTSerializationTESTS : public ::testing::Test
{
protected:
    auto SetUp() -> void override
    {
        static_cast<void>(SaveConfig::CreateDirectoryIfNotExists(SaveConfig::GetSaveDirectory()));
    }

    auto TearDown() -> void override
    {
        std::error_code errorCode;
        std::filesystem::remove("data/saves/test_save_txt.txt", errorCode);
    }
};

TEST_F(TXTSerializationTESTS, SerializeCreatesFile)
{
    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    auto serializer = TXTSerializer();

    serializer.Serialize(app, domain, "test_save_txt");

    EXPECT_TRUE(serializer.GetSerializationLog().empty());
    EXPECT_TRUE(std::filesystem::exists("data/saves/test_save_txt.txt"));
}

TEST_F(TXTSerializationTESTS, RoundTripPreservesPlayerState)
{
    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    domain.GetHuman().GetHP().LoseHP(3);
    domain.GetHumanInventory().SetItemCount(GameEnums::ItemType::SAW, 2);

    auto serializer = TXTSerializer();
    serializer.Serialize(app, domain, "test_save_txt");

    auto validator = SerializationValidator();
    auto deserializer = TXTDeserializer(validator);
    auto app2 = GameBuilder::BuildApplicationState();
    auto domain2 = GameBuilder::BuildDomainState("X", "Y");
    deserializer.Deserialize(app2, domain2, "test_save_txt");

    EXPECT_TRUE(deserializer.GetDeserializationLog().empty());
    EXPECT_EQ(domain2.GetHuman().GetName(), "Human");
    EXPECT_EQ(domain2.GetHuman().GetHP().GetHP(), GameConfig::MAX_PLAYER_HP - 3);
    EXPECT_EQ(domain2.GetHumanInventory().GetItemCount(GameEnums::ItemType::SAW), 2);
}

TEST_F(TXTSerializationTESTS, RoundTripPreservesMagazineHead)
{
    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    constexpr auto BUFFER = std::array<GameEnums::MagazineChamber, GameConfig::MAX_BULLETS>{
        GameEnums::MagazineChamber::LIVE,
        GameEnums::MagazineChamber::BLANK,
    };
    domain.GetMagazine().SetMagazine({.m_magazine = BUFFER, .m_head = 1});

    auto serializer = TXTSerializer();
    serializer.Serialize(app, domain, "test_save_txt");

    auto validator = SerializationValidator();
    auto deserializer = TXTDeserializer(validator);
    auto app2 = GameBuilder::BuildApplicationState();
    auto domain2 = GameBuilder::BuildDomainState("Human", "Computer");
    deserializer.Deserialize(app2, domain2, "test_save_txt");

    EXPECT_EQ(domain2.GetMagazine().GetMagazine().m_head, 1);
}

TEST_F(TXTSerializationTESTS, DeserializeHandlesMissingFile)
{
    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    auto validator = SerializationValidator();
    auto deserializer = TXTDeserializer(validator);

    deserializer.Deserialize(app, domain, "does_not_exist");

    EXPECT_FALSE(deserializer.GetDeserializationLog().empty());
}

TEST_F(TXTSerializationTESTS, DeserializeHandlesTruncatedFile)
{
    std::ofstream file("data/saves/test_save_txt.txt");
    file << "1.0.0\nHuman\n";
    file.close();

    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    auto validator = SerializationValidator();
    auto deserializer = TXTDeserializer(validator);

    deserializer.Deserialize(app, domain, "test_save_txt");

    EXPECT_FALSE(deserializer.GetDeserializationLog().empty());
}

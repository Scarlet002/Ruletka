#include "ApplicationState.h"
#include "DomainState.h"
#include "GameBuilder.h"
#include "GameEnums.h"
#include "JSONDeserializer.h"
#include "JSONSerializer.h"
#include "SaveConfig.h"
#include "SerializationManager.h"
#include "SerializationMethodStruct.h"
#include "SerializationValidator.h"
#include "TXTDeserializer.h"
#include "TXTSerializer.h"
#include <filesystem>
#include <gtest/gtest.h>
#include <memory>
#include <system_error>
#include <utility>

class SerializationManagerTESTS : public ::testing::Test
{
protected:
    auto SetUp() -> void override
    {
        static_cast<void>(SaveConfig::CreateDirectoryIfNotExists(SaveConfig::GetSaveDirectory()));
        m_validator = std::make_unique<SerializationValidator>();

        auto serialization = std::make_unique<SerializationManager>();
        SerializationMethodStruct smsJSON(std::make_unique<JSONSerializer>(),
                                          std::make_unique<JSONDeserializer>(*m_validator), m_validator.get());
        SerializationMethodStruct smsTXT(std::make_unique<TXTSerializer>(),
                                         std::make_unique<TXTDeserializer>(*m_validator), m_validator.get());

        serialization->AddSerializationMethod(GameEnums::SerializationFormat::JSON, std::move(smsJSON));
        serialization->AddSerializationMethod(GameEnums::SerializationFormat::TXT, std::move(smsTXT));
        m_manager = std::move(serialization);
    }

    auto TearDown() -> void override
    {
        std::error_code errorCode;
        std::filesystem::remove("data/saves/test_mgr.json", errorCode);
        std::filesystem::remove("data/saves/test_mgr.txt", errorCode);
    }

    std::unique_ptr<SerializationValidator> m_validator;
    std::unique_ptr<SerializationManager> m_manager;
};

TEST_F(SerializationManagerTESTS, SerializesToJsonAfterSettingMethod)
{
    m_manager->SetSerializationMethod(GameEnums::SerializationFormat::JSON);

    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    m_manager->Serialize(app, domain, "test_mgr");

    EXPECT_TRUE(std::filesystem::exists("data/saves/test_mgr.json"));
    EXPECT_FALSE(std::filesystem::exists("data/saves/test_mgr.txt"));
}

TEST_F(SerializationManagerTESTS, SerializesToTxtAfterSettingMethod)
{
    m_manager->SetSerializationMethod(GameEnums::SerializationFormat::TXT);

    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    m_manager->Serialize(app, domain, "test_mgr");

    EXPECT_FALSE(std::filesystem::exists("data/saves/test_mgr.json"));
    EXPECT_TRUE(std::filesystem::exists("data/saves/test_mgr.txt"));
}

TEST_F(SerializationManagerTESTS, SwitchingMethodAffectsNextSerialization)
{
    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");

    m_manager->SetSerializationMethod(GameEnums::SerializationFormat::JSON);
    m_manager->Serialize(app, domain, "test_mgr");
    EXPECT_TRUE(std::filesystem::exists("data/saves/test_mgr.json"));

    m_manager->SetSerializationMethod(GameEnums::SerializationFormat::TXT);
    m_manager->Serialize(app, domain, "test_mgr");
    EXPECT_TRUE(std::filesystem::exists("data/saves/test_mgr.txt"));
}

TEST_F(SerializationManagerTESTS, AddSerializationMethodWithDuplicateKeyIsIgnored)
{
    SerializationMethodStruct duplicate(std::make_unique<JSONSerializer>(),
                                        std::make_unique<JSONDeserializer>(*m_validator), m_validator.get());

    EXPECT_NO_THROW(m_manager->AddSerializationMethod(GameEnums::SerializationFormat::JSON, std::move(duplicate)));
}

TEST_F(SerializationManagerTESTS, GetSerializationLogWorksAfterSerialize)
{
    m_manager->SetSerializationMethod(GameEnums::SerializationFormat::JSON);

    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");
    m_manager->Serialize(app, domain, "test_mgr");

    EXPECT_TRUE(m_manager->GetSerializationLog().empty());
}

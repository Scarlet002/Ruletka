#include "ApplicationState.h"
#include "AutoSaveManager.h"
#include "DomainState.h"
#include "GameBuilder.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "JSONDeserializer.h"
#include "JSONSerializer.h"
#include "SaveConfig.h"
#include "SerializationManager.h"
#include "SerializationMethodStruct.h"
#include "SerializationValidator.h"
#include <chrono>
#include <cstdint>
#include <filesystem>
#include <gtest/gtest.h>
#include <memory>
#include <system_error>
#include <thread>
#include <utility>

class AutoSaveManagerTESTS : public ::testing::Test
{
protected:
    auto SetUp() -> void override
    {
        static_cast<void>(SaveConfig::CreateDirectoryIfNotExists(SaveConfig::GetAutoSaveDirectory()));
        m_validator = std::make_unique<SerializationValidator>();
        auto serialization = std::make_unique<SerializationManager>();
        SerializationMethodStruct smsJSON(std::make_unique<JSONSerializer>(),
                                          std::make_unique<JSONDeserializer>(*m_validator), m_validator.get());
        serialization->AddSerializationMethod(GameEnums::SerializationFormat::JSON, std::move(smsJSON));
        serialization->SetSerializationMethod(GameEnums::SerializationFormat::JSON);
        m_manager = std::move(serialization);
    }

    auto TearDown() -> void override
    {
        std::error_code errorCode;
        for (const auto& entry : std::filesystem::directory_iterator(SaveConfig::GetAutoSaveDirectory(), errorCode))
        {
            std::filesystem::remove(entry.path(), errorCode);
        }
    }

    std::unique_ptr<SerializationValidator> m_validator;
    std::unique_ptr<SerializationManager> m_manager;
};

TEST_F(AutoSaveManagerTESTS, IsSavingStartsFalse)
{
    AutoSaveManager autoSave(*m_manager);
    EXPECT_FALSE(autoSave.IsSaving());
}

TEST_F(AutoSaveManagerTESTS, GetSaveCounterStartsAtZero)
{
    AutoSaveManager autoSave(*m_manager);
    EXPECT_EQ(autoSave.GetSaveCounter(), 0U);
}

TEST_F(AutoSaveManagerTESTS, SetSaveCounterUpdatesValue)
{
    AutoSaveManager autoSave(*m_manager);
    constexpr auto COUNTER = 42U;
    autoSave.SetSaveCounter(static_cast<uint8_t>(COUNTER));
    EXPECT_EQ(autoSave.GetSaveCounter(), static_cast<uint8_t>(COUNTER));
}

TEST_F(AutoSaveManagerTESTS, SaveSnapshotAsyncSetsIsSavingTrue)
{
    AutoSaveManager autoSave(*m_manager);
    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");

    autoSave.SaveSnapshotAsync(app, domain);
    while (autoSave.IsSaving())
    {
        constexpr auto TIME = 1U;
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
    }
    EXPECT_FALSE(autoSave.IsSaving());
}

TEST_F(AutoSaveManagerTESTS, SaveSnapshotAsyncIncrementsCounter)
{
    AutoSaveManager autoSave(*m_manager);
    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");

    autoSave.SaveSnapshotAsync(app, domain);
    constexpr auto COUNTER = 1U;
    EXPECT_EQ(autoSave.GetSaveCounter(), COUNTER);

    while (autoSave.IsSaving())
    {
        constexpr auto TIME = 1U;
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
    }
}

TEST_F(AutoSaveManagerTESTS, ConcurrentSaveAndModificationDoesNotCrash)
{
    AutoSaveManager autoSave(*m_manager);
    auto app = GameBuilder::BuildApplicationState();
    auto domain = GameBuilder::BuildDomainState("Human", "Computer");

    auto modifier = std::thread([&]() -> void {
        constexpr auto SAMPLE_ONE = 50UZ;
        for (auto i = 0UZ; i < SAMPLE_ONE; ++i)
        {
            domain.GetHumanHP().LoseHP(GameConfig::DEFAULT_DAMAGE);
            constexpr auto TIME = 100U;
            std::this_thread::sleep_for(std::chrono::microseconds(TIME));
        }
    });

    constexpr auto SAMPLE_TWO = 5UZ;
    for (auto i = 0UZ; i < SAMPLE_TWO; ++i)
    {
        autoSave.SaveSnapshotAsync(app, domain);
        constexpr auto TIME = 10U;
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
    }

    modifier.join();
    while (autoSave.IsSaving())
    {
        constexpr auto TIME = 1U;
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
    }
    SUCCEED();
}

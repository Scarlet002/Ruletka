#pragma once

#include <atomic>
#include <cstdint>
#include <string_view>
#include <thread>

class SerializationManager;
class ApplicationState;
class DomainState;

class AutoSaveManager final
{
private:
    SerializationManager& m_serializer;
    std::jthread m_saveThread;
    std::atomic<uint8_t> m_saveCounter = 0U;
    std::atomic<bool> m_isSaving = false;

public:
    explicit AutoSaveManager(SerializationManager& serializer) noexcept;

    AutoSaveManager(const AutoSaveManager&) = delete;
    auto operator=(const AutoSaveManager&) -> AutoSaveManager& = delete;

    AutoSaveManager(AutoSaveManager&&) = delete;
    auto operator=(AutoSaveManager&&) -> AutoSaveManager& = delete;

    ~AutoSaveManager() noexcept;

    auto SaveSnapshotAsync(const ApplicationState& app, const DomainState& domain) -> void;
    [[nodiscard]]
    auto IsSaving() const noexcept -> bool;
    auto SetSaveCounter(uint8_t newCount) -> void;
    [[nodiscard]]
    auto GetSaveCounter() const noexcept -> uint8_t;
    [[nodiscard]]
    auto GetSerializationLog() const -> std::string_view;
};

#include "AutoSaveManager.h"
#include "ApplicationState.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "SerializationManager.h"
#include <boost/static_string/static_string.hpp>
#include <cstdint>
#include <format>
#include <stop_token>
#include <string_view>
#include <thread>

AutoSaveManager::AutoSaveManager(SerializationManager& serializer) noexcept : m_serializer(serializer)
{
}

AutoSaveManager::~AutoSaveManager() noexcept = default;

auto AutoSaveManager::SaveSnapshotAsync(const ApplicationState& app, const DomainState& domain) -> void
{
    if (m_saveThread.joinable())
    {
        m_saveThread.request_stop();
        m_saveThread.join();
    }

    const auto appSnapshot = app;       // NOLINT(performance-unnecessary-copy-initialization)
    const auto domainSnapshot = domain; // NOLINT(performance-unnecessary-copy-initialization)
    m_isSaving.store(true);
    m_saveCounter++;

    m_saveThread = std::jthread([this, appSnapshot, domainSnapshot](const std::stop_token& stop) -> void {
        try
        {
            if (stop.stop_requested())
            {
                m_isSaving.store(false);
                return;
            }

            boost::static_string<GameConfig::LOG_LINE_RESERVE> filename;
            const auto* end = std::format_to(filename.begin(), "autosave{}", static_cast<int>(GetSaveCounter()));
            filename.resize(static_cast<uint8_t>(end - filename.begin()));
            m_serializer.Serialize(appSnapshot, domainSnapshot, filename);
            m_isSaving.store(false);
        }
        catch (...)
        {
            m_isSaving.store(false);
            return;
        }
    });
}

auto AutoSaveManager::IsSaving() const noexcept -> bool
{
    return m_isSaving.load();
}

auto AutoSaveManager::SetSaveCounter(uint8_t newCount) -> void
{
    m_saveCounter.store(newCount);
}

auto AutoSaveManager::GetSaveCounter() const noexcept -> uint8_t
{
    return m_saveCounter.load();
}

auto AutoSaveManager::GetSerializationLog() const -> std::string_view
{
    return m_serializer.GetSerializationLog();
}

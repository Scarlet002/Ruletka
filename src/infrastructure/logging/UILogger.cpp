#include "UILogger.h"
#include "GameConfig.h"
#include "Logger.h"
#include <algorithm>
#include <cassert>
#include <string_view>

UILogger::UILogger() noexcept = default;

auto UILogger::UpdateLogs(std::string_view newLog) -> void
{
    assert(newLog.size() <= GameConfig::LOG_LINE_RESERVE && "Log line will be truncated!");
    assert(m_head < GameConfig::MAX_LOGS && "Invalid head index!");
    m_logs[m_head] = newLog;
    m_head = (m_head + 1) % GameConfig::MAX_LOGS;
}

auto UILogger::GetLogs() const noexcept -> LogsView
{
    return {.m_logs = m_logs, .m_head = m_head};
}

auto UILogger::SetLogs(LogsView newLogs) noexcept -> void
{
    assert(newLogs.m_head < GameConfig::MAX_LOGS && "Invalid head index!");
    std::ranges::copy(newLogs.m_logs, m_logs.begin());
    m_head = newLogs.m_head;
}

auto UILogger::ClearLogs() noexcept -> void
{
    for (auto& log : m_logs)
    {
        log.clear();
    }
    m_head = GameConfig::MIN_LOGS;
}

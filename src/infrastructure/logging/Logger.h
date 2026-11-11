#pragma once

#include "GameConfig.h"
#include <boost/static_string/static_string.hpp>
#include <cstdint>
#include <span>
#include <string_view>

struct LogsView final
{
    std::span<const boost::static_string<GameConfig::LOG_LINE_RESERVE>, GameConfig::MAX_LOGS> m_logs;
    std::uint8_t m_head = GameConfig::MIN_LOGS;
};

class Logger
{
protected:
    Logger() noexcept = default;

public:
    Logger(const Logger&) = delete;
    auto operator=(const Logger&) -> Logger& = delete;

    Logger(Logger&&) = delete;
    auto operator=(Logger&&) -> Logger& = delete;

    virtual ~Logger() noexcept = default;

    [[nodiscard]]
    virtual auto GetLogs() const noexcept -> LogsView = 0;
    virtual auto SetLogs(LogsView newLogs) noexcept -> void = 0;
    virtual auto UpdateLogs(std::string_view newLog) -> void = 0;
    virtual auto ClearLogs() noexcept -> void = 0;
};

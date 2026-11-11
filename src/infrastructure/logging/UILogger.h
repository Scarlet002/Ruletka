#pragma once

#include "GameConfig.h"
#include "Logger.h"
#include <array>
#include <boost/static_string/static_string.hpp>
#include <cstdint>
#include <string_view>

class UILogger final : public Logger
{
private:
    std::array<boost::static_string<GameConfig::LOG_LINE_RESERVE>, GameConfig::MAX_LOGS> m_logs = {};
    uint8_t m_head = GameConfig::MIN_LOGS;

public:
    UILogger() noexcept;

    [[nodiscard]]
    auto GetLogs() const noexcept -> LogsView override;
    auto SetLogs(LogsView newLogs) noexcept -> void override;
    auto UpdateLogs(std::string_view newLog) -> void override;
    auto ClearLogs() noexcept -> void override;
};

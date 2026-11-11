#include "GameConfig.h"
#include "UILogger.h"
#include <algorithm>
#include <array>
#include <boost/static_string/static_string.hpp>
#include <gtest/gtest.h>

namespace
{
using RingBuffer = std::array<boost::static_string<GameConfig::LOG_LINE_RESERVE>, GameConfig::MAX_LOGS>;
} //namespace

TEST(UILoggerTESTS, SetLogsAndGetLogsSetsAndReturnsLogs)
{
    auto uiLogger = UILogger();
    constexpr auto NEW_LOGS = RingBuffer{
        "1",
        "2",
        "3",
    };

    uiLogger.SetLogs({
        .m_logs = NEW_LOGS,
        .m_head = 0U,
    });

    EXPECT_TRUE(std::ranges::equal(uiLogger.GetLogs().m_logs, NEW_LOGS));
}

TEST(UILoggerTESTS, ClearLogsClearsLogs)
{
    auto uiLogger = UILogger();
    constexpr auto NEW_LOGS = RingBuffer{
        "1",
        "2",
        "3",
    };

    uiLogger.SetLogs({
        .m_logs = NEW_LOGS,
        .m_head = 0U,
    });

    uiLogger.ClearLogs();
    constexpr auto EMPTY_LOGS = RingBuffer{};

    EXPECT_TRUE(std::ranges::equal(uiLogger.GetLogs().m_logs, EMPTY_LOGS));
}

TEST(UILoggerTESTS, UpdateLogsUpdatesLogIfNumberOfLogsDoesNotExceedMaxLimit)
{
    auto uiLogger = UILogger();
    constexpr auto NEW_LOG = "xyz";
    uiLogger.UpdateLogs(NEW_LOG);

    const auto logs = uiLogger.GetLogs();
    EXPECT_EQ(logs.m_logs.front(), NEW_LOG);
}

TEST(UILoggerTESTS, UpdateLogsSizeDoesNotExceedMaxLimit)
{
    auto uiLogger = UILogger();
    constexpr auto NEW_LOG = "xyz";
    constexpr auto LOOPS = 30UZ;

    for (auto index = 0UZ; index < LOOPS; ++index)
    {
        uiLogger.UpdateLogs(NEW_LOG);
    }

    const auto logs = uiLogger.GetLogs();
    EXPECT_EQ(logs.m_logs.size(), GameConfig::MAX_LOGS);
}

#include "GameConfig.h"
#include "UILogger.h"
#include <algorithm>
#include <array>
#include <boost/static_string/static_string.hpp>
#include <gtest/gtest.h>
#include <string_view>

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
    constexpr auto NEW_LOG = std::string_view("xyz");
    uiLogger.UpdateLogs(NEW_LOG);

    const auto logs = uiLogger.GetLogs();
    EXPECT_EQ(logs.m_logs.front(), NEW_LOG);
}

TEST(UILoggerTESTS, UpdateLogsSizeDoesNotExceedMaxLimit)
{
    auto uiLogger = UILogger();
    constexpr auto NEW_LOG = std::string_view("xyz");
    constexpr auto LOOPS = 30UZ;

    for (auto index = 0UZ; index < LOOPS; ++index)
    {
        uiLogger.UpdateLogs(NEW_LOG);
    }

    const auto logs = uiLogger.GetLogs();
    EXPECT_EQ(logs.m_logs.size(), GameConfig::MAX_LOGS);
}

TEST(UILoggerTESTS, UpdateLogsTruncatesTooLongLog)
{
    auto uiLogger = UILogger();
    const auto longLog = boost::static_string<100>(100, 'x');

    EXPECT_NO_THROW(uiLogger.UpdateLogs(longLog));

    const auto logs = uiLogger.GetLogs();
    EXPECT_LE(logs.m_logs.front().size(), GameConfig::LOG_LINE_RESERVE);
}

TEST(UILoggerTESTS, UpdateLogsEmptyStringIsAllowed)
{
    auto uiLogger = UILogger();

    EXPECT_NO_THROW(uiLogger.UpdateLogs(""));

    const auto logs = uiLogger.GetLogs();
    EXPECT_TRUE(logs.m_logs.front().empty());
}

TEST(UILoggerTESTS, UpdateLogsWrapsHeadAroundAfterMaxLogs)
{
    auto uiLogger = UILogger();
    constexpr auto SAMPLE = GameConfig::MAX_LOGS + 3UZ;

    for (auto i = 0UZ; i < SAMPLE; ++i)
    {
        uiLogger.UpdateLogs("x");
    }

    const auto logs = uiLogger.GetLogs();
    EXPECT_LT(logs.m_head, GameConfig::MAX_LOGS);
}

TEST(UILoggerTESTS, ClearLogsResetsHeadToZero)
{
    auto uiLogger = UILogger();
    constexpr auto SAMPLE = 5UZ;
    for (auto i = 0UZ; i < SAMPLE; ++i)
    {
        uiLogger.UpdateLogs("x");
    }

    uiLogger.ClearLogs();

    EXPECT_EQ(uiLogger.GetLogs().m_head, GameConfig::MIN_LOGS);
}

TEST(UILoggerTESTS, SetLogsWithInvalidHeadDoesNotCorruptState)
{
    auto uiLogger = UILogger();

    uiLogger.UpdateLogs("marker");
    const auto before = uiLogger.GetLogs();

    EXPECT_EQ(before.m_logs.front(), "marker");
}

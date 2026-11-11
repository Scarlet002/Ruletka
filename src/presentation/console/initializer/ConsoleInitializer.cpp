#include "ConsoleInitializer.h"
#include "Logger.h"

ConsoleInitializer::ConsoleInitializer(Logger& logger) noexcept : m_logger(logger)
{
}

auto ConsoleInitializer::Initialize() -> void
{
    m_logger.ClearLogs();
}

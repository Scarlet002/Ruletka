#pragma once

#include "Initializer.h"

class Logger;

class ConsoleInitializer final : public Initializer
{
private:
    Logger& m_logger;

public:
    explicit ConsoleInitializer(Logger& logger) noexcept;

    auto Initialize() -> void override;
};

#pragma once

#include "IAction.h"

class ApplicationState;
class Logger;
class SerializationManager;

class ChangeSerialization final : public IAction
{
private:
    ApplicationState& m_app;
    Logger& m_logger;
    SerializationManager& m_serialization;

public:
    ChangeSerialization(ApplicationState& app, Logger& logger, SerializationManager& serialization) noexcept;

    ChangeSerialization(const ChangeSerialization&) = delete;
    auto operator=(const ChangeSerialization&) -> ChangeSerialization& = delete;

    ChangeSerialization(ChangeSerialization&&) = delete;
    auto operator=(ChangeSerialization&&) -> ChangeSerialization& = delete;

    ~ChangeSerialization() noexcept override;

    auto Execute() -> void override;
};

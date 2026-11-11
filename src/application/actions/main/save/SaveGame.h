#pragma once

#include "IAction.h"

class ApplicationState;
class DomainState;
class Logger;
class SerializationManager;

class SaveGame final : public IAction
{
private:
    ApplicationState& m_app;
    DomainState& m_domain;
    Logger& m_logger;
    SerializationManager& m_serialization;

public:
    SaveGame(ApplicationState& app, DomainState& domain, Logger& logger, SerializationManager& serialization) noexcept;

    SaveGame(const SaveGame&) = delete;
    auto operator=(const SaveGame&) -> SaveGame& = delete;

    SaveGame(SaveGame&&) = delete;
    auto operator=(SaveGame&&) -> SaveGame& = delete;

    ~SaveGame() noexcept override;

    auto Execute() -> void override;
};

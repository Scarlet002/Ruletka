#pragma once

#include "IAction.h"

class ApplicationState;
class DomainState;
class Logger;
class SerializationManager;

class LoadGame final : public IAction
{
private:
    ApplicationState& m_app;
    DomainState& m_domain;
    Logger& m_logger;
    SerializationManager& m_serialization;

public:
    LoadGame(ApplicationState& app, DomainState& domain, Logger& logger, SerializationManager& serialization) noexcept;

    LoadGame(const LoadGame&) = delete;
    auto operator=(const LoadGame&) -> LoadGame& = delete;

    LoadGame(LoadGame&&) = delete;
    auto operator=(LoadGame&&) -> LoadGame& = delete;

    ~LoadGame() noexcept override;

    auto Execute() -> void override;
};

#pragma once

#include "IAction.h"

class ApplicationState;
class DomainState;
class Logger;
class AutoSaveManager;

class AutoSave final : public IAction
{
private:
    ApplicationState& m_app;
    DomainState& m_domain;
    Logger& m_logger;
    AutoSaveManager& m_async;

public:
    AutoSave(ApplicationState& app, DomainState& domain, Logger& logger, AutoSaveManager& async) noexcept;

    AutoSave(const AutoSave&) = delete;
    auto operator=(const AutoSave&) -> AutoSave& = delete;

    AutoSave(AutoSave&&) = delete;
    auto operator=(AutoSave&&) -> AutoSave& = delete;

    ~AutoSave() noexcept override;

    auto Execute() -> void override;
};

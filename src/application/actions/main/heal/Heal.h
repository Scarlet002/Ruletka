#pragma once

#include "IAction.h"

class ApplicationState;
class DomainState;
class Logger;

class Heal final : public IAction
{
private:
    ApplicationState& m_app;
    DomainState& m_domain;
    Logger& m_logger;

public:
    Heal(ApplicationState& app, DomainState& domain, Logger& logger) noexcept;

    Heal(const Heal&) = delete;
    auto operator=(const Heal&) -> Heal& = delete;

    Heal(Heal&&) = delete;
    auto operator=(Heal&&) -> Heal& = delete;

    ~Heal() noexcept override;

    auto Execute() -> void override;
};

#pragma once

#include "IAction.h"

class ApplicationState;
class DomainState;
class Logger;

class Shoot final : public IAction
{
private:
    ApplicationState& m_app;
    DomainState& m_domain;
    Logger& m_logger;

public:
    Shoot(ApplicationState& app, DomainState& domain, Logger& logger) noexcept;

    Shoot(const Shoot&) = delete;
    auto operator=(const Shoot&) -> Shoot& = delete;

    Shoot(Shoot&&) = delete;
    auto operator=(Shoot&&) -> Shoot& = delete;

    ~Shoot() noexcept override;

    auto Execute() -> void override;
};

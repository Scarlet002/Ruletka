#pragma once

#include "IAction.h"

class ApplicationState;
class Logger;
class AIManager;

class ChangeDifficulty final : public IAction
{
private:
    ApplicationState& m_app;
    Logger& m_logger;
    AIManager& m_aiManager;

public:
    ChangeDifficulty(ApplicationState& app, Logger& logger, AIManager& aiManager) noexcept;

    ChangeDifficulty(const ChangeDifficulty&) = delete;
    auto operator=(const ChangeDifficulty&) -> ChangeDifficulty& = delete;

    ChangeDifficulty(ChangeDifficulty&&) = delete;
    auto operator=(ChangeDifficulty&&) -> ChangeDifficulty& = delete;

    ~ChangeDifficulty() noexcept override;

    auto Execute() -> void override;
};

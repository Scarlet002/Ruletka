#include "ChangeDifficulty.h"
#include "AIManager.h"
#include "AIState.h"
#include "ApplicationState.h"
#include "DecisionState.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Logger.h"
#include <optional>

ChangeDifficulty::~ChangeDifficulty() noexcept = default;

ChangeDifficulty::ChangeDifficulty(ApplicationState& app, Logger& logger, AIManager& aiManager) noexcept
    : m_app(app), m_logger(logger), m_aiManager(aiManager)
{
}

auto ChangeDifficulty::Execute() -> void
{
    auto& loop = m_app.GetGameLoopState();
    loop.SetCurrentMenu(GameEnums::Window::DIFFICULTY_MENU);

    auto& decision = m_app.GetDecisionState();
    const auto action = decision.GetDifficultyChoice();
    if (!action.has_value())
    {
        return;
    }

    const auto newDiff = action.value();
    m_app.GetAIState().SetDifficulty(newDiff);
    m_aiManager.SetDifficulty(newDiff);

    switch (newDiff)
    {
    case GameEnums::Difficulty::EASY:
        m_logger.UpdateLogs("Difficulty level: Easy!");
        break;
    case GameEnums::Difficulty::NORMAL:
        m_logger.UpdateLogs("Difficulty level: Normal!");
        break;
    case GameEnums::Difficulty::HARD:
        m_logger.UpdateLogs("Difficulty level: Hard!");
        break;
    default:
        break;
    }

    decision.SetDifficultyChoice(std::nullopt);
    decision.SetMainChoice(std::nullopt);
    loop.SetCurrentMenu(GameEnums::Window::MAIN_MENU);
}

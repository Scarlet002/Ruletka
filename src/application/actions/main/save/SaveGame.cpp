#include "SaveGame.h"
#include "ApplicationState.h"
#include "DecisionState.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Logger.h"
#include "SerializationManager.h"
#include <boost/static_string/static_string.hpp>
#include <format>
#include <iterator>
#include <optional>

SaveGame::~SaveGame() noexcept = default;

SaveGame::SaveGame(ApplicationState& app, DomainState& domain, Logger& logger,
                   SerializationManager& serialization) noexcept
    : m_app(app), m_domain(domain), m_logger(logger), m_serialization(serialization)
{
}

auto SaveGame::Execute() -> void
{
    auto& decision = m_app.GetDecisionState();
    auto& loop = m_app.GetGameLoopState();
    if (loop.GetCurrentMenu() != GameEnums::Window::SAVE_MENU)
    {
        decision.SetMainChoice(std::nullopt);
        loop.SetCurrentMenu(GameEnums::Window::SAVE_MENU);
        return;
    }

    const auto filename = decision.GetFilename();
    decision.SetMainChoice(std::nullopt);
    loop.SetCurrentMenu(GameEnums::Window::MAIN_MENU);
    m_serialization.Serialize(m_app, m_domain, filename);
    if (!m_serialization.GetSerializationLog().empty())
    {
        m_logger.UpdateLogs(m_serialization.GetSerializationLog());
    }
    else
    {
        boost::static_string<GameConfig::LOG_LINE_RESERVE> log;
        std::format_to(std::back_inserter(log), "Game has been saved as {}!", filename);
        m_logger.UpdateLogs(log);
    }
}

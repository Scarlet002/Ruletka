#include "LoadGame.h"
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

LoadGame::~LoadGame() noexcept = default;

LoadGame::LoadGame(ApplicationState& app, DomainState& domain, Logger& logger,
                   SerializationManager& serialization) noexcept
    : m_app(app), m_domain(domain), m_logger(logger), m_serialization(serialization)
{
}

auto LoadGame::Execute() -> void
{
    auto& loop = m_app.GetGameLoopState();
    auto& decision = m_app.GetDecisionState();
    if (loop.GetCurrentMenu() != GameEnums::Window::LOAD_MENU)
    {
        decision.SetMainChoice(std::nullopt);
        loop.SetCurrentMenu(GameEnums::Window::LOAD_MENU);
        return;
    }

    const auto filename = decision.GetFilename();
    decision.SetMainChoice(std::nullopt);
    loop.SetCurrentMenu(GameEnums::Window::MAIN_MENU);
    m_serialization.Deserialize(m_app, m_domain, filename);
    if (!m_serialization.GetDeserializationLog().empty())
    {
        m_logger.UpdateLogs(m_serialization.GetDeserializationLog());
    }
    else
    {
        boost::static_string<GameConfig::LOG_LINE_RESERVE> log;
        std::format_to(std::back_inserter(log), "Game has been loaded from file {}!", filename);
        m_logger.UpdateLogs(log);
    }
}

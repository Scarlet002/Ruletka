#include "GameLoopManager.h"
#include "ApplicationState.h"
#include "AutoSaveManager.h"
#include "DecisionState.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Logger.h"
#include "Magazine.h"
#include "Player.h"
#include "RoundInitializer.h"
#include <memory>
#include <optional>
#include <utility>

GameLoopManager::GameLoopManager(ApplicationState& appState, DomainState& domainState, AutoSaveManager& asyncSerializer,
                                 std::unique_ptr<Initializer> gameLoopInitializer,
                                 std::unique_ptr<Initializer> roundInitializer, Logger& logger)
    : m_appState(appState), m_domainState(domainState), m_asyncSerializer(asyncSerializer),
      m_gameLoopInitializer(std::move(gameLoopInitializer)), m_roundInitializer(std::move(roundInitializer)),
      m_logger(logger)
{
    RestartGame();
}

auto GameLoopManager::SetRestartMenu() -> void
{
    using namespace GameEnums;
    auto& decisionState = m_appState.GetDecisionState();
    auto& initializer = m_appState.GetGameLoopState();
    initializer.SetStarter(PlayerType::HUMAN);
    decisionState.SetYesNoChoice(std::nullopt);
    initializer.SetCurrentMenu(Window::RESTART_MENU);
    initializer.SetIsInRestartMenu(YesNo::YES);
}

auto GameLoopManager::HandlePlayerDeath() -> void
{
    using namespace GameEnums;
    const auto& human = m_domainState.GetHuman();
    const auto& computer = m_domainState.GetComputer();
    const auto& gameLoopInitializer = m_appState.GetGameLoopState();
    if (gameLoopInitializer.GetStateOfGameLoop() == YesNo::YES &&
        gameLoopInitializer.GetIsInRestartMenu() == YesNo::NO &&
        (human.IsAlive() == YesNo::NO || computer.IsAlive() == YesNo::NO))
    {
        SetRestartMenu();
    }
}

auto GameLoopManager::HandleEmptyMagazine() -> void
{
    using namespace GameEnums;
    const auto& gameLoopInitializer = m_appState.GetGameLoopState();
    const auto& magazine = m_domainState.GetMagazine();
    if (magazine.IsEmpty() && gameLoopInitializer.GetCurrentMenu() != Window::RESTART_MENU)
    {
        m_roundInitializer->Initialize();
    }
}

auto GameLoopManager::RestartGame() -> void
{
    m_logger.ClearLogs();
    m_gameLoopInitializer->Initialize();
    m_asyncSerializer.SetSaveCounter(GameConfig::STARTING_AUTOSAVE_COUNT);
}

auto GameLoopManager::ShutdownGame() -> void
{
    using namespace GameEnums;
    using namespace std::this_thread;
    using namespace std::chrono;
    auto& gameLoopInitializer = m_appState.GetGameLoopState();
    gameLoopInitializer.SetStateOfGameLoop(YesNo::NO);
}

auto GameLoopManager::HandleRestartChoice() -> void
{
    using namespace GameEnums;
    const auto& gameLoopInitializer = m_appState.GetGameLoopState();
    const auto& decisionState = m_appState.GetDecisionState();
    const auto action = decisionState.GetYesNoChoice();
    if (!action.has_value() || gameLoopInitializer.GetCurrentMenu() != Window::RESTART_MENU)
    {
        return;
    }

    const auto choice = action.value();
    if (choice == YesNo::YES)
    {
        RestartGame();
    }
    else
    {
        ShutdownGame();
    }
}

auto GameLoopManager::ProcessTurnEnd() -> void
{
    HandlePlayerDeath();
    HandleEmptyMagazine();
    HandleRestartChoice();
}

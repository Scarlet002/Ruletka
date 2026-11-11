#pragma once

#include <memory>

class ApplicationState;
class DomainState;
class AutoSaveManager;
class Initializer;
class Logger;

class GameLoopManager final
{
private:
    ApplicationState& m_appState;
    DomainState& m_domainState;
    AutoSaveManager& m_asyncSerializer;
    std::unique_ptr<Initializer> m_gameLoopInitializer;
    std::unique_ptr<Initializer> m_roundInitializer;
    Logger& m_logger;

    auto SetRestartMenu() -> void;
    auto HandlePlayerDeath() -> void;
    auto HandleEmptyMagazine() -> void;
    auto RestartGame() -> void;
    auto ShutdownGame() -> void;
    auto HandleRestartChoice() -> void;

public:
    GameLoopManager(ApplicationState& appState, DomainState& domainState, AutoSaveManager& asyncSerializer,
                    std::unique_ptr<Initializer> gameLoopInitializer, std::unique_ptr<Initializer> roundInitializer,
                    Logger& logger);

    auto ProcessTurnEnd() -> void;
};

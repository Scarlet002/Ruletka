#pragma once

#include "GameEnums.h"
#include <memory>
#include <string_view>

class GameLoopManager;
class SerializationValidator;
class SerializationManager;
class AutoSaveManager;
class Player;
class AIManager;
class IProcessor;
class Logger;
class ApplicationState;
class DomainState;
class UIManager;
class DecisionState;
class GameLoopState;

class GameBuilder final
{
private:
    [[nodiscard]]
    static auto BuildPlayer(std::string_view name, GameEnums::PlayerType type) -> Player;

public:
    GameBuilder() = delete;

    [[nodiscard]]
    static auto BuildApplicationState() -> ApplicationState;
    [[nodiscard]]
    static auto BuildDomainState(std::string_view humanName, std::string_view computerName) -> DomainState;
    [[nodiscard]]
    static auto BuildAIManager(DecisionState& decision, DomainState& domain) -> AIManager;
    [[nodiscard]]
    static auto BuildInventoryProcessor(DecisionState& decision, GameLoopState& loop, DomainState& domain,
                                        Logger& logger) -> std::unique_ptr<IProcessor>;
    [[nodiscard]]
    static auto BuildDecisionProcessor(ApplicationState& app, DomainState& domain, Logger& logger, AIManager& aiManager,
                                       IProcessor& inventory, SerializationManager& serialization,
                                       AutoSaveManager& async) -> std::unique_ptr<IProcessor>;
    [[nodiscard]]
    static auto BuildUIManager(ApplicationState& app, const DomainState& domain, Logger& logger,
                               GameEnums::UIType uiChoice) -> UIManager;
    [[nodiscard]]
    static auto BuildSerializationManager(SerializationValidator& validator,
                                          GameEnums::SerializationFormat serializationChoice)
        -> std::unique_ptr<SerializationManager>;
    [[nodiscard]]
    static auto BuildAsyncSerializer(SerializationManager& serialization) -> AutoSaveManager;
    [[nodiscard]]
    static auto BuildGameLoopManager(ApplicationState& app, DomainState& domain, AutoSaveManager& async, Logger& logger)
        -> GameLoopManager;
    [[nodiscard]]
    static auto BuildSerializationValidator() -> SerializationValidator;
    [[nodiscard]]
    static auto BuildUILogger() -> std::unique_ptr<Logger>;
};

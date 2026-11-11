#include "GameBuilder.h"
#include "AIManager.h"
#include "AIState.h"
#include "ApplicationState.h"
#include "AutoSave.h"
#include "AutoSaveManager.h"
#include "Beer.h"
#include "Cellphone.h"
#include "ChangeDifficulty.h"
#include "ChangeSerialization.h"
#include "ConsoleInitializer.h"
#include "ConsoleProvider.h"
#include "ConsoleRenderer.h"
#include "ConsoleUI.h"
#include "DecisionProcessor.h"
#include "DecisionState.h"
#include "Deserializer.h"
#include "DomainState.h"
#include "EasyAI.h"
#include "Exit.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopInitializer.h"
#include "GameLoopManager.h"
#include "GameLoopState.h"
#include "HP.h"
#include "Handcuffs.h"
#include "HardAI.h"
#include "Heal.h"
#include "IProcessor.h"
#include "Inventory.h"
#include "InventoryProcessor.h"
#include "Inverter.h"
#include "ItemState.h"
#include "JSONDeserializer.h"
#include "JSONSerializer.h"
#include "LoadGame.h"
#include "Logger.h"
#include "Magazine.h"
#include "Magnifier.h"
#include "NormalAI.h"
#include "Player.h"
#include "RoundInitializer.h"
#include "SFMLInitializer.h"
#include "SFMLProvider.h"
#include "SFMLRenderer.h"
#include "SFMLUI.h"
#include "SaveGame.h"
#include "Saw.h"
#include "SerializationManager.h"
#include "SerializationMethodStruct.h"
#include "SerializationState.h"
#include "SerializationValidator.h"
#include "Serializer.h"
#include "Shoot.h"
#include "TXTDeserializer.h"
#include "TXTSerializer.h"
#include "UILogger.h"
#include "UIManager.h"
#include "UseItem.h"
#include "Validator.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <memory>
#include <string_view>
#include <utility>

#ifdef _WIN32
#include <consoleapi3.h>
#include <windows.h>
#include <winuser.h>
#endif

auto GameBuilder::BuildPlayer(const std::string_view name, const GameEnums::PlayerType type) -> Player
{
    auto inventory = Inventory();
    for (const auto& item : GameConfig::ITEM_TYPES)
    {
        inventory.AddItemType(item.second, GameConfig::MIN_ITEMS);
    }
    return {name, HP(), std::move(inventory), type};
}

auto GameBuilder::BuildApplicationState() -> ApplicationState
{
    return {AIState(), DecisionState(), GameLoopState(), SerializationState()};
}

auto GameBuilder::BuildDomainState(std::string_view humanName, std::string_view computerName) -> DomainState
{
    return {BuildPlayer(computerName, GameEnums::PlayerType::COMPUTER),
            BuildPlayer(humanName, GameEnums::PlayerType::HUMAN), ItemState(), Magazine()};
}

auto GameBuilder::BuildAIManager(DecisionState& decision, DomainState& domain) -> AIManager
{
    using GameEnums::Difficulty;
    auto aim = AIManager();
    aim.AddDifficulty(Difficulty::EASY, std::make_unique<EasyAI>(decision));
    aim.AddDifficulty(Difficulty::NORMAL, std::make_unique<NormalAI>(decision, domain));
    aim.AddDifficulty(Difficulty::HARD, std::make_unique<HardAI>(decision, domain));
    return aim;
}

auto GameBuilder::BuildInventoryProcessor(DecisionState& decision, GameLoopState& loop, DomainState& domain,
                                          Logger& logger) -> std::unique_ptr<IProcessor>
{
    using GameEnums::ItemType;
    auto inventoryProcessor = std::make_unique<InventoryProcessor>(decision);
    inventoryProcessor->AddAction(ItemType::HANDCUFFS, std::make_unique<Handcuffs>(loop, domain, logger));
    inventoryProcessor->AddAction(ItemType::BEER, std::make_unique<Beer>(loop, domain, logger));
    inventoryProcessor->AddAction(ItemType::MAGNIFIER, std::make_unique<Magnifier>(loop, domain, logger));
    inventoryProcessor->AddAction(ItemType::SAW, std::make_unique<Saw>(loop, domain, logger));
    inventoryProcessor->AddAction(ItemType::CELLPHONE, std::make_unique<Cellphone>(loop, domain, logger));
    inventoryProcessor->AddAction(ItemType::INVERTER, std::make_unique<Inverter>(loop, domain, logger));
    return inventoryProcessor;
}

auto GameBuilder::BuildDecisionProcessor(ApplicationState& app, DomainState& domain, Logger& logger,
                                         AIManager& aiManager, IProcessor& inventory,
                                         SerializationManager& serialization, AutoSaveManager& async)
    -> std::unique_ptr<IProcessor>
{
    using GameEnums::MainChoice;
    auto decision = std::make_unique<DecisionProcessor>(app, domain, aiManager);
    decision->AddAction(MainChoice::HEAL, std::make_unique<Heal>(app, domain, logger));
    decision->AddAction(MainChoice::SHOOT, std::make_unique<Shoot>(app, domain, logger));
    auto& loop = app.GetGameLoopState();
    decision->AddAction(MainChoice::USE_ITEM, std::make_unique<UseItem>(inventory, app.GetDecisionState(), loop));
    decision->AddAction(MainChoice::EXIT, std::make_unique<Exit>(loop));
    decision->AddAction(MainChoice::SAVE, std::make_unique<SaveGame>(app, domain, logger, serialization));
    decision->AddAction(MainChoice::LOAD, std::make_unique<LoadGame>(app, domain, logger, serialization));
    decision->AddAction(MainChoice::CHANGE_DIFFICULTY, std::make_unique<ChangeDifficulty>(app, logger, aiManager));
    decision->AddAction(MainChoice::CHANGE_SERIALIZATION,
                        std::make_unique<ChangeSerialization>(app, logger, serialization));
    decision->AddAction(MainChoice::AUTOSAVE, std::make_unique<AutoSave>(app, domain, logger, async));
    return decision;
}

auto GameBuilder::BuildUIManager(ApplicationState& app, const DomainState& domain, Logger& logger,
                                 GameEnums::UIType uiChoice) -> UIManager
{
    auto uim = UIManager();
    if (uiChoice == GameEnums::UIType::CONSOLE)
    {
        auto initializer = std::make_unique<ConsoleInitializer>(logger);
        auto renderer = std::make_unique<ConsoleRenderer>(app, domain, logger);
        auto provider = std::make_unique<ConsoleProvider>(app.GetDecisionState(), app.GetGameLoopState());
        auto consoleUI = std::make_unique<ConsoleUI>(std::move(initializer), std::move(renderer), std::move(provider));
        uim.AddUIType(GameEnums::UIType::CONSOLE, std::move(consoleUI));
    }
    else
    {
        const auto windowSize = sf::Vector2u(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT);
        const auto windowMode = sf::VideoMode(windowSize);
        auto window = std::make_unique<sf::RenderWindow>(windowMode, "Roulette", sf::Style::Default);
        auto initializer = std::make_unique<SFMLInitializer>(*window);
        auto renderer = std::make_unique<SFMLRenderer>(app, domain, logger, *initializer, *window);
        auto provider = std::make_unique<SFMLProvider>(app, *initializer, *window);
        auto sfmlUI = std::make_unique<SFMLUI>(std::move(initializer), std::move(renderer), std::move(provider),
                                               std::move(window));
        uim.AddUIType(GameEnums::UIType::SFML, std::move(sfmlUI));
#ifdef _WIN32
        ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
    }
    uim.SetUIType(uiChoice);
    return uim;
}

auto GameBuilder::BuildSerializationManager(SerializationValidator& validator,
                                            GameEnums::SerializationFormat serializationChoice)
    -> std::unique_ptr<SerializationManager>
{
    auto serialization = std::make_unique<SerializationManager>();
    SerializationMethodStruct smsJSON(std::make_unique<JSONSerializer>(), std::make_unique<JSONDeserializer>(validator),
                                      &validator);
    SerializationMethodStruct smsTXT(std::make_unique<TXTSerializer>(), std::make_unique<TXTDeserializer>(validator),
                                     &validator);

    serialization->AddSerializationMethod(GameEnums::SerializationFormat::JSON, std::move(smsJSON));
    serialization->AddSerializationMethod(GameEnums::SerializationFormat::TXT, std::move(smsTXT));
    serialization->SetSerializationMethod(serializationChoice);
    return serialization;
}

auto GameBuilder::BuildAsyncSerializer(SerializationManager& serialization) -> AutoSaveManager
{
    return AutoSaveManager(serialization);
}

auto GameBuilder::BuildGameLoopManager(ApplicationState& app, DomainState& domain, AutoSaveManager& async,
                                       Logger& logger) -> GameLoopManager
{
    return {app,
            domain,
            async,
            std::make_unique<GameLoopInitializer>(app, domain),
            std::make_unique<RoundInitializer>(domain.GetComputerInventory(), domain.GetHumanInventory(),
                                               domain.GetMagazine()),
            logger};
}

auto GameBuilder::BuildSerializationValidator() -> SerializationValidator
{
    return {};
}

auto GameBuilder::BuildUILogger() -> std::unique_ptr<Logger>
{
    return std::make_unique<UILogger>();
}

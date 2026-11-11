#include "AIManager.h" // NOLINT(misc-include-cleaner)
#include "AIState.h"
#include "ApplicationState.h"
#include "AutoSave.h"
#include "AutoSaveManager.h"
#include "ChangeDifficulty.h"
#include "ChangeSerialization.h"
#include "ConsoleProvider.h"
#include "ConsoleRenderer.h"
#include "ConsoleUI.h"
#include "DecisionProcessor.h"
// NOLINTNEXTLINE(misc-include-cleaner)
#include "DecisionState.h" // IWYU pragma: keep
#include "Deserializer.h"
// NOLINTNEXTLINE(misc-include-cleaner)
#include "DomainState.h" // IWYU pragma: keep
#include "Exit.h"
#include "GameBuilder.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopInitializer.h"
#include "GameLoopManager.h"
#include "GameLoopState.h"
#include "Heal.h"
#include "IProcessor.h"
#include "InputValidator.h"
#include "JSONDeserializer.h"
#include "JSONSerializer.h"
#include "LoadGame.h"
// NOLINTNEXTLINE(misc-include-cleaner)
#include "Logger.h" // IWYU pragma: keep
#include "SFMLRenderer.h"
#include "SaveGame.h"
#include "SerializationManager.h"
#include "SerializationState.h"
#include "SerializationValidator.h"
#include "Serializer.h"
#include "Shoot.h"
#include "TXTDeserializer.h"
#include "TXTSerializer.h"
#include "UIManager.h"
#include "UseItem.h"
#include "Validator.h"
#include <boost/static_string/static_string.hpp>
#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <print>
#include <string_view>
#include <thread>

//    poprawic obsluge wyjatkow
//	  Zmniejszyć ilość powtarzalnego kodu
//    Dodać więcej testów i zabezpieczeń jak asserty
//    Zmienić struktury danych i pozbyć się zbędnej alokacji i komplikacji kodu
//    Zrobić porządek z namespaceami

namespace
{
inline auto RunMainLoop(GameLoopState& loopState, IProcessor& processor, GameLoopManager& loopManager,
                        UIManager& uiManager) -> void
{
    while (loopState.GetStateOfGameLoop() == GameEnums::YesNo::YES)
    {
        // const auto start = std::chrono::high_resolution_clock::now();
        auto next = std::chrono::steady_clock::now();
        if (loopState.GetStarter() == GameEnums::PlayerType::HUMAN)
        {
            uiManager.Render();
            if (loopState.GetRenderFlag() == GameEnums::YesNo::YES)
            {
                loopState.SetRenderFlag(GameEnums::YesNo::NO);
            }
            uiManager.GetInput();
        }
        processor.Process();
        loopManager.ProcessTurnEnd();
        next += std::chrono::milliseconds(GameConfig::SLEEP_FOR_MILLISECONDS);
        std::this_thread::sleep_until(next);

        /*const auto end = std::chrono::high_resolution_clock::now();
        const auto duration_us = duration_cast<std::chrono::microseconds>(end -
        start).count(); std::println("Loop time: {} us", duration_us);*/
    }
}

inline auto SetupGame(boost::static_string<GameConfig::MAX_FILENAME_LENGTH>& humanName, GameEnums::UIType& uiChoice,
                      GameEnums::SerializationFormat& serializationChoice, GameEnums::Difficulty& difficultyChoice)
    -> void
{
    const auto getNumericInput = [](std::string_view prompt, int lowerBand, int upperBand, auto type) -> auto {
        std::print("{}", prompt);
        const auto input =
            ConsoleProvider::GetValidatedInput(lowerBand, upperBand, InputValidator::IsValidNumericInput) - 1U;
        return static_cast<decltype(type)>(input);
    };

    std::print("Welcome to the game!\nEnter your name: ");
    humanName = ConsoleProvider::GetValidatedInput(InputValidator::IsValidFileName);
    std::print("\nChoose UI implementation:\n1. Console\n2. SFML\n");
    uiChoice = getNumericInput("Your choice (1 - 2): ", 1, 2, uiChoice);
    std::print("\nChoose Serialization format (Save/Load):\n1. TXT\n2. JSON\n");
    serializationChoice = getNumericInput("Your choice (1 - 2): ", 1, 2, serializationChoice);
    std::print("\nChoose Difficulty level implementation:\n1. Easy\n2. "
               "Normal\n3. Hard\n");
    difficultyChoice = getNumericInput("Your choice (1 - 3): ", 1, 3, difficultyChoice);
}
} // namespace

auto main() -> int
{
    try
    {
        boost::static_string<GameConfig::MAX_FILENAME_LENGTH> humanName;
        auto uiChoice = GameEnums::UIType::SFML;
        auto serializationChoice = GameEnums::SerializationFormat::JSON;
        auto difficultyChoice = GameEnums::Difficulty::NORMAL;
        SetupGame(humanName, uiChoice, serializationChoice, difficultyChoice);

        auto domain = GameBuilder::BuildDomainState(humanName, "Computer");
        auto app = GameBuilder::BuildApplicationState();
        app.GetAIState().SetDifficulty(difficultyChoice);

        app.GetSerializationState().SetSerializationType(serializationChoice);
        const auto logger = GameBuilder::BuildUILogger();
        auto uiManager = GameBuilder::BuildUIManager(app, domain, *logger, uiChoice);
        auto validator = GameBuilder::BuildSerializationValidator();
        const auto serialization = GameBuilder::BuildSerializationManager(validator, serializationChoice);
        auto async = GameBuilder::BuildAsyncSerializer(*serialization);
        auto aiManager = GameBuilder::BuildAIManager(app.GetDecisionState(), domain);
        aiManager.SetDifficulty(difficultyChoice);
        const auto inventory =
            GameBuilder::BuildInventoryProcessor(app.GetDecisionState(), app.GetGameLoopState(), domain, *logger);
        const auto decision =
            GameBuilder::BuildDecisionProcessor(app, domain, *logger, aiManager, *inventory, *serialization, async);
        auto loopManager = GameBuilder::BuildGameLoopManager(app, domain, async, *logger);
        RunMainLoop(app.GetGameLoopState(), *decision, loopManager, uiManager);
    }
    catch (const std::exception& e)
    {
        try
        {
            std::println(stderr, "The game will be closed.\nReason: {}", e.what());
        }
        catch (...)
        {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }
    catch (...)
    {
        try
        {
            std::println("The game will be closed. Unknown reason.");
        }
        catch (...)
        {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

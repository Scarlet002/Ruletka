#include "ForwardDeclarations.h"
#include "IGameEngine.h"
#include "GameEngine.h"
#include "GameEnums.h"
#include "GameConfig.h"
#include "AI.h"
#include "EasyAI.h"
#include "NormalAI.h"
#include "HardAI.h"
#include "AIManager.h"
#include "Serializer.h"
#include "JSONSerializer.h"
#include "TXTSerializer.h"
#include "AsyncSerializer.h"
#include "AutoSaveManager.h"
#include "SerializationManager.h"
#include "UI.h"
#include "Logger.h"
#include "UILogger.h"
#include "LogObserver.h"
#include "ConsoleUI.h"
#include "SFMLUI.h"
#include "IInventory.h"
#include "Inventory.h"
#include "HP.h"
#include "HPManager.h"
#include "Magazine.h"
#include "ShotgunMagazine.h"
#include "IPlayer.h"
#include "Player.h"
#include "Action.h"
#include "Cellphone.h"
#include "Inverter.h"
#include "Saw.h"
#include "Beer.h"
#include "Magnifier.h"
#include "Handcuffs.h"
#include "IGameState.h"
#include "GameState.h"
#include "Heal.h"
#include "Shoot.h"
#include "Exit.h"
#include "ChangeDifficulty.h"
#include "ChangeSerialization.h"
#include "SaveGame.h"
#include "LoadGame.h"
#include "AutoSave.h"
#include "Restart.h"
#include "Processor.h"
#include "UseItem.h"
#include "InventoryProcessor.h"
#include "DecisionProcessor.h"
#include "InputValidatorManager.h"
#include "GameLoopState.h"
#include "ItemState.h"
#include "DecisionState.h"
#include "Initializer.h"
#include "Validator.h"
#include "RoundInitializer.h"
#include "UIInitializer.h"
#include "GameLoopInitializer.h"
#include "GameLoopValidator.h"
#include "SerializationState.h"
#include "AIState.h"
#include <memory>
#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <utility>

// 
//    Urozmaicic UI, obie implementacje
//    Dodac testy jednostkowe i asserty, i wiecej zabezpieczen
//    Poprawic obsluge wyjatkow
//	  Obsluga wielu zabezpieczeeń, a nie ukrywanie problemu
//    Poprawić UI/UX, np dodac kursor dla logow, dodac liste zapisow
//	  Poprawic IPlayer
//	  Rozbic TurnManager
//	  Rozbic SFMLUI
//	  Zoptymalizowac SFMLUI
//    

int main()
{
    try
    {
		int8_t uiChoice = GameEnums::NO_CHOICE;
		int8_t serializationChoice = GameEnums::NO_CHOICE;
		int8_t difficultyChoice = GameEnums::NO_CHOICE;
		std::string humanName = "";

		if (humanName == "")
		{
			std::cout << "Witaj w grze!" << '\n';

			std::string input = InputValidatorManager::GetValidatedInput("Podaj swoja nazwe: ",
				InputValidatorManager::IsValidFileName);
			humanName = input;
		}

		if (uiChoice == GameEnums::NO_CHOICE)
		{
			std::cout << "Wybierz implementacje UI:" << '\n';
			std::cout << "1. Konsola" << '\n';
			std::cout << "2. SFML" << '\n';

			std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (1 - 2): ",
				InputValidatorManager::IsValidMainUIChoice);
			uiChoice = stoi(input);
		}

		if (serializationChoice == GameEnums::NO_CHOICE)
		{
			std::cout << "Wybierz implementacje Serializacji (Zapis/Odczyt):" << '\n';
			std::cout << "1. JSON" << '\n';
			std::cout << "2. TXT" << '\n';

			std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (1 - 2): ",
				InputValidatorManager::IsValidMainSerializationChoice);
			serializationChoice = stoi(input);
			serializationChoice -= 1;
		}

		if (difficultyChoice == GameEnums::NO_CHOICE)
		{
			std::cout << "Wybierz implementacje Poziomu Trudnosci:" << '\n';
			std::cout << "1. Normal" << '\n';
			std::cout << "2. Easy" << '\n';
			std::cout << "3. Hard" << '\n';

			std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (1 - 3): ",
				InputValidatorManager::IsValidMainDifficultyChoice);
			difficultyChoice = stoi(input);
			difficultyChoice -= 1;
		}

		std::shared_ptr<HP> humanHP = std::make_shared<HPManager>();
		std::shared_ptr<IInventory> hi = std::make_shared<Inventory>();
		hi->AddItemType(GameEnums::Item::HANDCUFFS, GameConfig::minItems);
		hi->AddItemType(GameEnums::Item::BEER, GameConfig::minItems);
		hi->AddItemType(GameEnums::Item::MAGNIFIER, GameConfig::minItems);
		hi->AddItemType(GameEnums::Item::SAW, GameConfig::minItems);
		hi->AddItemType(GameEnums::Item::CELLPHONE, GameConfig::minItems);
		hi->AddItemType(GameEnums::Item::INVERTER, GameConfig::minItems);

		std::shared_ptr<IPlayer> human = std::make_shared<Player>
								(std::move(humanHP), std::move(hi), humanName, "human");

		std::shared_ptr<HP> computerHP = std::make_shared<HPManager>();
		std::shared_ptr<IInventory> ci = std::make_shared<Inventory>();
		ci->AddItemType(GameEnums::Item::HANDCUFFS, GameConfig::minItems);
		ci->AddItemType(GameEnums::Item::BEER, GameConfig::minItems);
		ci->AddItemType(GameEnums::Item::MAGNIFIER, GameConfig::minItems);
		ci->AddItemType(GameEnums::Item::SAW, GameConfig::minItems);
		ci->AddItemType(GameEnums::Item::CELLPHONE, GameConfig::minItems);
		ci->AddItemType(GameEnums::Item::INVERTER, GameConfig::minItems);
		std::shared_ptr<IPlayer> computer = std::make_shared<Player>
								(std::move(computerHP), std::move(ci), "Computer", "computer");

		std::shared_ptr<Magazine> magazine = std::make_shared<ShotgunMagazine>();

		std::shared_ptr<GameLoopState> gls = std::make_shared<GameLoopState>();
		std::shared_ptr<DecisionState> ds = std::make_shared<DecisionState>();
		std::shared_ptr<AIState> ais = std::make_shared<AIState>();
		std::shared_ptr<ItemState> is = std::make_shared<ItemState>();
		std::shared_ptr<SerializationState> ss = std::make_shared<SerializationState>();

		std::shared_ptr<IGameState> gs = std::make_shared<GameState>
									(std::move(human), std::move(computer), std::move(magazine)
										, std::move(gls), std::move(is), std::move(ais), std::move(ds), std::move(ss));

		gs->GetAIState().SetDifficulty(difficultyChoice);
		gs->GetSerializationState().SetSerializationType(serializationChoice);

		std::shared_ptr<UI> ui;

		switch (uiChoice)
		{
		case GameEnums::CONSOLE:
			ui = std::make_shared<ConsoleUI>(gs);
			break;
		case GameEnums::SFML:
			ui = std::make_shared<SFMLUI>(gs);
			break;
		default:
			if (ui == nullptr) { ui = std::make_shared<SFMLUI>(gs); }
			break;
		}

		std::shared_ptr<Logger> logger = std::make_shared<UILogger>();
		logger->AddObservers(std::dynamic_pointer_cast<LogObserver>(ui));

		std::shared_ptr<SerializationManager> sm = std::make_shared<SerializationManager>();
		sm->AddSerializer(GameEnums::JSON, std::make_shared<JSONSerializer>());
		sm->AddSerializer(GameEnums::TXT, std::make_shared<TXTSerializer>());
		sm->SetSerializer(serializationChoice);

		std::shared_ptr<AsyncSerializer> as = std::make_shared<AutoSaveManager>(sm);

		std::shared_ptr<AIManager> aim = std::make_shared<AIManager>();
		aim->AddStrategy(GameEnums::EASY, std::make_shared<EasyAI>(gs));
		aim->AddStrategy(GameEnums::NORMAL, std::make_shared<NormalAI>(gs));
		aim->AddStrategy(GameEnums::HARD, std::make_shared<HardAI>(gs));
		aim->SetStrategy(difficultyChoice);

		std::shared_ptr<Processor> ip = std::make_shared<InventoryProcessor>(gs, logger, ui);
		ip->AddAction(GameEnums::HANDCUFFS, std::make_shared<Handcuffs>(gs, logger));
		ip->AddAction(GameEnums::BEER, std::make_shared<Beer>(gs, logger));
		ip->AddAction(GameEnums::MAGNIFIER, std::make_shared<Magnifier>(gs, logger));
		ip->AddAction(GameEnums::SAW, std::make_shared<Saw>(gs, logger));
		ip->AddAction(GameEnums::CELLPHONE, std::make_shared<Cellphone>(gs, logger));
		ip->AddAction(GameEnums::INVERTER, std::make_shared<Inverter>(gs, logger));

		std::shared_ptr<Processor> dp = std::make_shared<DecisionProcessor>(gs, aim, logger, ui);
		dp->AddAction(GameEnums::HEAL, std::make_shared<Heal>(gs, logger));
		dp->AddAction(GameEnums::SHOOT, std::make_shared<Shoot>(gs, logger));
		dp->AddAction(GameEnums::USEITEM, std::make_shared<UseItem>(std::move(ip)));
		dp->AddAction(GameEnums::EXIT, std::make_shared<Exit>(gs));
		dp->AddAction(GameEnums::SAVE, std::make_shared<SaveGame>(gs, logger, sm, ui));
		dp->AddAction(GameEnums::LOAD, std::make_shared<LoadGame>(gs, logger, sm, ui));
		dp->AddAction(GameEnums::DIFFICULTY, std::make_shared<ChangeDifficulty>(gs, logger, aim, ui));
		dp->AddAction(GameEnums::SERIALIZATION, std::make_shared<ChangeSerialization>(gs, logger, sm, ui));
		dp->AddAction(GameEnums::AUTOSAVE, std::make_shared<AutoSave>(gs, logger, as));
		dp->AddAction(GameEnums::RESTART, std::make_shared<Restart>(gs, ui));

		std::shared_ptr<Initializer> ri = std::make_shared<RoundInitializer>(gs);
		std::shared_ptr<Initializer> uii = std::make_shared<UIInitializer>(ui);
		std::shared_ptr<Initializer> gli = std::make_shared<GameLoopInitializer>(gs);
		std::shared_ptr<Validator> glv = std::make_shared<GameLoopValidator>(gs, as, gli, ri, ui);
		uii->Initialize();
		gli->Initialize();

        std::unique_ptr<IGameEngine> game = std::make_unique<GameEngine>
											(std::move(gs), std::move(ui), std::move(dp), std::move(glv));
		game->RunLoop();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Gra zostanie zamknieta." << '\n';
        std::cerr << "Powod: " << e.what() << '\n';
		std::cin.get();

        return 1;
    }
    catch (...)
    {
        std::cerr << "Gra zostanie zamknieta." << '\n';
		std::cin.get();

        return 1;
    }
    return 0;
}
#include "GameConsoleVersion.h"
#include "UiManager.h"
#include "Player.h"
#include "HpManager.h"
#include "AiManager.h"
#include "SaveTXTManager.h"
#include "SaveJSONManager.h"
#include "LoadTXTManager.h"
#include "LoadJSONManager.h"
#include "AutoSaveManager.h"
#include "GameConfig.h"
#include "GameState.h"
#include "GameEnums.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>

using std::string;
using std::unique_ptr;
using std::make_unique;

GameConsoleVersion::GameConsoleVersion(LoadJSONManager& loaderJSON, SaveJSONManager& saverJSON)
    : magazine(gameConfig), gameStateManager(gameConfig),
    human("Czlowiek", "human", gameConfig), computer("Komputer", "computer", gameConfig), log({}),
    gameState(static_cast<IPlayer&>(human),
        static_cast<IPlayer&>(computer),
        static_cast<IMagazineManager&>(magazine),
        static_cast<IGameStateManager&>(gameStateManager),
        gameConfig,
        static_cast<IAiManager&>(ai),
        log),
    loaderJSON(loaderJSON), saverJSON(saverJSON)
{
    asyncSaver = make_unique<AutoSaveManager>(saverJSON, gameState);
};

void GameConsoleVersion::NewRound(GameState& gameState, const UiManager& ui)
{
    ui.EndOfBullets();
    gameState.magazine.Reload();
    gameState.human.GetRandomItem(gameState);
    gameState.human.GetNumberOfItems(gameState);
    gameState.computer.GetRandomItem(gameState);
    gameState.computer.GetNumberOfItems(gameState);
    ui.ScrollScreen();
    ui.Clear();
    ui.DisplayStats(gameState);
}

bool GameConsoleVersion::WhoWon(const GameState& gameState, const UiManager& ui)
{
    if (!gameState.human.isAlive())
    {
        asyncSaver->SetSaveCounter(0);
        ui.ComputerWin();
        return true;
    }
    else if (!gameState.computer.isAlive())
    {
        asyncSaver->SetSaveCounter(0);
        ui.HumanWin();
        return true;
    }
    return false;
}

void GameConsoleVersion::StartGame()
{
    gameState.human.ResetHP();
    gameState.computer.ResetHP();
    gameState.magazine.Reload();
    gameState.human.ResetInventory(gameState);
    gameState.computer.ResetInventory(gameState);
    gameState.gameStateManager.RandomizeStarter();
    gameState.gameStateManager.SetStateOfHandCuffs(false);
    gameState.log.resize(0);
    asyncSaver->SetSaveCounter(0);
	ui.Clear();
    ui.DisplayStats(gameState);

    while (true)
    {
        if (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN)
        {
            asyncSaver->SaveGameStateAsync(gameState, autoSaveFileName);
            ui.AutoSaveDone();
            ui.ShowAutoSaveName(autoSaveFileName);
            ui.Menu();
            if (gameState.log.size() != 0)
            {
                for (int i = 0; i < gameState.log.size(); i++)
                {
                    if (i != 0) 
                    { 
                        if (i % gameConfig.maxLogsInLine == 0) { std::cout << std::endl; }
                        std::cout << " -> ";
                    }
                    std::cout << gameState.log[i];
                }
            }
            gameState.log.resize(0);
            ui.NewLine();
            gameState.human.MakeDecision(gameState);

            if (gameStateManager.GetChoice() == GameEnums::SHOOT)
            {
                gameState.gameStateManager.SetShooter(GameEnums::SHOOTER_HUMAN);
                gameState.gameStateManager.SetTarget(GameEnums::TARGET_COMPUTER);
                gameState.human.Shoot(gameState);
                ui.ShowPointer();
                gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);
                if (gameState.gameStateManager.GetStateOfHandCuffs() == false)
                {
                    gameState.gameStateManager.SetStarter(GameEnums::STARTER_COMPUTER);
                }
                else
                {
                    gameState.gameStateManager.SetStateOfHandCuffs(false);
                }
            }
            else if (gameState.gameStateManager.GetChoice() == GameEnums::HEAL)
            {
                gameState.gameStateManager.SetShooter(GameEnums::SHOOTER_HUMAN);
                gameState.gameStateManager.SetTarget(GameEnums::TARGET_HUMAN);
                gameState.human.Shoot(gameState);
                ui.ShowPointer();
                gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);
                if (gameState.gameStateManager.GetStateOfHandCuffs() == false)
                {
                    gameState.gameStateManager.SetStarter(GameEnums::STARTER_COMPUTER);
                }
                else
                {
                    gameState.gameStateManager.SetStateOfHandCuffs(false);
                }
            }
            else if (gameState.gameStateManager.GetChoice() == GameEnums::USEITEM)
            {
                ui.InventoryMenu();
                ui.InputItemChoice(gameState);
                ui.ItemUseSuccesHuman(gameState);
                gameState.human.GetNumberOfItems(gameState);
                ui.ShowPointer();
            }
            else if (gameState.gameStateManager.GetChoice() == GameEnums::SAVE)
            {
                ui.InputSaveJSON(fileName);
                saverJSON.SaveGameState(gameState, fileName);
                ui.SavingSucces();
                ui.ShowPointer();
            }
            else if (gameState.gameStateManager.GetChoice() == GameEnums::LOAD)
            {
                ui.InputLoadJSON(fileName);
                loaderJSON.LoadGameState(gameState, fileName);
                ui.LoadingSucces();
                ui.ShowPointer();

            }
            else if (gameState.gameStateManager.GetChoice() == GameEnums::DIFFICULTY)
            {
                ui.DifficultyMenu();
                ui.InputdifficultyLevel(gameState);
                ui.DifficultyChangeSucces();
                ui.ShowPointer();
            }
            else
            {
                ui.Clear();
                ui.ThankYou();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
            }
        }
        else
        {
            ui.ComputerChoosing();
            gameState.computer.MakeDecision(gameState);

            if (gameState.gameStateManager.GetChoice() == GameEnums::SHOOT)
            {
                gameState.gameStateManager.SetShooter(GameEnums::SHOOTER_COMPUTER);
                gameState.gameStateManager.SetTarget(GameEnums::TARGET_HUMAN);
                gameState.computer.Shoot(gameState);
                gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);
                if (gameState.gameStateManager.GetStateOfHandCuffs() == false)
                {
                    gameState.gameStateManager.SetStarter(GameEnums::STARTER_HUMAN);
                }
                else
                {
                    gameState.gameStateManager.SetStateOfHandCuffs(false);
                }
                ui.NewLine();
            }
            else
            {
                gameState.gameStateManager.SetShooter(GameEnums::SHOOTER_COMPUTER);
                gameState.gameStateManager.SetTarget(GameEnums::TARGET_COMPUTER);
                gameState.computer.Shoot(gameState);
                gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);
                if (gameState.gameStateManager.GetStateOfHandCuffs() == false)
                {
                    gameState.gameStateManager.SetStarter(GameEnums::STARTER_HUMAN);
                }
                else
                {
                    gameState.gameStateManager.SetStateOfHandCuffs(false);
                }
                ui.NewLine();
            }
        }
        ui.Clear();
        ui.DisplayStats(gameState);

        if (WhoWon(gameState, ui)) {
            if (!ui.WantsToContinue(gameState))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
            }
        }

        if (gameState.magazine.IsOutOfBullets())
            NewRound(gameState, ui);
    }
}

GameConsoleVersion::~GameConsoleVersion() {};
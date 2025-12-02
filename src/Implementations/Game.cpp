#include "Game.h"
#include "Player.h"
#include "HpManger.h"
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

using std::string;

Game::Game(LoadJSONManager& loaderJSON, SaveJSONManager& saverJSON)
    : humanHP(gameConfig), computerHP(gameConfig),
    human("czlowiek", "czlowiek", humanHP), computer("komputer", "komputer", computerHP),
    gameState(human, computer, magazine, gameStateManager, gameConfig, ai),
    loaderJSON(loaderJSON), saverJSON(saverJSON)
{
          asyncSaver = new AutoSaveManager(saverJSON, gameState);
};

void Game::NewRound(GameState& gameState, const UiManager& ui)
{
    ui.EndOfBullets();
    gameState.magazine.Reload();
    ui.DisplayStats(gameState);
}

bool Game::WhoWon(const Player& human, const Player& computer, const UiManager& ui)
{
    if (!human.isAlive())
    {
        ui.ComputerWin();
        return true;
    }
    else if (!computer.isAlive())
    {
        ui.HumanWin();
        return true;
    }
    return false;
}

void Game::StartGame()
{
    gameState.human.ResetHP();
    gameState.computer.ResetHP();
    gameState.magazine.Reload();
    gameState.gameStateManager.RundomizeStarter();
    ui.DisplayStats(gameState);

    while (true)
    {
        if (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN)
        {
            asyncSaver->SaveGameStateAsync(gameState, autoSaveFileName);
            ui.AutoSaveDone();
            ui.ShowAutoSaveName(autoSaveFileName);
            ui.NewLine();
            ui.Menu();
            gameState.human.MakeDecision(gameState);

            if (gameStateManager.GetChoice() == GameEnums::SHOOT)
            {   
                gameState.gameStateManager.SetShooter(GameEnums::SHOOTER_HUMAN);
                gameState.gameStateManager.SetTarget(GameEnums::TARGET_COMPUTER);
                gameState.human.Shoot(gameState);
                ui.ShowPointer();
                gameState.gameStateManager.SetStarter(GameEnums::STARTER_COMPUTER);
            }
            else if (gameState.gameStateManager.GetChoice() == GameEnums::HEAL)
            {
                gameState.gameStateManager.SetShooter(GameEnums::SHOOTER_HUMAN);
                gameState.gameStateManager.SetTarget(GameEnums::STARTER_HUMAN);
                gameState.human.Shoot(gameState);
                ui.ShowPointer();
                gameStateManager.SetStarter(GameEnums::STARTER_COMPUTER);
            }
            else if (gameState.gameStateManager.GetChoice() == GameEnums::SAVE)
            {
                ui.InputSaveJSON(fileName);
                saverJSON.SaveGameState(gameState, fileName);
                ui.DisplayStats(gameState);
                ui.SavingSucces();
                ui.ShowPointer();
            }
            else if (gameState.gameStateManager.GetChoice() == GameEnums::LOAD)
            {
                ui.InputLoadJSON(fileName);
                loaderJSON.LoadGameState(gameState, fileName);
                ui.LoadingSucces();
                ui.DisplayStats(gameState);
                ui.ShowPointer();

            }
            else if (gameState.gameStateManager.GetChoice() == GameEnums::DIFFICULTY)
            {
                ui.DifficultyMenu();
                ui.InputdifficultyLevel(gameState);
                ui.DisplayStats(gameState);
                ui.DifficultyChangeSucces();
                ui.ShowPointer();
            }
            else
            {
                ui.InvalidInput();
                ui.ShowPointer();
            }
        }
        else
        {
            ui.ComputerChoosing();
            gameState.computer.MakeDecision(gameState);

            if (gameState.gameStateManager.GetChoice() == GameEnums::SHOOT)
            {
                gameState.gameStateManager.SetShooter(GameEnums::SHOOTER_COMPUTER);
                gameState.gameStateManager.SetTarget(GameEnums::STARTER_HUMAN);
                gameState.computer.Shoot(gameState);
                ui.NewLine();
            }
            else
            {
                gameState.gameStateManager.SetShooter(GameEnums::SHOOTER_COMPUTER);
                gameState.gameStateManager.SetTarget(GameEnums::TARGET_COMPUTER);
                gameState.computer.Shoot(gameState);
                ui.NewLine();
            }
            gameState.gameStateManager.SetStarter(GameEnums::STARTER_HUMAN);
        }

        ui.DisplayStats(gameState);

        if (WhoWon(human, computer, ui)) {
            if (!ui.WantsToContinue(gameState))
            {
                break;
            }
            else
            {
                NewRound(gameState, ui);
            }
        }

        if (magazine.IsOutOfBullets())
            NewRound(gameState, ui);
    }
}

Game::~Game() {
    delete asyncSaver;
};
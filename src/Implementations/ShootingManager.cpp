#include "ShootingManager.h"
#include "GameState.h"
#include "GameEnums.h"
#include <iostream>
#include <stdexcept>

using std::runtime_error;
using std::cout;
using std::endl;
using std::exception;

void ShootingManager::Shoot(GameState& gameState)
{
    int target = gameState.gameStateManager.GetTarget();
    int shooter = gameState.gameStateManager.GetShooter();
    try
    {
        if (gameState.magazine.IsEmpty()) throw runtime_error("Brak pociskow w magazynku!");

        if (gameState.gameStateManager.GetChoice() == GameEnums::SHOOT)
        {
            if (gameState.magazine.IsEmptySlot())
            {
                //cout << "Pudlo!";
                if (target == GameEnums::SHOOTER_HUMAN)
                {
                    gameState.log.push_back("Komputer nie trafia!");
                }
                else
                {
                    gameState.log.push_back("Nie trafiasz!");
                }
                gameState.magazine.DecreaseEmptyCount();
            }
            else
            {
                if (target == GameEnums::SHOOTER_HUMAN)
                {
                    gameState.human.LoseHP(gameState);
                    gameState.log.push_back("Zostales trafiony!");
                }
                else
                {
                    gameState.computer.LoseHP(gameState);
                    gameState.log.push_back("Trafiles komputer!");
                }
                gameState.magazine.DecreaseFullCount();
                //cout << "Trafiony!";
            }
        }
        else
        {
            if (gameState.magazine.IsEmptySlot())
            {
                if ((shooter == GameEnums::SHOOTER_HUMAN ? gameState.human.GetHP() : gameState.computer.GetHP()) < gameState.gameConfig.maxPlayerHP)
                {
                    if (shooter == GameEnums::SHOOTER_HUMAN)
                    {
                        gameState.human.RegainHP();
                        gameState.log.push_back("Odzyskales 1 HP!");
                    }
                    else
                    {
                        gameState.computer.RegainHP();
                        gameState.log.push_back("Komputer odzyskal 1 HP!");
                    }
                    //cout << "Udalo sie odzyskac 1 HP!";
                }
                else
                {
                    //cout << "Masz juz max HP! Nie mozesz odzyskac zdrowia!";
                    if (shooter == GameEnums::SHOOTER_HUMAN)
                    {
                        gameState.log.push_back("Nie odzyskales HP bo masz MAXHP!");
                    }
                    else
                    {
                        gameState.log.push_back("Komputer nie odzyskal HP bo ma MAXHP!");
                    }
                }
                gameState.magazine.DecreaseEmptyCount();
            }
            else
            {
                if (shooter == GameEnums::SHOOTER_HUMAN)
                {
                    gameState.human.LoseHP(gameState);
                    gameState.log.push_back("Nie udalo sie odzyskac HP (straciles 1 HP)");
                }
                else
                {
                    gameState.computer.LoseHP(gameState);
                    gameState.log.push_back("Nie udalo sie odzyskac HP (komputer stracil 1 HP)!");
                }
                gameState.magazine.DecreaseFullCount();
            }
        }
        gameState.magazine.DecreaseBulletCount();
    }
    catch (const exception& e)
    {
        cout << "Blad strzalu: " << e.what() << endl;
        gameState.magazine.Reload();
    }
}
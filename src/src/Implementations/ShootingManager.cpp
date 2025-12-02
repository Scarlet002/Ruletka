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
                cout << "Pudlo!";
                gameState.magazine.DecreaseEmptyCount();
            }
            else
            {
                if (target == GameEnums::SHOOTER_HUMAN)
                {
                    gameState.human.LoseHP();
                }
                else
                {
                    gameState.computer.LoseHP();
                }
                gameState.magazine.DecreaseFullCount();
                cout << "Trafiony!";
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
                    }
                    else
                    {
                        gameState.computer.RegainHP();
                    }
                    cout << "Udalo sie odzyskac 1 HP!";
                }
                else
                    cout << "Masz juz max HP! Nie mozesz odzyskac zdrowia!";
                gameState.magazine.DecreaseEmptyCount();
            }
            else
            {
                if (shooter == GameEnums::SHOOTER_HUMAN)
                {
                    gameState.human.LoseHP();
                }
                else
                {
                    gameState.computer.LoseHP();
                }
                gameState.magazine.DecreaseFullCount();
                cout << "Nie udalo sie odzyskac HP i straciles 1 HP!";
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
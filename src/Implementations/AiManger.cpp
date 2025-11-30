#include "AiManager.h"
#include "GameState.h"
#include "GameEnums.h"
#include <iostream>

int AiManager::SetDifficulty(int newDifficulty)
{
    return difficulty = newDifficulty;;
}

int AiManager::GetDifficulty() const
{
    return difficulty;
}

void AiManager::EasyAI(GameState& gameState) const
{
    gameState.gameStateManager.SetChoice(rand() % 2);
}

void AiManager::NormalAI(GameState& gameState) const
{
    double hitChance = gameState.magazine.CalculateHitProbability();
    if (hitChance != 0.0)
    {
        gameState.gameStateManager.SetChoice(GameEnums::SHOOT);
    }
    else if (hitChance == 0.0)
    {
        gameState.gameStateManager.SetChoice(GameEnums::HEAL);
    }
}

void AiManager::HardAI(GameState& gameState) const
{
    if (gameState.magazine.CheckBulletType())
    {
        gameState.gameStateManager.SetChoice(GameEnums::SHOOT);
    }
    else if (!gameState.magazine.CheckBulletType())
    {
        gameState.gameStateManager.SetChoice(GameEnums::HEAL);
    }
}
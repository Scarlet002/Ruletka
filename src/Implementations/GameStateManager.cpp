#include "GameStateManager.h"
#include <cstdlib>

GameStateManager::GameStateManager(GameConfig& gameConfig) : gameConfig(gameConfig) {};

int GameStateManager::SetItem(int newItem)
{
    return item = newItem;
}

int GameStateManager::SetStarter(int newStarter)
{
    return starter = newStarter;
}

int GameStateManager::SetChoice(int newChoice)
{
    return choice = newChoice;
}

int GameStateManager::SetTarget(int newTarget)
{
    return target = newTarget;
}

int GameStateManager::SetShooter(int newShooter)
{
    return shooter = newShooter;
}

int GameStateManager::SetDamage(int newDamage)
{
    return damage = newDamage;
}

void GameStateManager::SetStateOfHandCuffs(bool newState)
{
    WereHandCuffsUsed = newState;
}

int GameStateManager::GetStarter() const
{
    return starter;
}

int GameStateManager::GetChoice() const
{
    return choice;
}

int GameStateManager::GetTarget() const
{
    return target;
}

int GameStateManager::GetShooter() const
{
    return shooter;
}

int GameStateManager::GetDamage() const
{
    return damage;
}

bool GameStateManager::GetStateOfHandCuffs() const
{
    return WereHandCuffsUsed == true;
}

int GameStateManager::RandomizeStarter()
{
    starter = rand() % gameConfig.numberOfBulletTypes;
    return starter;
}

int GameStateManager::GetItem() const
{
    return item;
}

void GameStateManager::ResetDamage()
{
    SetDamage(1);
}
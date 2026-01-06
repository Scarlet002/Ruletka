#include "GameStateManager.h"
#include <cstdlib>

GameStateManager::GameStateManager(GameConfig& gameConfig) : gameConfig(gameConfig) {};

void GameStateManager::SetItem(int newItem)
{
    item = newItem;
}

void GameStateManager::SetStarter(int newStarter)
{
    starter = newStarter;
}

void GameStateManager::SetChoice(int newChoice)
{
    choice = newChoice;
}

void GameStateManager::SetTarget(int newTarget)
{
    target = newTarget;
}

void GameStateManager::SetShooter(int newShooter)
{
    shooter = newShooter;
}

void GameStateManager::SetDamage(int newDamage)
{
    damage = newDamage;
}

void GameStateManager::SetStateOfHandCuffs(bool newState)
{
    WereHandCuffsUsed = newState;
}

void GameStateManager::SetLogLine(string newLogLine)
{
    LogLine = newLogLine;
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

int GameStateManager::GetItem() const
{
    return item;
}

bool GameStateManager::GetStateOfHandCuffs() const
{
    return WereHandCuffsUsed;
}

string GameStateManager::GetLogLine() const
{
    return LogLine;
}

int GameStateManager::RandomizeStarter()
{
    starter = rand() % gameConfig.numberOfPlayers;
    return starter;
}

void GameStateManager::ResetDamage()
{
    SetDamage(gameConfig.defaultDamage);
}
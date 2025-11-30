#include "GameStateManager.h"
#include <cstdlib>

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

int GameStateManager::RundomizeStarter()
{
    starter = rand() % 2;
    return starter;
}
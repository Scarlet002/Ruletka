#pragma once
#include "GameEnums.h"
#include "ForwardDeclarations.h"
#include "IGameStateManager.h"

class GameStateManager : IGameStateManager
{
private:

    int starter = GameEnums::STARTER_HUMAN;
    int choice = GameEnums::SHOOT;
    int target = GameEnums::TARGET_COMPUTER;
    int shooter = GameEnums::SHOOTER_HUMAN;

public:

    GameStateManager() {};

    int SetStarter(int newStarter) override;
    int SetChoice(int newChoice) override;
    int SetTarget(int newTarget) override;
    int SetShooter(int newShooter) override;
    int GetStarter() const override;
    int GetChoice() const override;
    int GetTarget() const override;
    int GetShooter() const override;
    int RundomizeStarter() override;

    ~GameStateManager() {};
};

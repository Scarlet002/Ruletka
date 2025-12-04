#pragma once
#include "GameEnums.h"
#include "GameConfig.h"
#include "ForwardDeclarations.h"
#include "IGameStateManager.h"

class GameStateManager : IGameStateManager
{
private:

    GameConfig& gameConfig;
    int starter = GameEnums::STARTER_HUMAN;
    int choice = GameEnums::SHOOT;
    int target = GameEnums::TARGET_COMPUTER;
    int shooter = GameEnums::SHOOTER_HUMAN;
    int item = GameEnums::NOITEMS;
    int damage = gameConfig.defaultDamage;
    bool WereHandCuffsUsed = false;

public:

    GameStateManager(GameConfig& gameConfig);

    int SetItem(int newItem) override;
    int SetStarter(int newStarter) override;
    int SetChoice(int newChoice) override;
    int SetTarget(int newTarget) override;
    int SetShooter(int newShooter) override;
    int SetDamage(int newDamage) override;
    void SetStateOfHandCuffs(bool newState) override;
    int GetStarter() const override;
    int GetChoice() const override;
    int GetTarget() const override;
    int GetShooter() const override;
    int GetDamage() const override;
    int GetItem() const override;
    bool GetStateOfHandCuffs() const override;
    int RandomizeStarter() override;
    void ResetDamage() override;

    ~GameStateManager() {};
};

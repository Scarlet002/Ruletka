#pragma once
#include "GameEnums.h"
#include "GameConfig.h"
#include "GameConfig.h"
#include "ForwardDeclarations.h"
#include "IGameStateManager.h"
#include <string>

using std::string;

class GameStateManager : public IGameStateManager
{
private:

    GameConfig& gameConfig;
    int starter = GameEnums::STARTER_HUMAN;
    int choice = GameEnums::NO_CHOICE;
    int target = GameEnums::TARGET_COMPUTER;
    int shooter = GameEnums::SHOOTER_HUMAN;
    int item = GameEnums::NO_ITEMS;
    int damage = gameConfig.defaultDamage;
    bool WereHandCuffsUsed = false;
    string LogLine = "";

public:

    GameStateManager(GameConfig& gameConfig);

    void SetItem(int newItem) override;
    void SetStarter(int newStarter) override;
    void SetChoice(int newChoice) override;
    void SetTarget(int newTarget) override;
    void SetShooter(int newShooter) override;
    void SetDamage(int newDamage) override;
    void SetStateOfHandCuffs(bool newState) override;
    void SetLogLine(string newLogLine) override;
    int GetStarter() const override;
    int GetChoice() const override;
    int GetTarget() const override;
    int GetShooter() const override;
    int GetDamage() const override;
    int GetItem() const override;
    bool GetStateOfHandCuffs() const override;
    string GetLogLine() const override;
    int RandomizeStarter() override;
    void ResetDamage() override;

    ~GameStateManager() {};
};
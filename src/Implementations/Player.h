#pragma once
#include "ForwardDeclarations.h"
#include "IPlayer.h"
#include "HpManger.h"
#include "ShootingManager.h"
#include "DecisionManger.h"
#include <string>

using std::string;

class Player : public IPlayer
{
private:
    //DecisionManager decision;
    //ShootingManager gun;
    HpManager& hp;
    string name;
    string type;

public:

    Player(const string& playerName, const string& playerType, HpManager& hpManager);

    void LoseHP() override;
    void RegainHP() override;
    void ResetHP() override;
    int GetHP() const override;
    void SetHP(int newHP) override;
    bool isAlive() const override;
    bool IsHuman() const override;
    bool IsComputer() const override;
    int MakeDecision(GameState& gameState) const override;
    void Shoot(GameState& gameState) override;

    ~Player() {};
};
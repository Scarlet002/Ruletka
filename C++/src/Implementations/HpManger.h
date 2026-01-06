#pragma once
#include "IHpManager.h"
#include "GameConfig.h"
#include "ForwardDeclarations.h"

class HpManager : public IHpManager
{
private:
    GameConfig& gameConfig;
    const int MAXHP;
    int currentHP;
public:

    HpManager(GameConfig& gameConfig);

    void LoseHP(GameState& gameState) override;
    void RegainHP() override;
    void ResetHP() override;
    int GetHP() const override;
    void SetHP(int newHP) override;

    ~HpManager() {};
};

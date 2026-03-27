#pragma once
#include "IHpManager.h"
#include "GameConfig.h"
#include <cstdint>

class HpManager : public IHpManager
{
private:
    int8_t currentHP = GameConfig::maxPlayerHP;
    const uint8_t maxHP = GameConfig::maxPlayerHP;
public:
    void SetHP(int newHP) override;
    void LoseHP(int damage) override;
    void RegainHP() override;
    void ResetHP() override;
    int GetHP() const override;
};

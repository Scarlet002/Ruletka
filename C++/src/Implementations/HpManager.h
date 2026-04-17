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
    void SetHP(uint8_t newHP) override;
    void LoseHP(uint8_t damage) override;
    void RegainHP() override;
    void ResetHP() override;
    int8_t GetHP() const override;
};

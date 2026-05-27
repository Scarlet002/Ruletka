#pragma once
#include "HP.h"
#include "GameConfig.h"
#include <cstdint>

class HPManager : public HP
{
private:
    int8_t currentHP = GameConfig::maxPlayerHP;
public:
    void SetHP(uint8_t newHP) override 
    { 
        if (newHP >= GameConfig::maxPlayerHP) currentHP = GameConfig::maxPlayerHP;
        else if (newHP <= GameConfig::minPlayerHP) currentHP = GameConfig::minPlayerHP;
		else currentHP = newHP;
    }

    void LoseHP(uint8_t damage) override 
    { 
        currentHP -= damage;
		if (currentHP < GameConfig::minPlayerHP) currentHP = GameConfig::minPlayerHP;
    }

    void RegainHP() override { if (currentHP < GameConfig::maxPlayerHP) currentHP++; }

    void ResetHP() override { currentHP = GameConfig::maxPlayerHP; }

    int8_t GetHP() const noexcept override { return currentHP; }
};

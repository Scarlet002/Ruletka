#include "HpManager.h"
#include <cstdint>

void HpManager::SetHP(uint8_t newHP) { currentHP = newHP; }

void HpManager::LoseHP(uint8_t damage) { if (currentHP > 0) { currentHP -= damage; } }

void HpManager::RegainHP() { if (currentHP > 0 && currentHP < maxHP) { currentHP++; } }

void HpManager::ResetHP() { currentHP = GameConfig::maxPlayerHP; }

int8_t HpManager::GetHP() const { return currentHP; }
#include "HpManager.h"

void HpManager::SetHP(int newHP) { currentHP = newHP; }
void HpManager::LoseHP(int damage) { if (currentHP > 0) { currentHP -= damage; } }
void HpManager::RegainHP() { if (currentHP > 0 && currentHP < maxHP) { currentHP++; } }
void HpManager::ResetHP() { currentHP = GameConfig::maxPlayerHP; }
int HpManager::GetHP() const { return currentHP; }
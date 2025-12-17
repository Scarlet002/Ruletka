#include "HpManger.h"
#include "GameConfig.h"
#include "GameState.h"

HpManager::HpManager(GameConfig& gameConfig)
    : gameConfig(gameConfig), MAXHP(gameConfig.maxPlayerHP), currentHP(gameConfig.maxPlayerHP) {
}

void HpManager::LoseHP(GameState& gameState) 
{ 
    int damage = gameState.gameStateManager.GetDamage(); 
    if (currentHP > 0)
    {
        SetHP(GetHP() - damage);
    }
}
void HpManager::RegainHP()
{
    if (currentHP > 0 && currentHP < MAXHP)
        currentHP++;
}
void HpManager::ResetHP() { currentHP = MAXHP; }
int HpManager::GetHP() const { return currentHP; }
void HpManager::SetHP(int newHP) { currentHP = newHP; }
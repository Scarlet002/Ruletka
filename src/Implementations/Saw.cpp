#include "Saw.h"
#include "GameState.h"

void Saw::UseItem(GameState& gameState) { gameState.gameStateManager.SetDamage(gameState.gameConfig.sawDamage); }
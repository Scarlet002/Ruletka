#include "HandCuffs.h"
#include "GameState.h"

void HandCuffs::UseItem(GameState& gameState) { gameState.gameStateManager.SetStateOfHandCuffs(true); }
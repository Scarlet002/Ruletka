#include "Inverter.h"
#include "GameState.h"

void Inverter::UseItem(GameState& gameState) { gameState.magazine.InvertBulletType(); gameState.magazine.CheckBullets(); }
#include "Inverter.h"
#include "GameState.h"

void Inverter::UseItem(GameState& gameState) 
{ 
	gameState.magazine.InvertBulletType();
	gameState.magazine.CheckBullets();
	gameState.wasMagazineShown = true;
	if (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN)
	{
		gameState.log.push_back("Zmieniles typ naboju!");
	}
	else
	{
		gameState.log.push_back("Komputer zmienil typ naboju!");
	}
}
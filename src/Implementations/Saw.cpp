#include "Saw.h"
#include "GameState.h"

void Saw::UseItem(GameState& gameState) 
{ 
	gameState.gameStateManager.SetDamage(gameState.gameConfig.sawDamage);
	if (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN)
	{
		gameState.log.push_back("Uzyles pily (obrazenia razy 2)!");
	}
	else
	{
		gameState.log.push_back("Komputer uzyl pily (obrazenia razy 2)!");
	}
}
#include "HandCuffs.h"
#include "GameState.h"

void HandCuffs::UseItem(GameState& gameState) 
{ 
	gameState.gameStateManager.SetStateOfHandCuffs(true);
	if (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN)
	{
		gameState.log.push_back("Uzyles kajdanek!");
	}
	else
	{
		gameState.log.push_back("Komputer uzyl kajdanek!");
	}
}
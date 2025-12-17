#include "Beer.h"
#include "GameState.h"

void Beer::UseItem(GameState& gameState)
{
	if (gameState.magazine.CheckBulletType())
	{
		gameState.magazine.DecreaseFullCount();
		if (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN)
		{
			gameState.log.push_back("Uzyles piwa (usunieto pelna)!");
		}
		else
		{
			gameState.log.push_back("Komputer uzyl piwa (usunieto pelna)!");
		}
	}
	else
	{
		gameState.magazine.DecreaseEmptyCount();
		if (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN)
		{
			gameState.log.push_back("Uzyles piwa (usunieto pusta)!");
		}
		else
		{
			gameState.log.push_back("Komputer uzyl piwa (usunieto pusta)!");
		}
	}
	gameState.magazine.DecreaseBulletCount();
}
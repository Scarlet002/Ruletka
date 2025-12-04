#include "Beer.h"
#include "GameState.h"

void Beer::UseItem(GameState& gameState)
{
	if (gameState.magazine.CheckBulletType())
	{
		gameState.magazine.DecreaseFullCount();
	}
	else
	{
		gameState.magazine.DecreaseEmptyCount();
	}
	gameState.magazine.DecreaseBulletCount();
}
#include "Magnifier.h"
#include "GameState.h"
#include <iostream>

using std::cout;
using std::endl;

void Magnifier::UseItem(GameState& gameState)
{
	if (gameState.magazine.CheckBulletType())
	{
		if (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN)
		{
			gameState.log.push_back("Uzyles lupy (pelna)!");
		}
		else
		{
			gameState.log.push_back("Komputer uzyl lupy!");
		}
	}
	else
	{
		if (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN)
		{
			gameState.log.push_back("Uzyles lupy (pusta)!");
		}
		else
		{
			gameState.log.push_back("Komputer uzyl lupy!");
		}
	}
}
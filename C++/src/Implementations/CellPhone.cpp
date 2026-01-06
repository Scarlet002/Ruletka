#include "CellPhone.h"
#include "GameState.h"
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::to_string;

CellPhone::CellPhone() : bullet(bullet) {};

void CellPhone::UseItem(GameState& gameState) 
{
	bullet = rand() % gameState.magazine.GetMagazienSize();
	if ( gameState.magazine.CheckBulletTypeCellPhone(bullet) ) 
	{
		if (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN)
		{
			gameState.log.push_back("Uzyles telefonu (" + to_string(bullet + 1) + " pelna)!");
		}
		else
		{
			gameState.log.push_back("Komputer uzyl telefonu!");
		}
	}
	else
	{
		if (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN)
		{
			gameState.log.push_back("Uzyto telefonu (" + to_string(bullet + 1) + " pusta)!");
		}
		else
		{
			gameState.log.push_back("Komputer uzyl telefonu!");
		}
	}
}
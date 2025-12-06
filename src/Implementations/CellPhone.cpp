#include "CellPhone.h"
#include "GameState.h"
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

CellPhone::CellPhone() : bullet(bullet) {};

void CellPhone::UseItem(GameState& gameState) 
{
	bullet = rand() % gameState.magazine.GetMagazienSize();
	if ( gameState.magazine.CheckBulletTypeCellPhone(bullet) ) 
	{
		cout << bullet + 1 << " Pelna" << endl;
	}
	else
	{
		cout << bullet + 1 << " Pusta" << endl;
	}
}
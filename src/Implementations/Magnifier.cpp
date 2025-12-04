#include "Magnifier.h"
#include "GameState.h"
#include <iostream>

using std::cout;
using std::endl;

void Magnifier::UseItem(GameState& gameState) { gameState.magazine.CheckBulletType() ? cout << "Pelna" << endl : cout << "Pusta" << endl; }
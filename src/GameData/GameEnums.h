#pragma once
#include "ForwardDeclarations.h"

namespace GameEnums 
{
    enum Difficulty { EASY = 0, NORMAL = 1, HARD = 2 };
    enum Bullet { EMPTY = 0, FULL = 1 };
    enum Choice { HEAL = 0, SHOOT = 1, USEITEM = 2, EXIT = 3, SAVE = 4, LOAD = 5, DIFFICULTY = 6 };
    enum Starter { STARTER_COMPUTER = 0, STARTER_HUMAN = 1 };
    enum Target { TARGET_COMPUTER = 0, TARGET_HUMAN = 1 };
    enum Shooter { SHOOTER_COMPUTER = 0, SHOOTER_HUMAN = 1 };
    enum Item { NOITEMS = 0, HANDCUFFS = 1, BEER = 2, MAGNIFIER = 3, SAW = 4, CELLPHONE = 5, INVERTER = 6 };
}
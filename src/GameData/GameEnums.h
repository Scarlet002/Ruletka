#pragma once
#include "ForwardDeclarations.h"

namespace GameEnums {
    enum Difficulty { EASY = 0, NORMAL = 1, HARD = 2 };
    enum Bullet { EMPTY = 0, FULL = 1 };
    enum Choice { HEAL = 0, SHOOT = 1, SAVE = 5, LOAD = 6, DIFFICULTY = 7 };
    enum Starter { STARTER_COMPUTER = 0, STARTER_HUMAN = 1 };
    enum Target { TARGET_COMPUTER = 0, TARGET_HUMAN = 1 };
    enum Shooter { SHOOTER_COMPUTER = 0, SHOOTER_HUMAN = 1 };
}
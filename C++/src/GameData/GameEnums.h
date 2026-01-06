#pragma once
#include "ForwardDeclarations.h"

namespace GameEnums 
{
    enum Difficulty { EASY = 1000, NORMAL = 1001, HARD = 1002 };
    enum Bullet { EMPTY = 0, FULL = 1 };
    enum Choice { NO_CHOICE = -1, HEAL = 0, SHOOT = 1, USEITEM = 2, EXIT = 3, SAVE = 4, LOAD = 5, DIFFICULTY = 6 };
    enum Starter { STARTER_COMPUTER = 0, STARTER_HUMAN = 1 };
    enum Target { TARGET_COMPUTER = 0, TARGET_HUMAN = 1 };
    enum Shooter { SHOOTER_COMPUTER = 0, SHOOTER_HUMAN = 1 };
    enum Item { NO_ITEMS = 0, HANDCUFFS = 1, BEER = 2, MAGNIFIER = 3, SAW = 4, CELLPHONE = 5, INVERTER = 6 };
	enum SaveLoadMethod { SAVE_TXT = 0, LOAD_TXT = 1, SAVE_JSON = 2, LOAD_JSON = 3 };
	enum GameStateEnum { STATE_NOT_RUNNING = 0, STATE_RUNNING = 1, STATE_HUMAN_WIN = 2, STATE_COMPUTER_WIN = 3 };
	enum RestartChoice { RESTART_YES = 100, RESTART_NO = 101 };

}
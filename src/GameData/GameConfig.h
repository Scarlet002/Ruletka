#pragma once
#include "ForwardDeclarations.h"
#include "GameEnums.h"

struct GameConfig
{
    GameConfig() {};

    const int maxPlayerHP = 3;
    const int maxBullets = 8;
    const int minBullets = 1;
    const int defaultDifficulty = GameEnums::NORMAL;
    const int StarterPlayerHP = maxPlayerHP;

    ~GameConfig() {};
};
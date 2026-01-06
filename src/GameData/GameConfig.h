#pragma once
#include "ForwardDeclarations.h"
#include "GameEnums.h"

struct GameConfig
{
    GameConfig() {};

    int defaultDamage = 1;
    int sawDamage = 2;
    int maxPlayerHP = 5;
    int maxBullets = 7;
    int minBullets = 2;
    int maxItemsRand = 1;
    int minItemsRand = 1;
    int minSaws = 0;
    int minBeers = 0;
    int minHandCuffs = 0;
    int minCellPhones = 0;
    int minInverters = 0;
    int minMagnifiers = 0;
    int minNumberOfItems = 0;
    int maxInventorySize = 5;
    int numberOfItemTypes = 6;
    int numberOfBulletTypes = 2;
	int numberOfPlayers = 2;
    int minBulletsCount = 0;
    int maxLogsInLine = 3;
    GameEnums::Difficulty defaultDifficulty = GameEnums::NORMAL;
    int StarterPlayerHP = maxPlayerHP;

    ~GameConfig() {};
};
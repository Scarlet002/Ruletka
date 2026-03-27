#pragma once
#include "ForwardDeclarations.h"
#include "GameEnums.h"
#include <cstdint>

namespace GameConfig
{
    static constexpr GameEnums::Difficulty defaultDifficulty = GameEnums::NORMAL;
    static constexpr uint8_t defaultDamage = 1;
    static constexpr uint8_t sawDamage = 2;
    static constexpr uint8_t maxPlayerHP = 5;
    static constexpr uint8_t maxBullets = 7;
    static constexpr uint8_t minBullets = 2;
    static constexpr uint8_t maxItemsRand = 1;
    static constexpr uint8_t minItemsRand = 1;
    static constexpr uint8_t minSaws = 0;
    static constexpr uint8_t minBeers = 0;
    static constexpr uint8_t minHandCuffs = 0;
    static constexpr uint8_t minCellPhones = 0;
    static constexpr uint8_t minInverters = 0;
    static constexpr uint8_t minMagnifiers = 0;
    static constexpr uint8_t minNumberOfItems = 0;
    static constexpr uint8_t maxInventorySize = 5;
    static constexpr uint8_t minInventorySize = 0;
    static constexpr uint8_t numberOfItemTypes = 6;
    static constexpr uint8_t numberOfBulletTypes = 2;
    static constexpr uint8_t numberOfPlayers = 2;
    static constexpr uint8_t minBulletsCount = 0;
    static constexpr uint8_t maxLogsInLine = 2;
    static constexpr uint8_t maxBulletsCount = 8;
};
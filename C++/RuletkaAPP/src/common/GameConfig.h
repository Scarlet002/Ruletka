#pragma once
#include "ForwardDeclarations.h"
#include "GameEnums.h"
#include <cstdint>

namespace GameConfig
{
    // Observers
    constexpr uint8_t maxObservers = 1;

    // Difficulty settings
    constexpr uint8_t defaultDifficulty = GameEnums::NORMAL;

    // HP limits
    constexpr uint8_t maxPlayerHP = 5;
	constexpr uint8_t minPlayerHP = 0;

    // Item types
    constexpr uint8_t ItemTypes = 6;

    // Log limits
    constexpr uint8_t maxLogsRendered = 9;
    constexpr uint8_t maxLogs = maxLogsRendered * 3;

    // Number of players
    constexpr uint8_t maxPlayers = 1;

    // IInventory bands RNG
    constexpr uint8_t minItemTypeRNG = 1;
    constexpr uint8_t maxItemTypeRNG = 6;
    constexpr uint8_t maxItemsGained = 1;

    // IInventory limits
    constexpr uint8_t minItems = 0;
    constexpr uint8_t maxItemsFiveSlots = 5;

    // Damage bands
    constexpr uint8_t defaultDamage = 1;
    constexpr uint8_t sawDamage = 2;

    // Bullet types
    constexpr uint8_t bulletTypes = 2;

    // Magazine bands
    constexpr uint8_t minBullets = 0;
    constexpr uint8_t maxBullets = 8;

    // Bullet bands RNG
    constexpr uint8_t minBulletsRNG = 2;
    constexpr uint8_t maxBulletsRNG = 8;

    // AI decision bands
    constexpr uint8_t minEasyAI = 0;
    constexpr uint8_t maxEasyAI = 1;

    constexpr uint8_t minNormalAI = 0;
    constexpr uint8_t maxNormalAI = 6;

    constexpr uint8_t minHardAI = 0;
    constexpr uint8_t maxHardAI = 6;
};
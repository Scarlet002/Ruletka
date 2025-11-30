#pragma once
#include "Player.h"
#include "ForwardDeclarations.h"
#include "MagazineManager.h"
#include "GameStateManager.h"
#include "GameConfig.h"
#include "AiManager.h"
#include <memory>

struct GameState
{
    GameState(Player& human, Player& computer, MagazineManager& magazine, GameStateManager& gameStateManager, GameConfig& gameConfig, AiManager& ai);

    Player& human;
    Player& computer;
    MagazineManager& magazine;
    GameStateManager& gameStateManager;
    GameConfig& gameConfig;
    AiManager& ai;

    ~GameState() {};
};
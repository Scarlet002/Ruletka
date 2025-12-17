#pragma once
#include "Player.h"
#include "ForwardDeclarations.h"
#include "MagazineManager.h"
#include "GameStateManager.h"
#include "GameConfig.h"
#include "AiManager.h"
#include <memory>
#include <string>
#include <vector>

using std::string;
using std::vector;

struct GameState
{
    GameState(Player& human, Player& computer, MagazineManager& magazine, GameStateManager& gameStateManager, GameConfig& gameConfig, AiManager& ai, vector<string>& log);

    Player& human;
    Player& computer;
    MagazineManager& magazine;
    GameStateManager& gameStateManager;
    GameConfig& gameConfig;
    AiManager& ai;
    vector<string>& log;

    ~GameState() {};
};
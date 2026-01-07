#pragma once
#include "ForwardDeclarations.h"
#include "IPlayer.h"
#include "IAiManager.h"
#include "IGameStateManager.h"
#include "IMagazineManager.h"
#include "GameConfig.h"
#include <memory>
#include <string>
#include <vector>

using std::string;
using std::vector;

struct GameState
{
    GameState(IPlayer& human, IPlayer& computer, IMagazineManager& magazine,
        IGameStateManager& gameStateManager, GameConfig& gameConfig,
        IAiManager& ai, vector<string>& log);

    IPlayer& human;
    IPlayer& computer;
    IMagazineManager& magazine;
    IGameStateManager& gameStateManager;
    GameConfig& gameConfig;
    IAiManager& ai;
    vector<string>& log;

    bool waitingForPlayer;
    bool gameRunning;
    bool waitingForRestartChoice;
    bool wasAutoSaved;
	bool wasLogCleared;
    bool wasMagazineShown;
    bool isComputerTurn;
    GameEnums::GameStateEnum currentGameState;

    ~GameState() {};
};
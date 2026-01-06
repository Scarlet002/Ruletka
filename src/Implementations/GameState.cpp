#include "Player.h"
#include "GameState.h"
#include "ForwardDeclarations.h"
#include "MagazineManager.h"
#include "GameStateManager.h"
#include "GameConfig.h"
#include "AiManager.h"

GameState::GameState(Player& human, Player& computer,
    MagazineManager& magazine, GameStateManager& gameStateManager,
    GameConfig& gameConfig, AiManager& ai, vector<string>& log)

    : human(human), computer(computer), magazine(magazine),
    gameStateManager(gameStateManager), gameConfig(gameConfig),
    ai(ai), log(log), waitingForPlayer(true), isComputerTurn(false),
	gameRunning(true), waitingForRestartChoice(false), 
    wasAutoSaved(false), wasLogCleared(false),
    currentGameState(GameEnums::STATE_RUNNING) {
};
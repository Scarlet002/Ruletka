#include "GameState.h"

GameState::GameState(IPlayer& human, IPlayer& computer,
    IMagazineManager& magazine, IGameStateManager& gameStateManager,
    GameConfig& gameConfig, IAiManager& ai, vector<string>& log)

    : human(human), computer(computer), magazine(magazine),
    gameStateManager(gameStateManager), gameConfig(gameConfig),
    ai(ai), log(log), waitingForPlayer(true), isComputerTurn(false),
	gameRunning(true), waitingForRestartChoice(false), 
    wasAutoSaved(false), wasLogCleared(false), wasMagazineShown(false),
    currentGameState(GameEnums::STATE_RUNNING) {
};
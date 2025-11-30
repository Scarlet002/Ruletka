#include "Player.h"
#include "ForwardDeclarations.h"
#include "MagazineManager.h"
#include "GameStateManager.h"
#include "GameConfig.h"
#include "AiManager.h"

GameState::GameState(Player& human, Player& computer, MagazineManager& magazine, GameStateManager& gameStateManager, GameConfig& gameConfig, AiManager& ai)
    : human(human), computer(computer), magazine(magazine), gameStateManager(gameStateManager), gameConfig(gameConfig), ai(ai) {
};
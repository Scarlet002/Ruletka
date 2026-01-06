#pragma once
#include "GameState.h"
#include "Player.h"
#include "MagazineManager.h"
#include "GameStateManager.h"
#include "GameConfig.h"
#include "AiManager.h"
#include "SaveJSONManager.h"
#include "LoadJSONManager.h"
#include "AutoSaveManager.h"
#include <memory>
#include <string>
#include <vector>

class IGameSFML {
public:
    virtual void InitializeGame() = 0;
    virtual void ProcessPlayerAction(int action) = 0;
    virtual void ProcessComputerTurn() = 0;
    virtual void UseItem(int item) = 0;
    virtual void CheckGameConditions() = 0;
    virtual void SwitchTurn() = 0;
    virtual void Run() = 0;
    virtual void HandlePlayerChoice(int choice) = 0;
    virtual void HandleItemChoice(int item) = 0;
    virtual void HandleRestartChoice(int choice) = 0;
    virtual void HandleSaveLoadWithFilename(int action, const std::string& filename) = 0;
    virtual void HandleDifficultyChoice(int choice) = 0;

    virtual ~IGameSFML() = default;
};
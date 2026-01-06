#pragma once
#include "GameState.h"
#include "Player.h"
#include "MagazineManager.h"
#include "GameStateManager.h"
#include "GameConfig.h"
#include "AiManager.h"
#include "IGameSFML.h"
#include "SaveJSONManager.h"
#include "LoadJSONManager.h"
#include "AutoSaveManager.h"
#include "UiSFMLManager.h"
#include <memory>
#include <string>
#include <vector>

class GameSFMLVersion : public IGameSFML 
{

private:
    GameConfig gameConfig;
    MagazineManager magazine;
    GameStateManager gameStateManager;
    Player human;
    Player computer;
    AiManager ai;
    std::vector<std::string> log;

    LoadJSONManager& loaderJSON;
    SaveJSONManager& saverJSON;
    GameState gameState;

    std::unique_ptr<AutoSaveManager> asyncSaver;
    UiSFMLManager ui;

    bool gameRunning;
    std::string autoSaveFileName;
    std::string filename;

    bool playerTurn;
    bool gameOver;

public:
    GameSFMLVersion(LoadJSONManager& loaderJSON, SaveJSONManager& saverJSON);

    void InitializeGame() override;
    void ProcessPlayerAction(int action) override;
    void ProcessComputerTurn() override;
    void UseItem(int item) override;
    void CheckGameConditions() override;
    void SwitchTurn() override;
    void Run() override;
    void HandlePlayerChoice(int choice) override;
    void HandleItemChoice(int item) override;
    void HandleRestartChoice(int choice) override;
    void HandleSaveLoadWithFilename(int action, const std::string& filename) override;
    void HandleDifficultyChoice(int choice) override;

    ~GameSFMLVersion();
};
#pragma once
#include "ForwardDeclarations.h"
#include "IGame.h"
#include "AiManager.h"
#include "HpManager.h"
#include "AutoSaveManager.h"
#include "LoadJSONManager.h"
#include "SaveJSONManager.h"
#include "UiManager.h"
#include "Player.h"
#include "GameStateManager.h"
#include "MagazineManager.h"
#include "GameConfig.h"
#include "GameState.h"
#include <string>
#include <memory>

using std::string;
using std::unique_ptr;

class GameConsoleVersion : public IGame {
private:

    GameConfig gameConfig;

    MagazineManager magazine;
    GameStateManager gameStateManager;
    AiManager ai;
    Player human;
    Player computer;

    vector<string> log;

    GameState gameState;

    unique_ptr<AutoSaveManager> asyncSaver;
    UiManager ui;

    SaveJSONManager& saverJSON;
    LoadJSONManager& loaderJSON;

    string fileName = "";
    string autoSaveFileName = "";

public:
    GameConsoleVersion(LoadJSONManager& loaderJSON, SaveJSONManager& saverJSON);

    void NewRound(GameState& gameState, const UiManager& ui) override;
    bool WhoWon(const GameState& gameState, const UiManager& ui) override;
    void StartGame() override;

    ~GameConsoleVersion();
};
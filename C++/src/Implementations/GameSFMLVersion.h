//#pragma once
//#include "Player.h"
//#include "MagazineManager.h"
//#include "TurnContext.h"
//#include "GameConfig.h"
//#include "AIStrategyManager.h"
//#include "IGameEngine.h"
//#include "SaveJSONManager.h"
//#include "LoadJSONManager.h"
//#include "AutoSaveManager.h"
//#include "UiSFMLManager.h"
//#include <memory>
//#include <string>
//#include <vector>
//
//class GameSFMLVersion : public IGameEngine
//{
//private:
//    MagazineManager magazine;
//    TurnContext TurnContext;
//    Player human;
//    Player computer;
//    AIStrategyManager ai;
//    std::vector<std::string> log;
//
//    ILoadManager& loader;
//    ISaveSyncManager& saver;
//
//    std::unique_ptr<AutoSaveManager> asyncSaver;
//    UiSFMLManager ui;
//
//    bool gameRunning;
//    std::string autoSaveFileName;
//    std::string filename;
//
//    bool playerTurn;
//    bool gameOver;
//
//    inline void HandlePlayerChoice(int choice);
//    inline void HandleItemChoice(int item);
//    inline void HandleRestartChoice(int choice);
//    inline void HandleSaveLoadWithFilename(int action, const std::string& filename);
//    inline void HandleDifficultyChoice(int choice);
//    inline void InitializeGame();
//    inline void ProcessPlayerAction(int action);
//    inline void ProcessComputerTurn();
//    inline void UseItem(int item);
//    inline void CheckGameConditions();
//    inline void SwitchTurn();
//public:
//    GameSFMLVersion();
//
//    void Run() override;
//};
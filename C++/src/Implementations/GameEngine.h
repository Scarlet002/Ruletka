#pragma once
#include "ForwardDeclarations.h"
#include "GameState.h"
#include "IGameEngine.h"
#include "GameConfig.h"
#include <string>
#include <memory>

class GameEngine : public IGameEngine
{
private:
    GameState state;
    std::unique_ptr<ISaveSyncManager> saver;
    std::unique_ptr<ILoadManager> loader;
    std::unique_ptr<ISaveAsyncManager> asyncSaver;
    std::unique_ptr<IAIStrategyManager> ai;
    std::unique_ptr<IUiManager> ui;

    inline void NewRound();
    inline void Initialize();

    inline void ProcessTurn(IPlayer& turnHandler,
        IPlayer& target, bool& isRunning);

    inline void VerifyMagazine();
    inline void CheckGameConditions(bool& isRunning);

    inline void ChangeTurnHandler(IPlayer& turnHandlert);
    inline void CloseInventoryForAI(IPlayer& turnHandler);

    inline void ProcessHeal(IPlayer& turnHandler);
    inline void ProcessShot(IPlayer& turnHandler, IPlayer& target);

    inline void HandleAutosave();
    inline void HandleInventory(IPlayer& turnHandler);
    inline void HandleExit(bool& isRunning);
    inline void HandleSave();
    inline void HandleLoad();
    inline void HandleDifficulty();
	inline void HandleRestart(bool& isRunning);

    inline void HandleHandCuffs(IPlayer& turnHandler);
    inline void HandleBeer(IPlayer& turnHandler);
    inline void HandleMagnifier(IPlayer& turnHandler);
    inline void HandleSaw(IPlayer& turnHandler);
    inline void HandleCellPhone(IPlayer& turnHandler);
    inline void HandleInverter(IPlayer& turnHandler);
    inline void HandleMainMenu(IPlayer& turnHandler,
        IPlayer& target, bool& isRunning);
public:
    GameEngine();

    void Run() override;
};
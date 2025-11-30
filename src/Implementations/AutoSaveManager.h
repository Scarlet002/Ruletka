#pragma once
#include "ForwardDeclarations.h"
#include "ISaveAsyncManager.h"
#include "GameState.h"
#include "SaveJSONManager.h"
#include <future>

using std::future;

class AutoSaveManager : public ISaveAsyncManager {
private:
    future<void> saveFuture;
    bool isSaving = false;
    int saveCounter = 0;
    SaveJSONManager& saver;
    GameState& gameState;

public:
    AutoSaveManager(SaveJSONManager& saverRef, GameState& gameState);

    void SaveGameStateAsync(const GameState& gameState, string& autoSaveFileName) override;
    bool IsSaving() const override;

    ~AutoSaveManager() {};
};

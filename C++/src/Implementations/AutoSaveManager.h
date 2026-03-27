#pragma once
#include "ForwardDeclarations.h"
#include "ISaveAsyncManager.h"
#include "SaveJSONManager.h"
#include "GameState.h"
#include <future>
#include <cstdint>

class AutoSaveManager : public ISaveAsyncManager 
{
private:
    std::future<void> saveFuture;
    ISaveSyncManager& saver;
    uint8_t saveCounter = 0;
    std::atomic<bool> isSaving = false;
public:
    AutoSaveManager(ISaveSyncManager& saverRef);

    void SetSaveCounter(int newSaveCounter) override;
    void SaveGameStateAsync(GameState state) override;
	int GetSaveCounter() const override;
    bool IsSaving() const override;
};

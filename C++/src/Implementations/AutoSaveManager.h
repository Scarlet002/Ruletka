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
    std::atomic <uint8_t> saveCounter = 0;
    std::atomic<bool> isSaving = false;
public:
    AutoSaveManager(ISaveSyncManager& saverRef);

    void SetSaveCounter(uint8_t newSaveCounter) override;
    void SaveGameStateAsync(const GameState& state) override;
	uint8_t GetSaveCounter() const override;
    bool IsSaving() const override;
};

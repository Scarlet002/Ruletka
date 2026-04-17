#include "AutoSaveManager.h"
#include "SaveJSONManager.h"
#include "GameState.h"
#include <string>
#include <chrono>
#include <ctime>
#include <future>
#include <thread>
#include <cstdint>

AutoSaveManager::AutoSaveManager(ISaveSyncManager& saverRef) 
    : saver(saverRef) {}

void AutoSaveManager::SaveGameStateAsync(const GameState& state)
{
    isSaving.store(true);
	SetSaveCounter(GetSaveCounter() + 1);
    std::string autoSaveFileName = "autosave" + std::to_string(GetSaveCounter());
    saveFuture = std::async(std::launch::async, [this, &state, autoSaveFileName]()
    {
        GameState snapshot;
        snapshot.CopyStateToSnapshot(state);
        saver.SaveGameState(snapshot, autoSaveFileName);
        isSaving.store(false);
    });
}

bool AutoSaveManager::IsSaving() const { return isSaving; }

void AutoSaveManager::SetSaveCounter(uint8_t newSaveCounter) { saveCounter = newSaveCounter; }

uint8_t AutoSaveManager::GetSaveCounter() const { return saveCounter; }
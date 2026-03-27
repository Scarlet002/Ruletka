#include "AutoSaveManager.h"
#include "SaveJSONManager.h"
#include "GameState.h"
#include <string>
#include <chrono>
#include <ctime>
#include <future>

AutoSaveManager::AutoSaveManager(ISaveSyncManager& saverRef) 
    : saver(saverRef) {}

void AutoSaveManager::SaveGameStateAsync(GameState state)
{
    isSaving = true;
	SetSaveCounter(GetSaveCounter() + 1);
    std::string autoSaveFileName = "autosave" + std::to_string(GetSaveCounter()) + ".json";
    saveFuture = std::async(std::launch::async, [this, state = std::move(state), autoSaveFileName]()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        saver.SaveGameState(state, autoSaveFileName);
        isSaving = false;
    });
}
bool AutoSaveManager::IsSaving() const { return isSaving; }
void AutoSaveManager::SetSaveCounter(int newSaveCounter) { saveCounter = newSaveCounter; }
int AutoSaveManager::GetSaveCounter() const { return saveCounter; }
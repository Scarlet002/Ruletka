#include "AutoSaveManager.h"
#include "GameState.h"
#include "SaveJSONManager.h"
#include <string>
#include <chrono>
#include <ctime>
#include <future>

using std::to_string;
using std::async;
using std::string;
using std::launch;

AutoSaveManager::AutoSaveManager(SaveJSONManager& saverRef, GameState& gameState) : saver(saverRef), gameState(gameState), isSaving(false), saveCounter(0) {};

void AutoSaveManager::SaveGameStateAsync(const GameState& gameState, string& autoSaveFileName)
{
    isSaving = true;
	SetSaveCounter(GetSaveCounter() + 1);
    autoSaveFileName = "autosave" + to_string(GetSaveCounter()) + ".json";

    saveFuture = async(launch::async, [this, autoSaveFileName, gameState]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            saver.SaveGameState(gameState, autoSaveFileName);
            isSaving = false;
        }
    );
}

bool AutoSaveManager::IsSaving() const
{
    return isSaving;
}

void AutoSaveManager::SetSaveCounter(int newSaveCounter) { saveCounter = newSaveCounter; }
int AutoSaveManager::GetSaveCounter() const { return saveCounter; }
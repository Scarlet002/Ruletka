#pragma once
#include "ForwardDeclarations.h"
#include "ISaveSyncManager.h"
#include "GameState.h"
#include <string>

class SaveJSONManager : public ISaveSyncManager
{
public:

    SaveJSONManager() {};

    void SaveGameState(const GameState& gameState, const string& fileName) const override;

    ~SaveJSONManager() {};
};

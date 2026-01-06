#pragma once
#include "ForwardDeclarations.h"
#include "GameState.h"
#include <string>

class ISaveSyncManager
{
public:

    virtual void SaveGameState(const GameState& gameState, const string& fileName) const = 0;

    virtual ~ISaveSyncManager() = default;
};

#pragma once
#include "ForwardDeclarations.h"
#include "GameState.h"
#include <string>

using std::string;

class ISaveAsyncManager
{
public:

	virtual void SetSaveCounter(int newSaveCounter) = 0;
    virtual int GetSaveCounter() const = 0;
    virtual void SaveGameStateAsync(const GameState& gameState, string& autoSaveFileName) = 0;
    virtual bool IsSaving() const = 0;

    virtual ~ISaveAsyncManager() = default;
};

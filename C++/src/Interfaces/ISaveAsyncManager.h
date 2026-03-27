#pragma once
#include "GameState.h"

class ISaveAsyncManager
{
public:
	virtual void SetSaveCounter(int newSaveCounter) = 0;
    virtual int GetSaveCounter() const = 0;
    virtual void SaveGameStateAsync(GameState state) = 0;
    virtual bool IsSaving() const = 0;

    virtual ~ISaveAsyncManager() = default;
};

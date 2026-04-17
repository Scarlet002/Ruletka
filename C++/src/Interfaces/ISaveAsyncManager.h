#pragma once
#include "GameState.h"

class ISaveAsyncManager
{
public:
	virtual void SetSaveCounter(uint8_t newSaveCounter) = 0;
    virtual uint8_t GetSaveCounter() const = 0;
    virtual void SaveGameStateAsync(const GameState& state) = 0;
    virtual bool IsSaving() const = 0;

    virtual ~ISaveAsyncManager() = default;
};

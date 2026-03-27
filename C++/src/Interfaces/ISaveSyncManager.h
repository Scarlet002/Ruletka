#pragma once
#include "GameState.h"
#include <string>

class ISaveSyncManager
{
public:
    virtual void SaveGameState(const GameState& state,
        const std::string& fileName) const = 0;

    virtual ~ISaveSyncManager() = default;
};

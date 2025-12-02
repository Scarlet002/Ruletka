#pragma once
#include "ForwardDeclarations.h"
#include "GameState.h"
#include <string>

using std::string;

class ISaveAsyncManager
{
public:

    virtual void SaveGameStateAsync(const GameState& gameState, string& autoSaveFileName) = 0;
    virtual bool IsSaving() const = 0;

    virtual ~ISaveAsyncManager() = default;
};

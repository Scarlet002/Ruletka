#pragma once
#include "ForwardDeclarations.h"
#include "ISaveSyncManager.h"
#include <string>

class SaveJSONManager : public ISaveSyncManager
{
public:
    void SaveGameState(const GameState& state,
        const std::string& fileName) const override;
};

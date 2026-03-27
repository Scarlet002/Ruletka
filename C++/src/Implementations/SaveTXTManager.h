#pragma once
#include "ForwardDeclarations.h"
#include "ISaveSyncManager.h"
#include "GameState.h"
#include <string>

class SaveTXTManager : public ISaveSyncManager
{
public:
	void SaveGameState(const GameState& state,
		const std::string& fileName) const override;
};

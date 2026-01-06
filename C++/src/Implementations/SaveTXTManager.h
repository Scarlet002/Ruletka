#pragma once
#include "ForwardDeclarations.h"
#include "ISaveSyncManager.h"
#include "GameState.h"
#include <string>

class SaveTXTManager : public ISaveSyncManager
{
public:

	SaveTXTManager() {};

	void SaveGameState(const GameState& gameState, const string& fileName) const override;

	~SaveTXTManager() {};
};

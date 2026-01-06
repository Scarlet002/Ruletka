#pragma once
#include "ForwardDeclarations.h"
#include "ILoadManager.h"
#include "GameState.h"
#include <string>

class LoadTXTManager : public ILoadManager
{
public:

	LoadTXTManager() {};

	void LoadGameState(GameState& gameState, const string& fileName) const override;

	~LoadTXTManager() {};
};

#pragma once
#include "ForwardDeclarations.h"
#include "ILoadManager.h"
#include "GameState.h"
#include <string>

class LoadJSONManager : public ILoadManager
{
public:

	LoadJSONManager() {};

	void LoadGameState(GameState& gameState, const string& fileName) const override;

	~LoadJSONManager() {};
};

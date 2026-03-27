#pragma once
#include "ForwardDeclarations.h"
#include "ILoadManager.h"
#include "GameState.h"
#include <string>

class LoadTXTManager : public ILoadManager
{
public:
	void LoadGameState(GameState& state,
		const std::string& fileName) override;
};

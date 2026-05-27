#pragma once
#include "AI.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "GameConfig.h"
#include "RNG.h"

class EasyAI : public AI
{
private:
	std::shared_ptr<IGameState> gs;
public:
	explicit EasyAI(std::shared_ptr<IGameState> gs)
		: gs(gs) {};

	int8_t Decision() const override { return RNG::GetRN<uint8_t>(GameConfig::minEasyAI, GameConfig::maxEasyAI); };
};
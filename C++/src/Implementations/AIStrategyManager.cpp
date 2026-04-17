#include "AIStrategyManager.h"
#include "IAIStrategy.h"
#include "EasyAI.h"
#include "NormalAI.h"
#include "HardAI.h"
#include "GameState.h"
#include "GameEnums.h"
#include <cstdint>

AIStrategyManager::AIStrategyManager(const GameState& state) 
	: state(state) {}

void AIStrategyManager::SetStrategy(int8_t difficulty)
{
	switch (difficulty)
	{
	case GameEnums::NORMAL:
		strategy = std::make_unique<NormalAI>(state);
		break;
	case GameEnums::EASY:
		strategy = std::make_unique<EasyAI>(state);
		break;
	case GameEnums::HARD:
		strategy = std::make_unique<HardAI>(state);
		break;
	default:
		if (strategy == nullptr) { strategy = std::make_unique<NormalAI>(state); }
		break;
	}
}

int8_t AIStrategyManager::Decision() const { return strategy->Decision(); }
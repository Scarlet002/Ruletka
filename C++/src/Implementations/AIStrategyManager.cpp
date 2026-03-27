#include "AIStrategyManager.h"
#include "IAIStrategy.h"
#include "EasyAI.h"
#include "NormalAI.h"
#include "HardAI.h"
#include "GameState.h"
#include "GameEnums.h"

AIStrategyManager::AIStrategyManager(const GameState& state) 
	: state(state) {}

void AIStrategyManager::SetStrategy(int difficulty)
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
		strategy = std::make_unique<EasyAI>(state);
		break;
	}
}
int AIStrategyManager::MakeDecision() const { return strategy->MakeDecision(); }
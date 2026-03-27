#pragma once
#include "IAIStrategyManager.h"
#include "IAIStrategy.h"
#include "ForwardDeclarations.h"
#include "GameState.h"
#include <memory>
#include <cstdint>

class AIStrategyManager : public IAIStrategyManager
{
private:
	std::unique_ptr<IAIStrategy> strategy;
	const GameState& state;
public:
	AIStrategyManager(const GameState& state);

	void SetStrategy(int difficulty) override;
	int MakeDecision() const override;
};
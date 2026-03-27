#pragma once
#include "IAIStrategy.h"
#include "GameState.h"

class EasyAI : public IAIStrategy
{
private:
	const GameState& state;
public:
	explicit EasyAI(const GameState& state);

	int MakeDecision() const override;
};
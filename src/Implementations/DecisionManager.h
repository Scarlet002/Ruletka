#pragma once
#include "IDecisionManager.h"
#include "ForwardDeclarations.h"

class DecisionManager : public IDecisionManager
{
public:
	DecisionManager() {};

	int MakeDecision(GameState& gameState) const override;

	~DecisionManager() {};
};

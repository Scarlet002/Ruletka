#pragma once
#include "ForwardDeclarations.h"
#include "GameState.h"

class IDecisionManager
{
public:

    virtual int MakeDecision(GameState& gameState) const = 0;

    virtual ~IDecisionManager() = default;
};

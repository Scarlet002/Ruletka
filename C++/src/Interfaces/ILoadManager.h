#pragma once
#include "GameState.h"
#include "ForwardDeclarations.h"
#include <string>


class ILoadManager
{
public:

    virtual void LoadGameState(GameState& gameState, const string& fileName) const = 0;

    virtual ~ILoadManager() = default;
};

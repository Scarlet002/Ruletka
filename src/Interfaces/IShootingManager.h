#pragma once
#include "ForwardDeclarations.h"
#include "GameState.h"

class IShootingManager
{
public:

    virtual void Shoot(GameState& gameState) = 0;

    virtual ~IShootingManager() = default;
};

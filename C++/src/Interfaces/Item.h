#pragma once
#include "ForwardDeclarations.h"

class Item
{
public:

	virtual void UseItem(GameState& gameState) = 0;

	virtual ~Item() = default;
};


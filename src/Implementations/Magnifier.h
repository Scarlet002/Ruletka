#pragma once
#include "Item.h"
#include "ForwardDeclarations.h"

class Magnifier : public Item
{
public:

	Magnifier() {};

	void UseItem(GameState& gameState) override;

	~Magnifier() {};
};

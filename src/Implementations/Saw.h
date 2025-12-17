#pragma once
#include "Item.h"
#include "ForwardDeclarations.h"

class Saw : public Item
{
public:

	Saw() {};

	void UseItem(GameState& gameState) override;

	~Saw() {};
};

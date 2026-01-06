#pragma once
#include "Item.h"
#include "ForwardDeclarations.h"

class HandCuffs : public Item
{
public:

	HandCuffs() {};

	void UseItem(GameState& gameState) override;

	~HandCuffs() {};
};

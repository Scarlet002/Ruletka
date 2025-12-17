#pragma once
#include "ForwardDeclarations.h"
#include "Item.h"

class Beer : public Item
{
public:

	Beer() {};

	void UseItem(GameState& gameState) override;

	~Beer() {};
};

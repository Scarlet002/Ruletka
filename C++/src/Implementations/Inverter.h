#pragma once
#include "Item.h"
#include "ForwardDeclarations.h"

class Inverter : public Item
{
public:

	Inverter() {};

	void UseItem(GameState& gameState) override;

	~Inverter() {};
};

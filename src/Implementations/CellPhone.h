#pragma once
#include "Item.h"
#include "ForwardDeclarations.h"

class CellPhone : public Item
{
private:
	int bullet = 0;
public:

	CellPhone();

	void UseItem(GameState& gameState) override;

	~CellPhone() {};
};

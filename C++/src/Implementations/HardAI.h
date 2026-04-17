#pragma once
#include "ForwardDeclarations.h"
#include "IAIStrategy.h"
#include "GameState.h"
#include <cstdint>

class HardAI : public IAIStrategy
{
private:
	const GameState& state;

	inline int8_t ManageInventory(int8_t& choice) const;
	inline int8_t MakeSpaceInInventory() const;
	inline int8_t IfBulletIsFull() const;
	inline int8_t IfBulletIsEmpty() const;
public:
	HardAI(const GameState& state);

	int8_t Decision() const override;
};
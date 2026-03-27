#pragma once
#include "ForwardDeclarations.h"
#include "IAIStrategy.h"
#include "GameState.h"
#include <cstdint>

class HardAI : public IAIStrategy
{
private:
	const GameState& state;

	inline uint8_t ManageInventory(uint8_t& choice) const;
	inline int MakeSpaceInInventory() const;
	inline int IfBulletIsFull() const;
	inline int IfBulletIsEmpty() const;
public:
	HardAI(const GameState& state);

	int MakeDecision() const override;
};
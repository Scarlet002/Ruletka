#pragma once
#include "ForwardDeclarations.h"
#include "IAIStrategy.h"
#include "GameState.h"
#include <cstdint>

class NormalAI : public IAIStrategy
{
private:
	const GameState& state;

	inline uint8_t ManageInventory(uint8_t& choice) const;
	inline int IfChanceForFullIsGreater() const;
	inline int IfChanceForEmptyIsGreater() const;
public:
	NormalAI(const GameState& state);

	int MakeDecision() const override;
};
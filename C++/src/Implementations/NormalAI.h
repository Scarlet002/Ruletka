#pragma once
#include "ForwardDeclarations.h"
#include "IAIStrategy.h"
#include "GameState.h"
#include <cstdint>

class NormalAI : public IAIStrategy
{
private:
	const GameState& state;

	inline int8_t ManageInventory(int8_t& choice) const;
	inline int8_t IfChanceForFullIsGreater() const;
	inline int8_t IfChanceForEmptyIsGreater() const;
public:
	NormalAI(const GameState& state);

	int8_t Decision() const override;
};
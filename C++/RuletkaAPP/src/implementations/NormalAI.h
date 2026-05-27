#pragma once
#include "ForwardDeclarations.h"
#include "AI.h"
#include "IGameState.h"
#include <cstdint>

class NormalAI : public AI
{
private:
	const std::shared_ptr<IGameState> gs;

	int8_t ManageInventory(int8_t& choice) const noexcept;
	int8_t IfChanceForFullIsGreater() const noexcept;
	int8_t IfChanceForEmptyIsGreater() const noexcept;
public:
	explicit NormalAI(const std::shared_ptr<IGameState> gs);

	int8_t Decision() const override;
};
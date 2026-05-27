#pragma once
#include "ForwardDeclarations.h"
#include "AI.h"
#include "IGameState.h"
#include <cstdint>

class HardAI : public AI
{
private:
	const std::shared_ptr<IGameState> gs;

	int8_t ManageInventory(int8_t& choice) const noexcept;
	int8_t MakeSpaceInInventory() const noexcept;
	int8_t IfBulletIsFull() const noexcept;
	int8_t IfBulletIsEmpty() const noexcept;
public:
	explicit HardAI(const std::shared_ptr<IGameState> gs);

	int8_t Decision() const override;
};
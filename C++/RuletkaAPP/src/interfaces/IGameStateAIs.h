#pragma once
#include "ForwardDeclarations.h"

class IGameStateAIs 
{
protected:
	IGameStateAIs() = default;
public:
	IGameStateAIs(const IGameStateAIs&) = delete;
	IGameStateAIs& operator=(const IGameStateAIs&) = delete;

	IGameStateAIs(IGameStateAIs&&) = delete;
	IGameStateAIs& operator=(IGameStateAIs&&) = delete;

	// Non-const getters
	[[nodiscard]] virtual AIState& GetAIState() noexcept = 0;

	// Const getters
	[[nodiscard]] virtual const AIState& GetAIState() const noexcept = 0;

	virtual ~IGameStateAIs() = default;
};
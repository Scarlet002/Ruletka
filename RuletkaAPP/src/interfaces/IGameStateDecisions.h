#pragma once
#include "ForwardDeclarations.h"

class IGameStateDecisions
{
protected:
	IGameStateDecisions() = default;
public:
	IGameStateDecisions(const IGameStateDecisions&) = delete;
	IGameStateDecisions& operator=(const IGameStateDecisions&) = delete;

	IGameStateDecisions(IGameStateDecisions&&) = delete;
	IGameStateDecisions& operator=(IGameStateDecisions&&) = delete;

	// Non-const getters
	[[nodiscard]] virtual DecisionState& GetDecisionState() noexcept = 0;

	// Const getters
	[[nodiscard]] virtual const DecisionState& GetDecisionState() const noexcept = 0;

	virtual ~IGameStateDecisions() = default;
};
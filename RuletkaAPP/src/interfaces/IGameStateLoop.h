#pragma once
#include "ForwardDeclarations.h"

class IGameStateLoop
{
protected:
	IGameStateLoop() = default;
public:
	IGameStateLoop(const IGameStateLoop&) = delete;
	IGameStateLoop& operator=(const IGameStateLoop&) = delete;

	IGameStateLoop(IGameStateLoop&&) = delete;
	IGameStateLoop& operator=(IGameStateLoop&&) = delete;

	// Non-const getters
	[[nodiscard]] virtual GameLoopState& GetGameLoopState() noexcept = 0;

	// Const getters
	[[nodiscard]] virtual const GameLoopState& GetGameLoopState() const noexcept = 0;

	virtual ~IGameStateLoop() = default;
};
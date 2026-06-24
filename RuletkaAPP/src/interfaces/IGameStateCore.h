#pragma once
#include "ForwardDeclarations.h"
#include <memory>

class IGameStateCore
{
protected:
	IGameStateCore() = default;
public:
	IGameStateCore(const IGameStateCore&) = delete;
	IGameStateCore& operator=(const IGameStateCore&) = delete;

	IGameStateCore(IGameStateCore&&) = delete;
	IGameStateCore& operator=(IGameStateCore&&) = delete;

	// Snapshot
	[[nodiscard]] virtual std::shared_ptr<IGameState> CreateSnapshot() const = 0;

	virtual ~IGameStateCore() = default;
};
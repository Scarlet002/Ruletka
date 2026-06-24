#pragma once
#include "ForwardDeclarations.h"

class IGameStateSerializations
{
protected:
	IGameStateSerializations() = default;
public:
	IGameStateSerializations(const IGameStateSerializations&) = delete;
	IGameStateSerializations& operator=(const IGameStateSerializations&) = delete;

	IGameStateSerializations(IGameStateSerializations&&) = delete;
	IGameStateSerializations& operator=(IGameStateSerializations&&) = delete;

	// Non-const getters
	[[nodiscard]] virtual SerializationState& GetSerializationState() noexcept = 0;

	// Const getters
	[[nodiscard]] virtual const SerializationState& GetSerializationState() const noexcept = 0;

	virtual ~IGameStateSerializations() = default;
};
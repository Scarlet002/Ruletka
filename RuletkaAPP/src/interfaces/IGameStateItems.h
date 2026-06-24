#pragma once
#include "ForwardDeclarations.h"

class IGameStateItems
{
protected:
	IGameStateItems() = default;
public:
	IGameStateItems(const IGameStateItems&) = delete;
	IGameStateItems& operator=(const IGameStateItems&) = delete;

	IGameStateItems(IGameStateItems&&) = delete;
	IGameStateItems& operator=(IGameStateItems&&) = delete;

	// Non-const getters
	[[nodiscard]] virtual ItemState& GetItemState() noexcept = 0;

	// Const getters
	[[nodiscard]] virtual const ItemState& GetItemState() const noexcept = 0;

	virtual ~IGameStateItems() = default;
};
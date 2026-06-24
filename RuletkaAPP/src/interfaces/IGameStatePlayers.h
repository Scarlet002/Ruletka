#pragma once
#include "ForwardDeclarations.h"

class IGameStatePlayers
{
protected:
	IGameStatePlayers() = default;
public:
	IGameStatePlayers(const IGameStatePlayers&) = delete;
	IGameStatePlayers& operator=(const IGameStatePlayers&) = delete;

	IGameStatePlayers(IGameStatePlayers&&) = delete;
	IGameStatePlayers& operator=(IGameStatePlayers&&) = delete;

	// Non-const getters
	[[nodiscard]] virtual IPlayer& GetHuman() noexcept = 0;
	[[nodiscard]] virtual IInventory& GetHumanInventory() noexcept = 0;
	[[nodiscard]] virtual HP& GetHumanHP() noexcept = 0;
	[[nodiscard]] virtual IPlayer& GetComputer() noexcept = 0;
	[[nodiscard]] virtual IInventory& GetComputerInventory() noexcept = 0;
	[[nodiscard]] virtual HP& GetComputerHP() noexcept = 0;

	// Const getters
	[[nodiscard]] virtual const IPlayer& GetHuman() const noexcept = 0;
	[[nodiscard]] virtual const IInventory& GetHumanInventory() const noexcept = 0;
	[[nodiscard]] virtual const HP& GetHumanHP() const noexcept = 0;
	[[nodiscard]] virtual const IPlayer& GetComputer() const noexcept = 0;
	[[nodiscard]] virtual const IInventory& GetComputerInventory() const noexcept = 0;
	[[nodiscard]] virtual const HP& GetComputerHP() const noexcept = 0;

	virtual ~IGameStatePlayers() = default;
};
#pragma once
#include "ForwardDeclarations.h"

class IGameStateMagazine
{
protected:
	IGameStateMagazine() = default;
public:
	IGameStateMagazine(const IGameStateMagazine&) = delete;
	IGameStateMagazine& operator=(const IGameStateMagazine&) = delete;

	IGameStateMagazine(IGameStateMagazine&&) = delete;
	IGameStateMagazine& operator=(IGameStateMagazine&&) = delete;

	// Non-const getters
	[[nodiscard]] virtual Magazine& GetMagazine() noexcept = 0;

	// Const getters
	[[nodiscard]] virtual const Magazine& GetMagazine() const noexcept = 0;

	virtual ~IGameStateMagazine() = default;
};
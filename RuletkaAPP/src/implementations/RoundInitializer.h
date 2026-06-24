#pragma once
#include "Initializer.h"
#include "IGameState.h"
#include "Magazine.h"
#include "IInventory.h"
#include <memory>

class RoundInitializer : public Initializer
{
private:
	std::shared_ptr<IGameState> gs;
public:
	RoundInitializer(std::shared_ptr<IGameState> gs) : gs(gs) {}

	void Initialize() override
	{
		gs->GetMagazine().Reload();
		gs->GetHumanInventory().GetRandomItems();
		gs->GetComputerInventory().GetRandomItems();
	}
};
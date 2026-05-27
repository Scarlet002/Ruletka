#pragma once
#include "Initializer.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "DecisionState.h"
#include "GameLoopState.h"
#include "ItemState.h"
#include "HP.h"
#include "Magazine.h"
#include "IInventory.h"
#include <memory>

class GameLoopInitializer : public Initializer
{
private:
    std::shared_ptr<IGameState> gs;
public:
    GameLoopInitializer(std::shared_ptr<IGameState> gs) : gs(gs) {}

	void Initialize() override
	{
        gs->GetDecisionState().SetChoice(GameEnums::NO_CHOICE);
        gs->GetGameLoopState().SetStateOfGameLoop(true);
        gs->GetItemState().SetStateOfMagnifier(GameEnums::ITEM_NOT_USED);
        gs->GetItemState().SetStateOfCellPhone(GameEnums::ITEM_NOT_USED);
        gs->GetItemState().SetStateOfHandCuffs(GameEnums::ITEM_NOT_USED);
        gs->GetDecisionState().SetPreviousChoice(GameEnums::EXIT);
        gs->GetGameLoopState().SetIsOnePlayerAlive(false);
        gs->GetDecisionState().SetCurrentMenu(GameEnums::MAIN_MENU);
        gs->GetHumanHP().ResetHP();
        gs->GetComputerHP().ResetHP();
        gs->GetMagazine().Reload();
        gs->GetHumanInventory().ResetInventory();
        gs->GetComputerInventory().ResetInventory();
        gs->GetGameLoopState().RandomizeStarter();
	}
};
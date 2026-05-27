#include "NormalAI.h"
#include "IGameState.h"
#include "HPManager.h"
#include "IInventory.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "IPlayer.h"    
#include "ItemState.h"
#include "DecisionState.h"
#include "Magazine.h"
#include <cstdint>

NormalAI::NormalAI(const std::shared_ptr<IGameState> gs) : gs(gs) {};

int8_t NormalAI::IfChanceForFullIsGreater() const noexcept
{
    int8_t choice = GameEnums::NO_ITEMS;
    if (gs->GetHumanHP().GetHP() >= 2)
    {
        if (gs->GetComputerInventory().GetItemCount(GameEnums::HANDCUFFS) > 0
            && gs->GetItemState().GetStateOfHandCuffs() == GameEnums::ITEM_NOT_USED)
        {
            choice = GameEnums::HANDCUFFS;
            return choice;
        }
        else if (gs->GetMagazine().GetHitProbability() < 0.999
            && gs->GetComputerInventory().GetItemCount(GameEnums::MAGNIFIER) > 0
            && !gs->GetItemState().GetStateOfMagnifier())
        {
            choice = GameEnums::MAGNIFIER;
            return choice;
        }
        else if (gs->GetComputerInventory().GetItemCount(GameEnums::CELLPHONE) > 0
            && gs->GetMagazine().GetMagazineSize() == 2
            && gs->GetMagazine().GetHitProbability() < 0.999
            && !gs->GetItemState().GetStateOfCellPhone())
        {
            choice = GameEnums::CELLPHONE;
            return choice;
        }
        else if (gs->GetComputerInventory().GetItemCount(GameEnums::SAW) > 0
            && gs->GetItemState().GetDamage() == GameConfig::defaultDamage)
        {
            choice = GameEnums::SAW;
            return choice;
        }
        else
        {
            choice = GameEnums::NO_ITEMS;
            return choice;
        }
    }
    else if (gs->GetComputerHP().GetHP() == 1
        && gs->GetComputerInventory().GetItemCount(GameEnums::INVERTER) > 0
        && gs->GetMagazine().GetHitProbability() > 0.999)
    {
        choice = GameEnums::INVERTER;
        return choice;
    }
    else
    {
        choice = GameEnums::NO_ITEMS;
        return choice;
    }
}

int8_t NormalAI::IfChanceForEmptyIsGreater() const noexcept
{
    int8_t choice = GameEnums::NO_ITEMS;
    if (gs->GetHumanHP().GetHP() <= 2
        && gs->GetComputerInventory().GetItemCount(GameEnums::INVERTER) > 0)
    {
        choice = GameEnums::INVERTER;
        return choice;
    }
    if (gs->GetComputerInventory().GetItemCount(GameEnums::BEER) > 0
        && gs->GetComputerHP().GetHP() == GameConfig::maxPlayerHP)
    {
        choice = GameEnums::BEER;
        return choice;
    }
    else if (gs->GetMagazine().GetHitProbability() < 0.999
        && gs->GetComputerInventory().GetItemCount(GameEnums::MAGNIFIER) > 0
        && !gs->GetItemState().GetStateOfMagnifier())
    {
        choice = GameEnums::MAGNIFIER;
        return choice;
    }
    else if (gs->GetComputerInventory().GetItemCount(GameEnums::CELLPHONE) > 0
        && gs->GetMagazine().GetMagazineSize() == 1
        && gs->GetMagazine().GetHitProbability() < 0.999
        && !gs->GetItemState().GetStateOfCellPhone())
    {
        choice = GameEnums::CELLPHONE;
        return choice;
    }
    else if (gs->GetComputerInventory().GetItemCount(GameEnums::INVERTER) > 0
        && gs->GetMagazine().GetHitProbability() < 0.001)
    {
        choice = GameEnums::INVERTER;
        return choice;
    }
    else if (gs->GetComputerInventory().GetItemCount(GameEnums::INVERTER) > 0
        && gs->GetComputerHP().GetHP() == GameConfig::maxPlayerHP)
    {
        choice = GameEnums::INVERTER;
        return choice;
    }
    else
    {
        choice = GameEnums::NO_ITEMS;
        return choice;
    }
}

int8_t NormalAI::ManageInventory(int8_t& choice) const noexcept
{
    if (gs->GetDecisionState().GetCurrentMenu() != GameEnums::INVENTORY_MENU)
    {
        choice = GameEnums::USEITEM;
        return choice;
    }
	return choice;
}

int8_t NormalAI::Decision() const
{
    int8_t choice = GameEnums::NO_ITEMS;
    if (gs->GetMagazine().GetHitProbability() > 0.5)
    {
        choice = IfChanceForFullIsGreater();
        if (choice != GameEnums::NO_ITEMS)
        { 
            choice = ManageInventory(choice);
            return choice;
        }
        else
        {
            choice = GameEnums::SHOOT;
            return choice;
        }
    }
    else
    {
        choice = IfChanceForEmptyIsGreater();
        if (choice != GameEnums::NO_ITEMS)
        { 
            choice = ManageInventory(choice);
            return choice;
        }
        else
        {
            choice = GameEnums::HEAL;
            return choice;
        }
    }
}
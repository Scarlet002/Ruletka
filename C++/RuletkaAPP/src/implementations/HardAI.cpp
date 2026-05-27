#include "HardAI.h"
#include "IGameState.h"
#include "GameConfig.h"
#include "IPlayer.h"
#include "DecisionState.h"
#include "HP.h"
#include "IInventory.h"
#include "ItemState.h"
#include "Magazine.h"
#include <cstdint>

HardAI::HardAI(const std::shared_ptr<IGameState> gs) : gs(gs) {}

int8_t HardAI::MakeSpaceInInventory() const noexcept
{
    int8_t choice = GameEnums::NO_ITEMS;
    if (gs->GetComputerInventory().GetItemCount(GameEnums::MAGNIFIER) > 0)
    {
        choice = GameEnums::MAGNIFIER;
        return choice;
    }
    else if (gs->GetComputerInventory().GetItemCount(GameEnums::CELLPHONE) > 0)
    { 
        choice = GameEnums::CELLPHONE;
        return choice;
    }
    else 
    { 
        choice = GameEnums::NO_ITEMS;
        return choice;
    }
}

int8_t HardAI::IfBulletIsFull() const noexcept
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
        && gs->GetComputerInventory().GetItemCount(GameEnums::INVERTER) > 0)
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

int8_t HardAI::IfBulletIsEmpty() const noexcept
{
    int8_t choice = GameEnums::NO_ITEMS;
    if (gs->GetHumanHP().GetHP() <= 2 
        && gs->GetComputerInventory().GetItemCount(GameEnums::INVERTER) > 0)
    {
        choice = GameEnums::INVERTER;
        return choice;
    }
    else if (gs->GetComputerInventory().GetItemCount(GameEnums::BEER) > 0
        && gs->GetComputerHP().GetHP() == GameConfig::maxPlayerHP)
    {
        choice = GameEnums::BEER;
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

int8_t HardAI::ManageInventory(int8_t& choice) const noexcept
{
    if (gs->GetDecisionState().GetCurrentMenu() != GameEnums::INVENTORY_MENU)
    {
        choice = GameEnums::USEITEM;
        return choice;
    }
    else { return choice; }
}

int8_t HardAI::Decision() const
{
    int8_t choice = GameEnums::NO_ITEMS;
    if (gs->GetComputerInventory().GetItemCount(GameEnums::MAGNIFIER) > 0
        || gs->GetComputerInventory().GetItemCount(GameEnums::CELLPHONE) > 0)
    { 
        choice = MakeSpaceInInventory();
        choice = ManageInventory(choice);
        return choice;
    }
    else if (gs->GetMagazine().CheckBulletType(GameEnums::FIRST_BULLET))
    {
        choice = IfBulletIsFull();
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
        choice = IfBulletIsEmpty();
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
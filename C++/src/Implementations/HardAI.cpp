#include "HardAI.h"
#include "GameState.h"
#include "GameConfig.h"
#include <cstdint>

HardAI::HardAI(const GameState& state) 
    : state(state) {}

int8_t HardAI::MakeSpaceInInventory() const
{
    int8_t choice = GameEnums::NO_ITEMS;
    if (state.computer->GetMagnifiers() > 0) 
    {
        choice = GameEnums::MAGNIFIER;
        return choice;
    }
    else if (state.computer->GetCellPhones() > 0) 
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

int8_t HardAI::IfBulletIsFull() const
{
    int8_t choice = GameEnums::NO_ITEMS;
    if (state.human->GetHP() >= 2)
    {
        if (state.computer->GetHandCuffs() > 0
            && state.turn->GetStateOfHandCuffs() == GameEnums::ITEM_NOT_USED)
        {
            choice = GameEnums::HANDCUFFS;
            return choice;
        }
        else if (state.computer->GetSaws() > 0
            && state.turn->GetDamage() == GameConfig::defaultDamage)
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
    else if (state.computer->GetHP() == 1 
        && state.computer->GetInverters() > 0)
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

int8_t HardAI::IfBulletIsEmpty() const
{
    int8_t choice = GameEnums::NO_ITEMS;
    if (state.human->GetHP() <= 2 
        && state.computer->GetInverters() > 0)
    {
        choice = GameEnums::INVERTER;
        return choice;
    }
    else if (state.computer->GetBeers() > 0
        && state.computer->GetHP() == GameConfig::maxPlayerHP)
    {
        choice = GameEnums::BEER;
        return choice;
    }
    else if (state.computer->GetInverters() > 0 
        && state.computer->GetHP() == GameConfig::maxPlayerHP)
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

int8_t HardAI::ManageInventory(int8_t& choice) const
{
    if (state.turn->GetCurrentMenu() != GameEnums::INVENTORY_MENU) //<- do zmiany
    {
        choice = GameEnums::USEITEM;
        return choice;
    }
    else { return choice; }
}

int8_t HardAI::Decision() const
{
    int8_t choice = GameEnums::NO_ITEMS;
    if (state.computer->GetMagnifiers() > 0
        || state.computer->GetCellPhones() > 0)
    { 
        choice = MakeSpaceInInventory();
        choice = ManageInventory(choice);
        return choice;
    }
    else if (state.magazine->CheckBulletType(GameEnums::LOADED))
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
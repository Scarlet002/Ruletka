#include "NormalAI.h"
#include "GameState.h"
#include "GameConfig.h"
#include <cstdint>

NormalAI::NormalAI(const GameState& state) 
    : state(state) {};

int NormalAI::IfChanceForFullIsGreater() const
{
    uint8_t choice = 0;
    if (state.human->GetHP() >= 2)
    {
        if (state.computer->GetHandCuffs() > 0
            && state.turn->GetStateOfHandCuffs() == GameEnums::HANDCUFFS_NOT_USED)
        {
            choice = GameEnums::HANDCUFFS;
            return choice;
        }
        else if (state.turn->GetHitProbability() != 1.0
            && state.computer->GetMagnifiers() > 0
            && !state.turn->GetStateOfMagnifier())
        {
            choice = GameEnums::MAGNIFIER;
            return choice;
        }
        else if (state.computer->GetCellPhones() > 0
            && state.magazine->GetMagazineSize() == 2
            && state.turn->GetHitProbability() != 1.0
            && !state.turn->GetStateOfCellPhone())
        {
            choice = GameEnums::CELLPHONE;
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
        && state.computer->GetInverters() > 0
        && state.turn->GetHitProbability() == 1.0)
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
int NormalAI::IfChanceForEmptyIsGreater() const
{
    uint8_t choice = 0;
    if (state.human->GetHP() <= 2
        && state.computer->GetInverters() > 0)
    {
        choice = GameEnums::INVERTER;
        return choice;
    }
    if (state.computer->GetBeers() > 0
        && state.computer->GetHP() == GameConfig::maxPlayerHP)
    {
        choice = GameEnums::BEER;
        return choice;
    }
    else if (state.turn->GetHitProbability() != 1.0
        && state.computer->GetMagnifiers() > 0
        && !state.turn->GetStateOfMagnifier())
    {
        choice = GameEnums::MAGNIFIER;
        return choice;
    }
    else if (state.computer->GetCellPhones() > 0
        && state.magazine->GetMagazineSize() == 1
        && state.turn->GetHitProbability() != 1.0
        && !state.turn->GetStateOfCellPhone())
    {
        choice = GameEnums::CELLPHONE;
        return choice;
    }
    else if (state.computer->GetInverters() > 0
        && state.turn->GetHitProbability() == 0.0)
    {
        choice = GameEnums::INVERTER;
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
uint8_t NormalAI::ManageInventory(uint8_t& choice) const
{
    if (!state.turn->GetStateOfInventory())
    {
        choice = GameEnums::USEITEM;
        return choice;
    }
    else { return choice; }
}
int NormalAI::MakeDecision() const
{
    uint8_t choice = 0;
    if (state.turn->GetHitProbability() > 0.5)
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
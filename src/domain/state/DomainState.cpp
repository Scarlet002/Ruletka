#include "DomainState.h"
#include "HP.h"
#include "Inventory.h"
#include "ItemState.h"
#include "Magazine.h"
#include "Player.h"
#include <utility>

DomainState::DomainState(Player computer, Player human, ItemState itemState, Magazine magazine)
    : m_computer(std::move(computer)), m_human(std::move(human)), m_itemState(itemState), m_magazine(magazine)
{
}

auto DomainState::GetHuman() noexcept -> Player&
{
    return m_human;
}

auto DomainState::GetHumanInventory() noexcept -> Inventory&
{
    return m_human.GetInventory();
}

auto DomainState::GetHumanHP() noexcept -> HP&
{
    return m_human.GetHP();
}

auto DomainState::GetComputer() noexcept -> Player&
{
    return m_computer;
}

auto DomainState::GetComputerInventory() noexcept -> Inventory&
{
    return m_computer.GetInventory();
}

auto DomainState::GetComputerHP() noexcept -> HP&
{
    return m_computer.GetHP();
}

auto DomainState::GetMagazine() noexcept -> Magazine&
{
    return m_magazine;
}

auto DomainState::GetItemState() noexcept -> ItemState&
{
    return m_itemState;
}

auto DomainState::GetHuman() const noexcept -> const Player&
{
    return m_human;
}

auto DomainState::GetHumanInventory() const noexcept -> const Inventory&
{
    return m_human.GetInventory();
}

auto DomainState::GetHumanHP() const noexcept -> const HP&
{
    return m_human.GetHP();
}

auto DomainState::GetComputer() const noexcept -> const Player&
{
    return m_computer;
}

auto DomainState::GetComputerInventory() const noexcept -> const Inventory&
{
    return m_computer.GetInventory();
}

auto DomainState::GetComputerHP() const noexcept -> const HP&
{
    return m_computer.GetHP();
}

auto DomainState::GetMagazine() const noexcept -> const Magazine&
{
    return m_magazine;
}

auto DomainState::GetItemState() const noexcept -> const ItemState&
{
    return m_itemState;
}

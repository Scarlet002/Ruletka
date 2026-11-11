#pragma once

#include "HP.h"
#include "Inventory.h"
#include "ItemState.h"
#include "Magazine.h"
#include "Player.h"

class DomainState final
{
private:
    Player m_computer;
    Player m_human;
    Magazine m_magazine;
    ItemState m_itemState;

public:
    DomainState(Player computer, Player human, ItemState itemState, Magazine magazine);

    [[nodiscard]]
    auto GetHuman() noexcept -> Player&;
    [[nodiscard]]
    auto GetHumanInventory() noexcept -> Inventory&;
    [[nodiscard]]
    auto GetHumanHP() noexcept -> HP&;
    [[nodiscard]]
    auto GetComputer() noexcept -> Player&;
    [[nodiscard]]
    auto GetComputerInventory() noexcept -> Inventory&;
    [[nodiscard]]
    auto GetComputerHP() noexcept -> HP&;
    [[nodiscard]]
    auto GetMagazine() noexcept -> Magazine&;
    [[nodiscard]]
    auto GetItemState() noexcept -> ItemState&;

    [[nodiscard]]
    auto GetHuman() const noexcept -> const Player&;
    [[nodiscard]]
    auto GetHumanInventory() const noexcept -> const Inventory&;
    [[nodiscard]]
    auto GetHumanHP() const noexcept -> const HP&;
    [[nodiscard]]
    auto GetComputer() const noexcept -> const Player&;
    [[nodiscard]]
    auto GetComputerInventory() const noexcept -> const Inventory&;
    [[nodiscard]]
    auto GetComputerHP() const noexcept -> const HP&;
    [[nodiscard]]
    auto GetMagazine() const noexcept -> const Magazine&;
    [[nodiscard]]
    auto GetItemState() const noexcept -> const ItemState&;
};

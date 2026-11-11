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
    ItemState m_itemState;
    Magazine m_magazine;

public:
    DomainState(Player computer, Player human, ItemState itemState, Magazine magazine);

    [[nodiscard]]
    auto GetHuman() noexcept [[clang::lifetimebound]] -> Player&;
    [[nodiscard]]
    auto GetHumanInventory() noexcept [[clang::lifetimebound]] -> Inventory&;
    [[nodiscard]]
    auto GetHumanHP() noexcept [[clang::lifetimebound]] -> HP&;
    [[nodiscard]]
    auto GetComputer() noexcept [[clang::lifetimebound]] -> Player&;
    [[nodiscard]]
    auto GetComputerInventory() noexcept [[clang::lifetimebound]] -> Inventory&;
    [[nodiscard]]
    auto GetComputerHP() noexcept [[clang::lifetimebound]] -> HP&;
    [[nodiscard]]
    auto GetMagazine() noexcept [[clang::lifetimebound]] -> Magazine&;
    [[nodiscard]]
    auto GetItemState() noexcept [[clang::lifetimebound]] -> ItemState&;

    [[nodiscard]]
    auto GetHuman() const noexcept [[clang::lifetimebound]] -> const Player&;
    [[nodiscard]]
    auto GetHumanInventory() const noexcept [[clang::lifetimebound]] -> const Inventory&;
    [[nodiscard]]
    auto GetHumanHP() const noexcept [[clang::lifetimebound]] -> const HP&;
    [[nodiscard]]
    auto GetComputer() const noexcept [[clang::lifetimebound]] -> const Player&;
    [[nodiscard]]
    auto GetComputerInventory() const noexcept [[clang::lifetimebound]] -> const Inventory&;
    [[nodiscard]]
    auto GetComputerHP() const noexcept [[clang::lifetimebound]] -> const HP&;
    [[nodiscard]]
    auto GetMagazine() const noexcept [[clang::lifetimebound]] -> const Magazine&;
    [[nodiscard]]
    auto GetItemState() const noexcept [[clang::lifetimebound]] -> const ItemState&;
};

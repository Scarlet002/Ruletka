#pragma once

#include "DomainState.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Inventory.h"
#include "ItemAction.h"
#include "Logger.h"
#include "Player.h"

class Handcuffs final : public ItemAction
{
protected:
    [[nodiscard]]
    constexpr auto GetItemType() const noexcept -> GameEnums::ItemType override
    {
        return GameEnums::ItemType::HANDCUFFS;
    }

    auto UseItem(Player& player, Inventory& playerInventory) -> void override;

public:
    Handcuffs(GameLoopState& gameLoopState, DomainState& domainState, Logger& logger) noexcept;

    Handcuffs(const Handcuffs&) = delete;
    auto operator=(const Handcuffs&) -> Handcuffs& = delete;

    Handcuffs(Handcuffs&&) = delete;
    auto operator=(Handcuffs&&) -> Handcuffs& = delete;

    ~Handcuffs() noexcept override;
};

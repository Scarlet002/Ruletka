#pragma once

#include "DomainState.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Inventory.h"
#include "ItemAction.h"
#include "Logger.h"
#include "Player.h"

class Saw final : public ItemAction
{
protected:
    [[nodiscard]]
    constexpr auto GetItemType() const noexcept -> GameEnums::ItemType override
    {
        return GameEnums::ItemType::SAW;
    }

    auto UseItem(Player& player, Inventory& playerInventory) -> void override;

public:
    Saw(GameLoopState& gameLoopState, DomainState& domainState, Logger& logger) noexcept;

    Saw(const Saw&) = delete;
    auto operator=(const Saw&) -> Saw& = delete;

    Saw(Saw&&) = delete;
    auto operator=(Saw&&) -> Saw& = delete;

    ~Saw() noexcept override;
};

#pragma once

#include "DomainState.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Inventory.h"
#include "ItemAction.h"
#include "Logger.h"
#include "Player.h"

class Inverter final : public ItemAction
{
protected:
    [[nodiscard]]
    constexpr auto GetItemType() const noexcept -> GameEnums::ItemType override
    {
        return GameEnums::ItemType::INVERTER;
    }

    auto UseItem(Player& player, Inventory& playerInventory) -> void override;

public:
    Inverter(GameLoopState& gameLoopState, DomainState& domainState, Logger& logger) noexcept;

    Inverter(const Inverter&) = delete;
    auto operator=(const Inverter&) -> Inverter& = delete;

    Inverter(Inverter&&) = delete;
    auto operator=(Inverter&&) -> Inverter& = delete;

    ~Inverter() noexcept override;
};

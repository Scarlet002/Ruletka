#pragma once

#include "DomainState.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Inventory.h"
#include "ItemAction.h"
#include "Logger.h"
#include "Player.h"

class Magnifier final : public ItemAction
{
protected:
    [[nodiscard]]
    constexpr auto GetItemType() const noexcept -> GameEnums::ItemType override
    {
        return GameEnums::ItemType::MAGNIFIER;
    }

    auto UseItem(Player& player, Inventory& playerInventory) -> void override;

public:
    Magnifier(GameLoopState& gameLoopState, DomainState& domainState, Logger& logger) noexcept;

    Magnifier(const Magnifier&) = delete;
    auto operator=(const Magnifier&) -> Magnifier& = delete;

    Magnifier(Magnifier&&) = delete;
    auto operator=(Magnifier&&) -> Magnifier& = delete;

    ~Magnifier() noexcept override;
};

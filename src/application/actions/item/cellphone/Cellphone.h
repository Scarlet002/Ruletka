#pragma once

#include "DomainState.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Inventory.h"
#include "ItemAction.h"
#include "Logger.h"
#include "Player.h"

class Cellphone final : public ItemAction
{
protected:
    [[nodiscard]]
    constexpr auto GetItemType() const noexcept -> GameEnums::ItemType override
    {
        return GameEnums::ItemType::CELLPHONE;
    }

    auto UseItem(Player& player, Inventory& playerInventory) -> void override;

public:
    Cellphone(GameLoopState& gameLoopState, DomainState& domainState, Logger& logger) noexcept;

    Cellphone(const Cellphone&) = delete;
    auto operator=(const Cellphone&) -> Cellphone& = delete;

    Cellphone(Cellphone&&) = delete;
    auto operator=(Cellphone&&) -> Cellphone& = delete;

    ~Cellphone() noexcept override;
};

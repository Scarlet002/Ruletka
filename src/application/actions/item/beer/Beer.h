#pragma once

#include "DomainState.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Inventory.h"
#include "ItemAction.h"
#include "Logger.h"
#include "Player.h"

class Beer final : public ItemAction
{
protected:
    [[nodiscard]]
    constexpr auto GetItemType() const noexcept -> GameEnums::ItemType override
    {
        return GameEnums::ItemType::BEER;
    }

    auto UseItem(Player& player, Inventory& playerInventory) -> void override;

public:
    Beer(GameLoopState& gameLoopState, DomainState& domainState, Logger& logger) noexcept;

    Beer(const Beer&) = delete;
    auto operator=(const Beer&) -> Beer& = delete;

    Beer(Beer&&) = delete;
    auto operator=(Beer&&) -> Beer& = delete;

    ~Beer() noexcept override;
};

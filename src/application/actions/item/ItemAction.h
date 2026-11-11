#pragma once

#include "DomainState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "IAction.h"
#include "Inventory.h"
#include "Logger.h"
#include "Player.h"
#include <boost/static_string/static_string.hpp>
#include <format>
#include <iterator>

class ItemAction : public IAction
{
protected:
    GameLoopState&
        m_gameLoopState; //NOLINT(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)
    DomainState&
        m_domainState; //NOLINT(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)
    Logger&
        m_logger; //NOLINT(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)

    ItemAction(GameLoopState& gameLoopState, DomainState& domainState, Logger& logger) noexcept
        : m_gameLoopState(gameLoopState), m_domainState(domainState), m_logger(logger)
    {
    }

    [[nodiscard]]
    virtual auto GetItemType() const noexcept -> GameEnums::ItemType = 0;
    virtual auto UseItem(Player& player, Inventory& playerInventory) -> void = 0;

public:
    auto Execute() -> void final
    {
        using GameEnums::PlayerType::HUMAN;
        auto& player = m_gameLoopState.GetStarter() == HUMAN ? m_domainState.GetHuman() : m_domainState.GetComputer();
        auto& playerInventory = player.GetInventory();
        if (playerInventory.GetItemCount(GetItemType()) == GameConfig::MIN_ITEMS)
        {
            boost::static_string<GameConfig::LOG_LINE_RESERVE> log;
            std::format_to(std::back_inserter(log), "{} doesn't have this item!", player.GetName());
            m_logger.UpdateLogs(log);
            return;
        }
        UseItem(player, playerInventory);
    }
};

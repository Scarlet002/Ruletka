#include "Saw.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Inventory.h"
#include "ItemAction.h"
#include "ItemState.h"
#include "Logger.h"
#include "Player.h"
#include <boost/static_string/static_string.hpp>
#include <format>
#include <iterator>

Saw::~Saw() noexcept = default;

Saw::Saw(GameLoopState& gameLoopState, DomainState& domainState, Logger& logger) noexcept
    : ItemAction(gameLoopState, domainState, logger)
{
}

auto Saw::UseItem(Player& player, Inventory& playerInventory) -> void
{
    playerInventory.UseItem(GameEnums::ItemType::SAW);
    m_domainState.GetItemState().SetDamage(GameConfig::SAW_DAMAGE);
    boost::static_string<GameConfig::LOG_LINE_RESERVE> log;
    std::format_to(std::back_inserter(log), "{} used the saw! Damage increased!", player.GetName());
    m_logger.UpdateLogs(log);
}

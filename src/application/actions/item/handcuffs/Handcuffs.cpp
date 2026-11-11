#include "Handcuffs.h"
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

Handcuffs::~Handcuffs() noexcept = default;

Handcuffs::Handcuffs(GameLoopState& gameLoopState, DomainState& domainState, Logger& logger) noexcept
    : ItemAction(gameLoopState, domainState, logger)
{
}

auto Handcuffs::UseItem(Player& player, Inventory& playerInventory) -> void
{
    playerInventory.UseItem(GameEnums::ItemType::HANDCUFFS);
    m_domainState.GetItemState().SetStateOfHandCuffs(GameEnums::YesNo::YES);
    boost::static_string<GameConfig::LOG_LINE_RESERVE> log;
    std::format_to(std::back_inserter(log), "{} used handcuffs!", player.GetName());
    m_logger.UpdateLogs(log);
}

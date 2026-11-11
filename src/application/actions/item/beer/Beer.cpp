#include "Beer.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Inventory.h"
#include "ItemAction.h"
#include "Logger.h"
#include "Magazine.h"
#include "Player.h"
#include <boost/static_string/static_string.hpp>
#include <format>
#include <iterator>

Beer::~Beer() noexcept = default;

Beer::Beer(GameLoopState& gameLoopState, DomainState& domainState, Logger& logger) noexcept
    : ItemAction(gameLoopState, domainState, logger)
{
}

auto Beer::UseItem(Player& player, Inventory& playerInventory) -> void
{
    auto& magazine = m_domainState.GetMagazine();
    if (magazine.IsEmpty())
    {
        return;
    }

    playerInventory.UseItem(GameEnums::ItemType::BEER);
    magazine.DecreaseBulletCount();
    boost::static_string<GameConfig::LOG_LINE_RESERVE> log;
    std::format_to(std::back_inserter(log), "{} used beer!", player.GetName());
    m_logger.UpdateLogs(log);
}

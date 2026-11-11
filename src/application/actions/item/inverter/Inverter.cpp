#include "Inverter.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Inventory.h"
#include "ItemAction.h"
#include "ItemState.h"
#include "Logger.h"
#include "Magazine.h"
#include "Player.h"
#include <boost/static_string/static_string.hpp>
#include <format>
#include <iterator>

Inverter::~Inverter() noexcept = default;

Inverter::Inverter(GameLoopState& gameLoopState, DomainState& domainState, Logger& logger) noexcept
    : ItemAction(gameLoopState, domainState, logger)
{
}

auto Inverter::UseItem(Player& player, Inventory& playerInventory) -> void
{
    auto& magazine = m_domainState.GetMagazine();
    if (magazine.IsEmpty())
    {
        return;
    }

    playerInventory.UseItem(GameEnums::ItemType::INVERTER);
    magazine.InvertBulletType();
    m_domainState.GetItemState().SetStateOfInverter(GameEnums::YesNo::YES);
    boost::static_string<GameConfig::LOG_LINE_RESERVE> log;
    std::format_to(std::back_inserter(log), "{} used the inverter!", player.GetName());
    m_logger.UpdateLogs(log);
}

#include "Magnifier.h"
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
#include <string_view>

Magnifier::~Magnifier() noexcept = default;

Magnifier::Magnifier(GameLoopState& gameLoopState, DomainState& domainState, Logger& logger) noexcept
    : ItemAction(gameLoopState, domainState, logger)
{
}

auto Magnifier::UseItem(Player& player, Inventory& playerInventory) -> void
{
    auto& magazine = m_domainState.GetMagazine();
    if (magazine.IsEmpty())
    {
        return;
    }

    playerInventory.UseItem(GameEnums::ItemType::MAGNIFIER);
    const auto firstBullet = magazine.GetMagazine().m_head;
    m_domainState.GetItemState().SetStateOfMagnifier(GameEnums::YesNo::YES);

    if (player.GetType() == GameEnums::PlayerType::HUMAN)
    {
        auto bulletTypeString = std::string_view("empty");
        switch (magazine.CheckMagazineChamber(firstBullet))
        {
        case GameEnums::MagazineChamber::BLANK:
            magazine.SetHitProbability(GameConfig::MIN_PROBABILITY);
            bulletTypeString = "blank";
            break;
        case GameEnums::MagazineChamber::LIVE:
            magazine.SetHitProbability(GameConfig::MAX_PROBABILITY);
            bulletTypeString = "live";
            break;
        default:
        case GameEnums::MagazineChamber::EMPTY:
            break;
        }
        boost::static_string<GameConfig::LOG_LINE_RESERVE> log;
        std::format_to(std::back_inserter(log), "{} used the magnifier! The first bullet is {}!", player.GetName(),
                       bulletTypeString);
        m_logger.UpdateLogs(log);
    }
}

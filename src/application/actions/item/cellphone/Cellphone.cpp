#include "Cellphone.h"
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
#include "RNG.h"
#include <boost/static_string/static_string.hpp>
#include <cstdint>
#include <format>
#include <iterator>
#include <string_view>

Cellphone::~Cellphone() noexcept = default;

Cellphone::Cellphone(GameLoopState& gameLoopState, DomainState& domainState, Logger& logger) noexcept
    : ItemAction(gameLoopState, domainState, logger)
{
}

auto Cellphone::UseItem(Player& player, Inventory& playerInventory) -> void
{
    const auto& magazine = m_domainState.GetMagazine();
    if (magazine.IsEmpty())
    {
        return;
    }

    playerInventory.UseItem(GameEnums::ItemType::CELLPHONE);
    m_domainState.GetItemState().SetStateOfCellPhone(GameEnums::YesNo::YES);

    if (player.GetType() != GameEnums::PlayerType::HUMAN)
    {
        return;
    }

    const auto upperLimit = static_cast<uint8_t>(magazine.GetMagazineSize() - 1U);
    const auto index = static_cast<uint8_t>(RNG::GetRN<uint8_t>(GameConfig::MIN_BULLETS, upperLimit));
    if (player.GetType() == GameEnums::PlayerType::HUMAN)
    {
        auto bulletTypeString = std::string_view("empty");
        switch (magazine.CheckMagazineChamber(index))
        {
        case GameEnums::MagazineChamber::BLANK:
            bulletTypeString = "blank";
            break;
        case GameEnums::MagazineChamber::LIVE:
            bulletTypeString = "live";
            break;
        default:
        case GameEnums::MagazineChamber::EMPTY:
            break;
        }

        boost::static_string<GameConfig::LOG_LINE_RESERVE> log;
        std::format_to(std::back_inserter(log), "{} used the cellphone! Bullet {} is {}!", player.GetName(), index + 1U,
                       bulletTypeString);
        m_logger.UpdateLogs(log);
    }
}

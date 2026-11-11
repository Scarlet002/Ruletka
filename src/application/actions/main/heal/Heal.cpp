#include "Heal.h"
#include "ApplicationState.h"
#include "AutoSaveManager.h"
#include "DecisionState.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "HP.h"
#include "ItemState.h"
#include "Logger.h"
#include "Magazine.h"
#include "Player.h"
#include <boost/static_string/static_string.hpp>
#include <format>
#include <iterator>
#include <optional>

Heal::~Heal() noexcept = default;

Heal::Heal(ApplicationState& app, DomainState& domain, Logger& logger) noexcept
    : m_app(app), m_domain(domain), m_logger(logger)
{
}

auto Heal::Execute() -> void
{
    auto& loop = m_app.GetGameLoopState();
    auto& player = loop.GetStarter() == GameEnums::PlayerType::HUMAN ? m_domain.GetHuman() : m_domain.GetComputer();
    loop.SetCurrentMenu(GameEnums::Window::MAIN_MENU);
    auto& magazine = m_domain.GetMagazine();
    auto& itemState = m_domain.GetItemState();

    boost::static_string<GameConfig::LOG_LINE_RESERVE> log;
    switch (magazine.CheckMagazineChamber(magazine.GetMagazine().m_head))
    {
    default:
    case GameEnums::MagazineChamber::EMPTY:
        break;
    case GameEnums::MagazineChamber::BLANK:
        player.GetHP().RegainHP();
        std::format_to(std::back_inserter(log), "{} regained 1 HP!", player.GetName());
        break;
    case GameEnums::MagazineChamber::LIVE:
        const auto damage = itemState.GetDamage();
        player.GetHP().LoseHP(damage);
        std::format_to(std::back_inserter(log), "{} lost {} HP!", player.GetName(), damage);
        break;
    }
    m_logger.UpdateLogs(log);

    magazine.DecreaseBulletCount();
    itemState.SetDamage(GameConfig::DEFAULT_DAMAGE);
    itemState.SetStateOfCellPhone(GameEnums::YesNo::NO);
    itemState.SetStateOfMagnifier(GameEnums::YesNo::NO);
    itemState.SetStateOfInverter(GameEnums::YesNo::NO);
    m_app.GetDecisionState().SetMainChoice(std::nullopt);

    if (itemState.GetStateOfHandCuffs() == GameEnums::YesNo::NO)
    {
        if (player.GetType() == GameEnums::PlayerType::HUMAN)
        {
            loop.SetStarter(GameEnums::PlayerType::COMPUTER);
        }
        else
        {
            loop.SetStarter(GameEnums::PlayerType::HUMAN);
        }
    }
    else
    {
        itemState.SetStateOfHandCuffs(GameEnums::YesNo::NO);
    }
}

#include "Shoot.h"
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

Shoot::~Shoot() noexcept = default;

Shoot::Shoot(ApplicationState& app, DomainState& domain, Logger& logger) noexcept
    : m_app(app), m_domain(domain), m_logger(logger)
{
}

auto Shoot::Execute() -> void
{
    using namespace GameEnums;
    auto& loop = m_app.GetGameLoopState();
    const auto& shooter = loop.GetStarter() == PlayerType::HUMAN ? m_domain.GetHuman() : m_domain.GetComputer();
    auto& target = loop.GetStarter() == PlayerType::HUMAN ? m_domain.GetComputer() : m_domain.GetHuman();
    loop.SetCurrentMenu(Window::MAIN_MENU);
    auto& magazine = m_domain.GetMagazine();
    auto& itemState = m_domain.GetItemState();

    boost::static_string<GameConfig::LOG_LINE_RESERVE> log;
    switch (magazine.CheckMagazineChamber(magazine.GetMagazine().m_head))
    {
    default:
    case GameEnums::MagazineChamber::EMPTY:
        break;
    case GameEnums::MagazineChamber::BLANK:
        std::format_to(std::back_inserter(log), "{} missed {}!", shooter.GetName(), target.GetName());
        m_logger.UpdateLogs(log);
        break;
    case GameEnums::MagazineChamber::LIVE:
        const auto damage = itemState.GetDamage();
        target.GetHP().LoseHP(damage);
        std::format_to(std::back_inserter(log), "{} hit {} and dealt {} damage!", shooter.GetName(), target.GetName(),
                       damage);
        m_logger.UpdateLogs(log);
        break;
    }

    magazine.DecreaseBulletCount();
    itemState.SetDamage(GameConfig::DEFAULT_DAMAGE);
    itemState.SetStateOfCellPhone(YesNo::NO);
    itemState.SetStateOfMagnifier(YesNo::NO);
    itemState.SetStateOfInverter(YesNo::NO);
    m_app.GetDecisionState().SetMainChoice(std::nullopt);

    if (itemState.GetStateOfHandCuffs() == YesNo::NO)
    {
        if (shooter.GetType() == PlayerType::HUMAN)
        {
            loop.SetStarter(PlayerType::COMPUTER);
        }
        else
        {
            loop.SetStarter(PlayerType::HUMAN);
        }
    }
    else
    {
        itemState.SetStateOfHandCuffs(YesNo::NO);
    }
}

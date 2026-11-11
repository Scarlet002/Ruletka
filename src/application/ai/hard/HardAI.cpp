#include "HardAI.h"
#include "DecisionState.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "HP.h"
#include "Inventory.h"
#include "ItemState.h"
#include "Magazine.h"
#include <optional>

HardAI::HardAI(DecisionState& decision, DomainState& domain) noexcept : m_decision(decision), m_domain(domain)
{
}

auto HardAI::MakeSpaceInInventory() const noexcept -> std::optional<GameEnums::ItemType>
{
    using namespace GameEnums;
    const auto& inventory = m_domain.GetComputerInventory();

    if (inventory.GetItemCount(ItemType::MAGNIFIER) > GameConfig::MIN_ITEMS)
    {
        return ItemType::MAGNIFIER;
    }

    if (inventory.GetItemCount(ItemType::CELLPHONE) > GameConfig::MIN_ITEMS)
    {
        return ItemType::CELLPHONE;
    }

    return std::nullopt;
}

auto HardAI::IfBulletIsFull() const noexcept -> std::optional<GameEnums::ItemType>
{
    using namespace GameEnums;
    using namespace GameConfig;
    const auto& humanHP = m_domain.GetHumanHP();
    const auto& computerHP = m_domain.GetComputerHP();
    const auto& inventory = m_domain.GetComputerInventory();
    const auto& itemState = m_domain.GetItemState();

    if (humanHP.GetHP() >= 2U)
    {
        if (inventory.GetItemCount(ItemType::HANDCUFFS) > MIN_ITEMS && itemState.GetStateOfHandCuffs() == YesNo::NO)
        {
            return ItemType::HANDCUFFS;
        }

        if (inventory.GetItemCount(ItemType::SAW) > MIN_ITEMS && itemState.GetDamage() == DEFAULT_DAMAGE)
        {
            return ItemType::SAW;
        }

        return std::nullopt;
    }

    if (inventory.GetItemCount(ItemType::INVERTER) > MIN_ITEMS && computerHP.GetHP() == 1U)
    {
        return ItemType::INVERTER;
    }

    return std::nullopt;
}

auto HardAI::IfBulletIsEmpty() const noexcept -> std::optional<GameEnums::ItemType>
{
    using namespace GameEnums;
    using namespace GameConfig;
    const auto& humanHP = m_domain.GetHumanHP();
    const auto& computerHP = m_domain.GetComputerHP();
    const auto& inventory = m_domain.GetComputerInventory();

    if (inventory.GetItemCount(ItemType::INVERTER) > MIN_ITEMS && humanHP.GetHP() <= 2U)
    {
        return ItemType::INVERTER;
    }

    if (inventory.GetItemCount(ItemType::BEER) > MIN_ITEMS && computerHP.GetHP() == MAX_PLAYER_HP)
    {
        return ItemType::BEER;
    }

    if (inventory.GetItemCount(ItemType::INVERTER) > MIN_ITEMS && computerHP.GetHP() == MAX_PLAYER_HP)
    {
        return ItemType::INVERTER;
    }

    return std::nullopt;
}

auto HardAI::GetInput() -> void
{
    using namespace GameEnums;
    using namespace GameConfig;
    const auto& inventory = m_domain.GetComputerInventory();
    if (inventory.GetItemCount(ItemType::MAGNIFIER) > MIN_ITEMS ||
        inventory.GetItemCount(ItemType::CELLPHONE) > MIN_ITEMS)
    {
        const auto action = MakeSpaceInInventory();
        if (action.has_value())
        {
            m_decision.SetMainChoice(MainChoice::USE_ITEM);
            m_decision.SetItemChoice(action);
        }
        return;
    }

    const auto& magazine = m_domain.GetMagazine();
    if (magazine.CheckMagazineChamber(magazine.GetMagazine().m_head) == GameEnums::MagazineChamber::LIVE)
    {
        const auto action = IfBulletIsFull();
        if (action.has_value())
        {
            m_decision.SetMainChoice(MainChoice::USE_ITEM);
            m_decision.SetItemChoice(action);
        }
        else
        {
            m_decision.SetMainChoice(MainChoice::SHOOT);
        }
        return;
    }

    if (magazine.CheckMagazineChamber(magazine.GetMagazine().m_head) == GameEnums::MagazineChamber::BLANK)
    {
        const auto action = IfBulletIsEmpty();
        if (action.has_value())
        {
            m_decision.SetMainChoice(MainChoice::USE_ITEM);
            m_decision.SetItemChoice(action);
        }
        else
        {
            m_decision.SetMainChoice(MainChoice::HEAL);
        }
        return;
    }
}

#include "NormalAI.h"
#include "DecisionState.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "HP.h"
#include "Inventory.h"
#include "ItemState.h"
#include "Magazine.h"
#include <optional>

namespace
{
inline constexpr auto AI_HIT_PROBABILITY_CERTAIN = 0.999;
inline constexpr auto AI_HIT_PROBABILITY_UNCERTAIN = 0.001;
inline constexpr auto AI_HIT_PROBABILITY_BALANCED = 0.5;
} // namespace

NormalAI::NormalAI(DecisionState& decision, DomainState& domain) noexcept : m_decision(decision), m_domain(domain)
{
}

auto NormalAI::IfChanceForFullIsGreater() const noexcept -> std::optional<GameEnums::ItemType>
{
    using namespace GameEnums;
    using namespace GameConfig;
    const auto& inventory = m_domain.GetComputerInventory();
    const auto& itemState = m_domain.GetItemState();
    const auto& humanHP = m_domain.GetHumanHP();
    const auto& magazine = m_domain.GetMagazine();
    const auto& computerHP = m_domain.GetComputerHP();
    if (humanHP.GetHP() >= 2U)
    {
        if (inventory.GetItemCount(ItemType::HANDCUFFS) > MIN_ITEMS && itemState.GetStateOfHandCuffs() == YesNo::NO)
        {
            return ItemType::HANDCUFFS;
        }

        if (magazine.GetHitProbability() < AI_HIT_PROBABILITY_CERTAIN &&
            inventory.GetItemCount(ItemType::MAGNIFIER) > MIN_ITEMS && itemState.GetStateOfMagnifier() == YesNo::NO)
        {
            return ItemType::MAGNIFIER;
        }

        if (inventory.GetItemCount(ItemType::CELLPHONE) > MIN_ITEMS && magazine.GetMagazineSize() == 2U &&
            magazine.GetHitProbability() < AI_HIT_PROBABILITY_CERTAIN && itemState.GetStateOfCellPhone() == YesNo::NO)
        {
            return ItemType::CELLPHONE;
        }

        if (inventory.GetItemCount(ItemType::SAW) > MIN_ITEMS && itemState.GetDamage() == DEFAULT_DAMAGE)
        {
            return ItemType::SAW;
        }
        return std::nullopt;
    }

    if (computerHP.GetHP() == 1U && inventory.GetItemCount(ItemType::INVERTER) > MIN_ITEMS &&
        magazine.GetHitProbability() > AI_HIT_PROBABILITY_CERTAIN)
    {
        return ItemType::INVERTER;
    }
    return std::nullopt;
}

auto NormalAI::IfChanceForEmptyIsGreater() const noexcept -> std::optional<GameEnums::ItemType>
{
    using namespace GameEnums;
    using namespace GameConfig;
    const auto& inventory = m_domain.GetComputerInventory();
    const auto& itemState = m_domain.GetItemState();
    const auto& humanHP = m_domain.GetHumanHP();
    const auto& magazine = m_domain.GetMagazine();
    const auto& computerHP = m_domain.GetComputerHP();

    if (humanHP.GetHP() <= 2U && inventory.GetItemCount(ItemType::INVERTER) > MIN_ITEMS)
    {
        return ItemType::INVERTER;
    }

    if (inventory.GetItemCount(ItemType::BEER) > MIN_ITEMS && computerHP.GetHP() == MAX_PLAYER_HP)
    {
        return ItemType::BEER;
    }

    if (magazine.GetHitProbability() < AI_HIT_PROBABILITY_CERTAIN &&
        inventory.GetItemCount(ItemType::MAGNIFIER) > MIN_ITEMS && itemState.GetStateOfMagnifier() == YesNo::NO)
    {
        return ItemType::MAGNIFIER;
    }

    if (inventory.GetItemCount(ItemType::CELLPHONE) > MIN_ITEMS && magazine.GetMagazineSize() == 1U &&
        magazine.GetHitProbability() < AI_HIT_PROBABILITY_CERTAIN && itemState.GetStateOfCellPhone() == YesNo::NO)
    {
        return ItemType::CELLPHONE;
    }

    if (inventory.GetItemCount(ItemType::INVERTER) > MIN_ITEMS &&
        magazine.GetHitProbability() < AI_HIT_PROBABILITY_UNCERTAIN)
    {
        return ItemType::INVERTER;
    }

    if (inventory.GetItemCount(ItemType::INVERTER) > MIN_ITEMS && computerHP.GetHP() == MAX_PLAYER_HP)
    {
        return ItemType::INVERTER;
    }
    return std::nullopt;
}

auto NormalAI::GetInput() -> void
{
    using namespace GameEnums;
    const auto& magazine = m_domain.GetMagazine();
    if (magazine.GetHitProbability() > AI_HIT_PROBABILITY_BALANCED)
    {
        const auto action = IfChanceForFullIsGreater();
        if (action.has_value())
        {
            m_decision.SetMainChoice(MainChoice::USE_ITEM);
            m_decision.SetItemChoice(action);
        }
        else
        {
            m_decision.SetMainChoice(MainChoice::SHOOT);
        }
    }
    else
    {
        auto const action = IfChanceForEmptyIsGreater();
        if (action.has_value())
        {
            m_decision.SetMainChoice(MainChoice::USE_ITEM);
            m_decision.SetItemChoice(action);
        }
        else
        {
            m_decision.SetMainChoice(MainChoice::HEAL);
        }
    }
}

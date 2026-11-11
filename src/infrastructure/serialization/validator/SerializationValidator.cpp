#include "SerializationValidator.h"
#include "AIState.h"
#include "ApplicationState.h"
#include "DecisionState.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "HP.h"
#include "Inventory.h"
#include "ItemState.h"
#include "Magazine.h"
#include "Player.h"
#include "SerializationState.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>

SerializationValidator::SerializationValidator() noexcept = default;

auto SerializationValidator::ValidatePlayer(const Player& state) -> void
{
    using namespace GameEnums;
    const auto type = state.GetType();
    if (type != PlayerType::HUMAN && type != PlayerType::COMPUTER)
    {
        throw std::runtime_error("Invalid player type in file!");
    }

    const auto& playerHp = state.GetHP();
    const auto hitPoints = playerHp.GetHP();
    if (hitPoints > GameConfig::MAX_PLAYER_HP)
    {
        throw std::runtime_error("Invalid HP value in file!");
    }

    const auto& playerInventory = state.GetInventory();
    for (const auto& item : GameConfig::ITEM_TYPES)
    {
        if (playerInventory.GetItemCount(item.second) > GameConfig::MAX_ITEMS)
        {
            throw std::runtime_error("Invalid item count in file!");
        }
    }
}

auto SerializationValidator::ValidateMagazine(const Magazine& state) -> void
{
    const auto& magazine = state.GetMagazine();
    const auto emptyCount = std::ranges::count_if(
        magazine.m_magazine, [](const auto& bullet) -> auto { return bullet == GameEnums::MagazineChamber::EMPTY; });
    const auto size = magazine.m_magazine.size() - static_cast<size_t>(emptyCount);
    if (size > GameConfig::MAX_BULLETS || magazine.m_magazine.size() > GameConfig::MAX_BULLETS)
    {
        throw std::runtime_error("Invalid magazine size in file!");
    }

    for (const auto& bullet : magazine.m_magazine)
    {
        if (bullet != GameEnums::MagazineChamber::EMPTY && bullet != GameEnums::MagazineChamber::LIVE &&
            bullet != GameEnums::MagazineChamber::BLANK)
        {
            throw std::runtime_error("Invalid bullet type in file!");
        }
    }

    if (magazine.m_head > GameConfig::MAX_BULLETS)
    {
        throw std::runtime_error("Invalid magazine head in file!");
    }

    const auto hitProbability = state.GetHitProbability();
    if (!std::isfinite(hitProbability) ||
        (hitProbability < GameConfig::MIN_PROBABILITY || hitProbability > GameConfig::MAX_PROBABILITY))
    {
        throw std::runtime_error("Invalid hit probability in file!");
    }
}

auto SerializationValidator::ValidateGameLoopState(const GameLoopState& state) -> void
{
    using namespace GameEnums;
    const auto starter = state.GetStarter();
    if (starter != PlayerType::COMPUTER && starter != PlayerType::HUMAN)
    {
        throw std::runtime_error("Invalid STARTER in file!");
    }

    const auto menu = state.GetCurrentMenu();
    if (menu < Window::MAIN_MENU || menu > Window::RESTART_MENU)
    {
        throw std::runtime_error("Invalid MENU window in file!");
    }
}

auto SerializationValidator::ValidateSerializationState(const SerializationState& state) -> void
{
    using namespace GameEnums;
    const auto type = state.GetSerializationType();
    if (type != SerializationFormat::JSON && type != SerializationFormat::TXT)
    {
        throw std::runtime_error("Invalid serialization type in file!");
    }
}

auto SerializationValidator::ValidateAIState(const AIState& state) -> void
{
    using namespace GameEnums;
    const auto difficulty = state.GetDifficulty();
    if (difficulty < Difficulty::EASY || difficulty > Difficulty::HARD)
    {
        throw std::runtime_error("Invalid difficulty level in file!");
    }
}

auto SerializationValidator::ValidateDecisionState(const DecisionState& state) -> void
{
    using namespace GameEnums;
    const auto mainChoice = state.GetMainChoice();
    if (mainChoice.has_value())
    {
        const auto mainChoiceValue = mainChoice.value();
        if (mainChoiceValue < MainChoice::HEAL || mainChoiceValue > MainChoice::RESTART)
        {
            throw std::runtime_error("Invalid main choice in file!");
        }
    }

    const auto itemChoice = state.GetItemChoice();
    if (itemChoice.has_value())
    {
        const auto itemChoiceValue = itemChoice.value();
        if (itemChoiceValue < ItemType::HANDCUFFS || itemChoiceValue > ItemType::INVERTER)
        {
            throw std::runtime_error("Invalid item choice in file!");
        }
    }

    const auto difficultyChoice = state.GetDifficultyChoice();
    if (difficultyChoice.has_value())
    {
        const auto difficultyChoiceValue = difficultyChoice.value();
        if (difficultyChoiceValue < Difficulty::EASY || difficultyChoiceValue > Difficulty::HARD)
        {
            throw std::runtime_error("Invalid difficulty choice in file!");
        }
    }

    const auto yesNoChoice = state.GetYesNoChoice();
    if (yesNoChoice.has_value())
    {
        const auto yesNoChoiceValue = yesNoChoice.value();
        if (yesNoChoiceValue < YesNo::NO || yesNoChoiceValue > YesNo::YES)
        {
            throw std::runtime_error("Invalid yes/no choice in file!");
        }
    }

    const auto uiChoice = state.GetUIChoice();
    if (uiChoice.has_value())
    {
        const auto uiChoiceValue = uiChoice.value();
        if (uiChoiceValue < UIType::CONSOLE || uiChoiceValue > UIType::SFML)
        {
            throw std::runtime_error("Invalid UI choice in file!");
        }
    }

    const auto serializationChoice = state.GetSerializationChoice();
    if (serializationChoice.has_value())
    {
        const auto serializationChoiceValue = serializationChoice.value();
        if (serializationChoiceValue < SerializationFormat::TXT || serializationChoiceValue > SerializationFormat::JSON)
        {
            throw std::runtime_error("Invalid serialization choice in file!");
        }
    }
}

auto SerializationValidator::ValidateItemState(const ItemState& state) -> void
{
    const auto damage = state.GetDamage();
    if (damage != GameConfig::DEFAULT_DAMAGE && damage != GameConfig::SAW_DAMAGE)
    {
        throw std::runtime_error("Invalid damage value in file!");
    }
}

auto SerializationValidator::Validate(const ApplicationState& app, const DomainState& domain) const -> void
{
    ValidatePlayer(domain.GetHuman());
    ValidatePlayer(domain.GetComputer());
    ValidateMagazine(domain.GetMagazine());
    ValidateGameLoopState(app.GetGameLoopState());
    ValidateSerializationState(app.GetSerializationState());
    ValidateAIState(app.GetAIState());
    ValidateDecisionState(app.GetDecisionState());
    ValidateItemState(domain.GetItemState());
}

#include "AIState.h"
#include "GameConfig.h"
#include "GameEnums.h"

auto AIState::Reset() noexcept -> void
{
    m_difficulty = GameConfig::DEFAULT_DIFFICULTY;
}

auto AIState::SetDifficulty(GameEnums::Difficulty newDifficulty) noexcept -> void
{
    m_difficulty = newDifficulty;
}

[[nodiscard]]
auto AIState::GetDifficulty() const noexcept -> GameEnums::Difficulty
{
    return m_difficulty;
}

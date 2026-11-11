#include "AIManager.h"
#include "GameEnums.h"
#include "IAI.h"
#include <memory>
#include <stdexcept>
#include <utility>

auto AIManager::SetDifficulty(GameEnums::Difficulty key) -> void
{
    const auto iterator = m_strategies.find(key);
    if (iterator == m_strategies.end())
    {
        throw std::runtime_error("No strategy selected!");
    }
    m_strategy = iterator->second.get();
}

auto AIManager::AddDifficulty(GameEnums::Difficulty key, std::unique_ptr<IAI> difficulty) -> void
{
    const auto [iterator, inserted] = m_strategies.try_emplace(key, std::move(difficulty));
    if (!inserted)
    {
        throw std::runtime_error("Attempt to duplicate strategy!");
    }
    if (m_strategy == nullptr)
    {
        m_strategy = iterator->second.get();
    }
}

auto AIManager::GetInput() -> void
{
    if (m_strategy == nullptr)
    {
        throw std::runtime_error("Strategy not set!");
    }
    m_strategy->GetInput();
}

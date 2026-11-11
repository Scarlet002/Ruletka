#pragma once
#include "GameEnums.h"
#include "IAI.h"
#include <memory>
#include <unordered_map>

class AIManager
{
private:
    std::unordered_map<GameEnums::Difficulty, std::unique_ptr<IAI>> m_strategies;
    IAI* m_strategy = nullptr;

public:
    auto SetDifficulty(GameEnums::Difficulty key) -> void;
    auto AddDifficulty(GameEnums::Difficulty key, std::unique_ptr<IAI> difficulty) -> void;
    auto GetInput() -> void;
};

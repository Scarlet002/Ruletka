#include "EasyAI.h"
#include "DecisionState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "RNG.h"
#include <cstdint>

EasyAI::~EasyAI() noexcept = default;

EasyAI::EasyAI(DecisionState& decision) noexcept : m_decision(decision)
{
}

auto EasyAI::GetInput() -> void
{
    using namespace GameConfig;
    const auto value = RNG::GetRN<uint8_t>(MIN_EASY_AI, MAX_EASY_AI);
    m_decision.SetMainChoice(static_cast<GameEnums::MainChoice>(value));
};

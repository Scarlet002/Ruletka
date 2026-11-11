#pragma once

#include "AIState.h"
#include "DecisionState.h"
#include "GameLoopState.h"
#include "SerializationState.h"

class ApplicationState final
{
private:
    AIState m_aiState;
    DecisionState m_decisionState;
    GameLoopState m_gameLoopState;
    SerializationState m_serializationState;

public:
    ApplicationState(AIState aiState, DecisionState decisionState, GameLoopState gameLoopState,
                     SerializationState serializationState) noexcept;

    [[nodiscard]]
    auto GetGameLoopState() noexcept -> GameLoopState&;
    [[nodiscard]]
    auto GetAIState() noexcept -> AIState&;
    [[nodiscard]]
    auto GetDecisionState() noexcept -> DecisionState&;
    [[nodiscard]]
    auto GetSerializationState() noexcept -> SerializationState&;

    [[nodiscard]]
    auto GetGameLoopState() const noexcept -> const GameLoopState&;
    [[nodiscard]]
    auto GetAIState() const noexcept -> const AIState&;
    [[nodiscard]]
    auto GetDecisionState() const noexcept -> const DecisionState&;
    [[nodiscard]]
    auto GetSerializationState() const noexcept -> const SerializationState&;
};

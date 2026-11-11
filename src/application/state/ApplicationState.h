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
    auto GetGameLoopState() noexcept [[clang::lifetimebound]] -> GameLoopState&;
    [[nodiscard]]
    auto GetAIState() noexcept [[clang::lifetimebound]] -> AIState&;
    [[nodiscard]]
    auto GetDecisionState() noexcept [[clang::lifetimebound]] -> DecisionState&;
    [[nodiscard]]
    auto GetSerializationState() noexcept [[clang::lifetimebound]] -> SerializationState&;

    [[nodiscard]]
    auto GetGameLoopState() const noexcept [[clang::lifetimebound]] -> const GameLoopState&;
    [[nodiscard]]
    auto GetAIState() const noexcept [[clang::lifetimebound]] -> const AIState&;
    [[nodiscard]]
    auto GetDecisionState() const noexcept [[clang::lifetimebound]] -> const DecisionState&;
    [[nodiscard]]
    auto GetSerializationState() const noexcept [[clang::lifetimebound]] -> const SerializationState&;
};

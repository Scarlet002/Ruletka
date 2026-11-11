#include "ApplicationState.h"
#include "AIState.h"
#include "DecisionState.h"
#include "GameLoopState.h"
#include "SerializationState.h"
#include <utility>

ApplicationState::ApplicationState(AIState aiState, DecisionState decisionState, GameLoopState gameLoopState,
                                   SerializationState serializationState) noexcept
    : m_aiState(aiState), m_decisionState(std::move(decisionState)), m_gameLoopState(gameLoopState),
      m_serializationState(serializationState)
{
}

auto ApplicationState::GetGameLoopState() noexcept -> GameLoopState&
{
    return m_gameLoopState;
}

auto ApplicationState::GetAIState() noexcept -> AIState&
{
    return m_aiState;
}

auto ApplicationState::GetDecisionState() noexcept -> DecisionState&
{
    return m_decisionState;
}

auto ApplicationState::GetSerializationState() noexcept -> SerializationState&
{
    return m_serializationState;
}

auto ApplicationState::GetGameLoopState() const noexcept -> const GameLoopState&
{
    return m_gameLoopState;
}

auto ApplicationState::GetAIState() const noexcept -> const AIState&
{
    return m_aiState;
}

auto ApplicationState::GetDecisionState() const noexcept -> const DecisionState&
{
    return m_decisionState;
}

auto ApplicationState::GetSerializationState() const noexcept -> const SerializationState&
{
    return m_serializationState;
}

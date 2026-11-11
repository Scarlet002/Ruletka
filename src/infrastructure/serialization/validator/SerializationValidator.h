#pragma once

#include "Validator.h"

class ApplicationState;
class DomainState;
class Player;
class Magazine;
class GameLoopState;
class SerializationState;
class DecisionState;
class ItemState;
class AIState;

class SerializationValidator final : public Validator
{
private:
    static auto ValidatePlayer(const Player& state) -> void;
    static auto ValidateMagazine(const Magazine& state) -> void;
    static auto ValidateGameLoopState(const GameLoopState& state) -> void;
    static auto ValidateSerializationState(const SerializationState& state) -> void;
    static auto ValidateAIState(const AIState& state) -> void;
    static auto ValidateDecisionState(const DecisionState& state) -> void;
    static auto ValidateItemState(const ItemState& state) -> void;

public:
    SerializationValidator() noexcept;

    auto Validate(const ApplicationState& app, const DomainState& domain) const -> void override;
};

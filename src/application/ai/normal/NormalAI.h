#pragma once

#include "GameEnums.h"
#include "IAI.h"
#include <optional>

class DecisionState;
class DomainState;

class NormalAI final : public IAI
{
private:
    DecisionState& m_decision;
    DomainState& m_domain;
    [[nodiscard]]
    auto IfChanceForFullIsGreater() const noexcept -> std::optional<GameEnums::ItemType>;
    [[nodiscard]]
    auto IfChanceForEmptyIsGreater() const noexcept -> std::optional<GameEnums::ItemType>;

public:
    NormalAI(DecisionState& decision, DomainState& domain) noexcept;

    auto GetInput() -> void override;
};

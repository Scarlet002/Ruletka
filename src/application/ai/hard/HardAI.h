#pragma once

#include "GameEnums.h"
#include "IAI.h"
#include <optional>

class DecisionState;
class DomainState;

class HardAI final : public IAI
{
private:
    DecisionState& m_decision;
    DomainState& m_domain;
    [[nodiscard]]
    auto MakeSpaceInInventory() const noexcept -> std::optional<GameEnums::ItemType>;
    [[nodiscard]]
    auto IfBulletIsFull() const noexcept -> std::optional<GameEnums::ItemType>;
    [[nodiscard]]
    auto IfBulletIsEmpty() const noexcept -> std::optional<GameEnums::ItemType>;

public:
    HardAI(DecisionState& decision, DomainState& domain) noexcept;

    auto GetInput() -> void override;
};

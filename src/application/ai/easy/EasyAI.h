#pragma once

#include "IAI.h"

class DecisionState;

class EasyAI final : public IAI
{
private:
    DecisionState& m_decision;

public:
    explicit EasyAI(DecisionState& decision) noexcept;

    EasyAI(const EasyAI&) = delete;
    auto operator=(const EasyAI&) -> EasyAI& = delete;

    EasyAI(EasyAI&&) = delete;
    auto operator=(EasyAI&&) -> EasyAI& = delete;

    ~EasyAI() noexcept override;

    auto GetInput() -> void override;
};

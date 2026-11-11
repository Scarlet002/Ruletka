#pragma once

#include "IAction.h"

class IProcessor;
class DecisionState;
class GameLoopState;

class UseItem final : public IAction
{
private:
    IProcessor& m_inventory;
    DecisionState& m_decision;
    GameLoopState& m_loop;

public:
    UseItem(IProcessor& inventory, DecisionState& decision, GameLoopState& loop) noexcept;

    UseItem(const UseItem&) = delete;
    auto operator=(const UseItem&) -> UseItem& = delete;

    UseItem(UseItem&&) = delete;
    auto operator=(UseItem&&) -> UseItem& = delete;

    ~UseItem() noexcept override;

    auto Execute() -> void override;
};

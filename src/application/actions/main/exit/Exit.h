#pragma once

#include "IAction.h"

class GameLoopState;

class Exit final : public IAction
{
private:
    GameLoopState& m_gameLoopState;

public:
    explicit Exit(GameLoopState& gameLoopState) noexcept;

    Exit(const Exit&) = delete;
    auto operator=(const Exit&) -> Exit& = delete;

    Exit(Exit&&) = delete;
    auto operator=(Exit&&) -> Exit& = delete;

    ~Exit() noexcept override;

    auto Execute() -> void override;
};

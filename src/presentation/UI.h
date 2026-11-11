#pragma once

#include "GameEnums.h"
#include "Provider.h"
#include "Renderer.h"

// NOLINT(misc-confusable-identifiers)
class UI : public Renderer, public Provider
{
protected:
    UI() noexcept = default;

public:
    UI(const UI&) = delete;
    auto operator=(const UI&) -> UI& = delete;

    UI(UI&&) = delete;
    auto operator=(UI&&) -> UI& = delete;

    [[nodiscard]]
    virtual auto GetUIType() const noexcept -> GameEnums::UIType = 0;

    ~UI() noexcept override = default;
};

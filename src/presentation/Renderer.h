#pragma once

class Renderer
{
protected:
    Renderer() noexcept = default;

public:
    Renderer(const Renderer&) = delete;
    auto operator=(const Renderer&) -> Renderer& = delete;

    Renderer(Renderer&&) = delete;
    auto operator=(Renderer&&) -> Renderer& = delete;

    virtual auto Render() -> void = 0;

    virtual ~Renderer() noexcept = default;
};

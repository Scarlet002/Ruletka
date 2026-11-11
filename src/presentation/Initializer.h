#pragma once

class Initializer
{
protected:
    Initializer() noexcept = default;

public:
    Initializer(const Initializer&) = delete;
    auto operator=(const Initializer&) -> Initializer& = delete;

    Initializer(Initializer&&) = delete;
    auto operator=(Initializer&&) -> Initializer& = delete;

    virtual auto Initialize() -> void = 0;

    virtual ~Initializer() noexcept = default;
};

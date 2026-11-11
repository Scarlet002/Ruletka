#pragma once

class IAI
{
protected:
    IAI() noexcept = default;

public:
    IAI(const IAI&) = delete;
    auto operator=(const IAI&) -> IAI& = delete;

    IAI(IAI&&) = delete;
    auto operator=(IAI&&) -> IAI& = delete;

    virtual ~IAI() noexcept = default;

    virtual auto GetInput() -> void = 0;
};

#pragma once

class Provider
{
protected:
    Provider() noexcept = default;

public:
    Provider(const Provider&) = delete;
    auto operator=(const Provider&) -> Provider& = delete;

    Provider(Provider&&) = delete;
    auto operator=(Provider&&) -> Provider& = delete;

    virtual auto GetInput() -> void = 0;

    virtual ~Provider() noexcept = default;
};

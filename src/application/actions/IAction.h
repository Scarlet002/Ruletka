#pragma once

class IAction
{
protected:
    IAction() noexcept = default;

public:
    IAction(const IAction&) = delete;
    auto operator=(const IAction&) -> IAction& = delete;

    IAction(IAction&&) = delete;
    auto operator=(IAction&&) -> IAction& = delete;

    virtual ~IAction() noexcept = default;

    virtual auto Execute() -> void = 0;
};

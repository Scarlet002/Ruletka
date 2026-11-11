#pragma once

class IProcessor
{
protected:
    IProcessor() noexcept = default;

public:
    IProcessor(const IProcessor&) = delete;
    auto operator=(const IProcessor&) -> IProcessor& = delete;

    IProcessor(IProcessor&&) = delete;
    auto operator=(IProcessor&&) -> IProcessor& = delete;

    virtual auto Process() -> void = 0;

    virtual ~IProcessor() noexcept = default;
};

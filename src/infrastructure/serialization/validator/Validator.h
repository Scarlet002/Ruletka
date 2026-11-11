#pragma once

class ApplicationState;
class DomainState;

class Validator
{
protected:
    Validator() noexcept = default;

public:
    Validator(const Validator&) = delete;
    auto operator=(const Validator&) -> Validator& = delete;

    Validator(Validator&&) = delete;
    auto operator=(Validator&&) -> Validator& = delete;

    virtual ~Validator() noexcept = default;

    virtual auto Validate(const ApplicationState& app, const DomainState& domain) const -> void = 0;
};

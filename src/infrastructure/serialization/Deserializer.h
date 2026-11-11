#pragma once

#include <string_view>

class ApplicationState;
class DomainState;

class Deserializer
{
protected:
    Deserializer() noexcept = default;

public:
    Deserializer(const Deserializer&) = delete;
    auto operator=(const Deserializer&) -> Deserializer& = delete;

    Deserializer(Deserializer&&) = delete;
    auto operator=(Deserializer&&) -> Deserializer& = delete;

    virtual ~Deserializer() noexcept = default;

    virtual auto Deserialize(ApplicationState& app, DomainState& domain, std::string_view filename) -> void = 0;

    [[nodiscard]]
    virtual auto GetDeserializationLog() const -> std::string_view = 0;
};

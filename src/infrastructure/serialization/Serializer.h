#pragma once

#include <string_view>

class ApplicationState;
class DomainState;

class Serializer
{
protected:
    Serializer() noexcept = default;

public:
    Serializer(const Serializer&) = delete;
    auto operator=(const Serializer&) -> Serializer& = delete;

    Serializer(Serializer&&) = delete;
    auto operator=(Serializer&&) -> Serializer& = delete;

    virtual ~Serializer() noexcept = default;

    virtual auto Serialize(const ApplicationState& app, const DomainState& domain, std::string_view filename) const
        -> void = 0;

    [[nodiscard]]
    virtual auto GetSerializationLog() const -> std::string_view = 0;
};

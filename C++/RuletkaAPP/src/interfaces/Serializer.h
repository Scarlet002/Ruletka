#pragma once
#include "IGameState.h"
#include <string>

class Serializer
{
protected:
	Serializer() = default;
public:
    Serializer(const Serializer&) = delete;
    Serializer& operator=(const Serializer&) = delete;

    Serializer(Serializer&&) = delete;
    Serializer& operator=(Serializer&&) = delete;

    virtual void Serialize(const std::shared_ptr<IGameState> gs,
        const std::string& fileName) = 0;

    virtual void Deserialize(std::shared_ptr<IGameState> gs,
        const std::string& fileName) = 0;

    [[nodiscard]] virtual std::string GetSerializationLog() const noexcept = 0;

    virtual ~Serializer() = default;
};

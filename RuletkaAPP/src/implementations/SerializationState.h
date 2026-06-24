#pragma once
#include "GameConfig.h"
#include <cstdint>

class SerializationState
{
private:
    uint8_t serializationType = GameEnums::JSON;
public:
    SerializationState() = default;

    SerializationState(const SerializationState&) = delete;
    SerializationState& operator=(const SerializationState&) = delete;

    SerializationState(SerializationState&&) = delete;
    SerializationState& operator=(SerializationState&&) = delete;

    void Reset() { serializationType = GameEnums::JSON; }

    void SetSerializationType(uint8_t newType) { serializationType = newType; }

    [[nodiscard]] uint8_t GetSerializationType() const noexcept { return serializationType; }

    ~SerializationState() = default;
};
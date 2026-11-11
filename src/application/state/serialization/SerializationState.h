#pragma once

#include "GameEnums.h"

class SerializationState final
{
private:
    GameEnums::SerializationFormat m_serializationType = GameEnums::SerializationFormat::JSON;

public:
    auto Reset() noexcept -> void;
    auto SetSerializationType(GameEnums::SerializationFormat newType) noexcept -> void;

    [[nodiscard]]
    auto GetSerializationType() const noexcept -> GameEnums::SerializationFormat;
};

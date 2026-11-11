#include "SerializationState.h"
#include "GameEnums.h"

auto SerializationState::Reset() noexcept -> void
{
    m_serializationType = GameEnums::SerializationFormat::JSON;
}

auto SerializationState::SetSerializationType(GameEnums::SerializationFormat newType) noexcept -> void
{
    m_serializationType = newType;
}

[[nodiscard]]
auto SerializationState::GetSerializationType() const noexcept -> GameEnums::SerializationFormat
{
    return m_serializationType;
}

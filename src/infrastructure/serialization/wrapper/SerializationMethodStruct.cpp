#include "SerializationMethodStruct.h"
#include "Deserializer.h"
#include "SerializationValidator.h"
#include "Serializer.h"
#include <memory>
#include <utility>

SerializationMethodStruct::SerializationMethodStruct() noexcept = default;

SerializationMethodStruct::SerializationMethodStruct(SerializationMethodStruct&&) noexcept = default;
auto SerializationMethodStruct::operator=(SerializationMethodStruct&&) noexcept -> SerializationMethodStruct& = default;

SerializationMethodStruct::SerializationMethodStruct(std::unique_ptr<Serializer> serializer,
                                                     std::unique_ptr<Deserializer> deserializer,
                                                     SerializationValidator* validator) noexcept
    : m_serializer(std::move(serializer)), m_deserializer(std::move(deserializer)), m_validator(validator)
{
}

SerializationMethodStruct::~SerializationMethodStruct() noexcept = default;

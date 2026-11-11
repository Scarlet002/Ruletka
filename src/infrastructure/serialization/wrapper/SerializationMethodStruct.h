#pragma once

#include <memory>

class Serializer;
class Deserializer;
class SerializationValidator;

struct SerializationMethodStruct final
{
    std::unique_ptr<Serializer> m_serializer;      // NOLINT(misc-non-private-member-variables-in-classes):
    std::unique_ptr<Deserializer> m_deserializer;  // NOLINT(misc-non-private-member-variables-in-classes):
    SerializationValidator* m_validator = nullptr; // NOLINT(misc-non-private-member-variables-in-classes):

    SerializationMethodStruct() noexcept;

    SerializationMethodStruct(std::unique_ptr<Serializer> serializer, std::unique_ptr<Deserializer> deserializer,
                              SerializationValidator* validator) noexcept;

    SerializationMethodStruct(const SerializationMethodStruct&) = delete;
    auto operator=(const SerializationMethodStruct&) -> SerializationMethodStruct& = delete;

    SerializationMethodStruct(SerializationMethodStruct&&) noexcept;
    auto operator=(SerializationMethodStruct&&) noexcept -> SerializationMethodStruct&;

    ~SerializationMethodStruct() noexcept;
};

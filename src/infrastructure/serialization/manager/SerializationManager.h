#pragma once

#include "GameEnums.h"
#include "SerializationMethodStruct.h"
#include <mutex>
#include <string_view>
#include <unordered_map>

class ApplicationState;
class DomainState;
class Serializer;
class Deserializer;
class SerializationValidator;

class SerializationManager final
{
private:
    std::unordered_map<GameEnums::SerializationFormat, SerializationMethodStruct> m_serializationMethods;
    mutable std::mutex m_mtx;
    Serializer* m_serialization = nullptr;
    Deserializer* m_deserialization = nullptr;
    SerializationValidator* m_validation = nullptr;

public:
    auto SetSerializationMethod(GameEnums::SerializationFormat method) -> void;
    auto Serialize(const ApplicationState& app, const DomainState& domain, std::string_view filename) const -> void;
    auto Deserialize(ApplicationState& app, DomainState& domain, std::string_view filename) -> void;
    auto AddSerializationMethod(GameEnums::SerializationFormat method, SerializationMethodStruct elements) -> void;

    [[nodiscard]]
    auto GetSerializationLog() const -> std::string_view;
    [[nodiscard]]
    auto GetDeserializationLog() const -> std::string_view;
};

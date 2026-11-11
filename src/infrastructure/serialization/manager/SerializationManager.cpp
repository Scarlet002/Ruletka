#include "SerializationManager.h"
#include "ApplicationState.h"
#include "Deserializer.h"
#include "DomainState.h"
#include "GameEnums.h"
#include "SerializationMethodStruct.h"
#include "SerializationValidator.h"
#include "Serializer.h"
#include <cassert>
#include <mutex>
#include <string_view>
#include <utility>

auto SerializationManager::SetSerializationMethod(GameEnums::SerializationFormat method) -> void
{
    const std::scoped_lock lock(m_mtx);
    const auto iterator = m_serializationMethods.find(method);
    if (iterator == m_serializationMethods.end())
    {
        return;
    }
    m_serialization = iterator->second.m_serializer.get();
    m_deserialization = iterator->second.m_deserializer.get();
    m_validation = iterator->second.m_validator;
}

auto SerializationManager::Serialize(const ApplicationState& app, const DomainState& domain,
                                     std::string_view filename) const -> void
{
    const std::scoped_lock lock(m_mtx);
    assert(m_serialization != nullptr && m_validation != nullptr);
    if (m_serialization == nullptr || m_validation == nullptr)
    {
        return;
    }
    m_serialization->Serialize(app, domain, filename);
}

auto SerializationManager::Deserialize(ApplicationState& app, DomainState& domain, std::string_view filename) -> void
{
    const std::scoped_lock lock(m_mtx);
    assert(m_deserialization != nullptr && m_validation != nullptr);
    if (m_deserialization == nullptr || m_validation == nullptr)
    {
        return;
    }
    m_deserialization->Deserialize(app, domain, filename);
}

auto SerializationManager::AddSerializationMethod(GameEnums::SerializationFormat method,
                                                  SerializationMethodStruct elements) -> void
{
    const std::scoped_lock lock(m_mtx);
    const auto [iterator, inserted] = m_serializationMethods.try_emplace(method, std::move(elements));
    if (!inserted)
    {
        return;
    }
    if (m_serialization == nullptr)
    {
        m_serialization = iterator->second.m_serializer.get();
    }
    if (m_deserialization == nullptr)
    {
        m_deserialization = iterator->second.m_deserializer.get();
    }
    if (m_validation == nullptr)
    {
        m_validation = iterator->second.m_validator;
    }
}

auto SerializationManager::GetSerializationLog() const -> std::string_view
{
    const std::scoped_lock lock(m_mtx);
    assert(m_serialization != nullptr);
    if (m_serialization == nullptr)
    {
        return "Serialization was nullptr!";
    }
    return m_serialization->GetSerializationLog();
}

auto SerializationManager::GetDeserializationLog() const -> std::string_view
{
    const std::scoped_lock lock(m_mtx);
    assert(m_deserialization != nullptr);
    if (m_deserialization == nullptr)
    {
        return "Deserialization was nullptr!";
    }
    return m_deserialization->GetDeserializationLog();
}

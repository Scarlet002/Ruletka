#pragma once

#include "Deserializer.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include <boost/static_string/static_string.hpp>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <string_view>
#include <type_traits>
#include <utility>

class Validator;
class ApplicationState;
class DomainState;
class Player;
class Magazine;
class AIState;
class ItemState;
class SerializationState;
class DecisionState;
class GameLoopState;

class JSONDeserializer final : public Deserializer
{
private:
    boost::static_string<GameConfig::LOG_LINE_RESERVE> m_serializationLog;
    const Validator& m_validator;

    template <typename T>
        requires std::is_enum_v<T>
    [[nodiscard]]
    static auto DeserializeChoice(const nlohmann::json& data, std::string_view key) -> std::optional<T>
    {
        const auto iterator = data.find(key);
        if (iterator == data.end() || !iterator->is_number_integer())
        {
            return std::nullopt;
        }

        const auto value = iterator->get<int>();
        if (value == std::to_underlying(GameEnums::SpecialValues::NOTHING))
        {
            return std::nullopt;
        }
        return static_cast<T>(value);
    }

    static auto DeserializePlayer(const nlohmann::json& data, Player& state) -> void;
    static auto DeserializeMagazine(const nlohmann::json& data, Magazine& state) -> void;
    static auto DeserializeGameLoopState(const nlohmann::json& data, GameLoopState& state) -> void;
    static auto DeserializeSerializationState(const nlohmann::json& data, SerializationState& state) -> void;
    static auto DeserializeAIState(const nlohmann::json& data, AIState& state) -> void;
    static auto DeserializeDecisionState(const nlohmann::json& data, DecisionState& state) -> void;
    static auto DeserializeItemState(const nlohmann::json& data, ItemState& state) -> void;
    static auto DeserializeAll(const nlohmann::json& data, ApplicationState& app, DomainState& domain) -> void;

public:
    explicit JSONDeserializer(const Validator& validator);

    [[nodiscard]]
    auto GetDeserializationLog() const -> std::string_view override;

    auto Deserialize(ApplicationState& app, DomainState& domain, std::string_view filename) -> void override;
};

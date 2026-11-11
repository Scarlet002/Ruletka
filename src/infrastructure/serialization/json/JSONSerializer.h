#pragma once

#include "GameConfig.h"
#include "GameEnums.h"
#include "Serializer.h"
#include <boost/static_string/static_string.hpp>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <optional>
#include <string_view>
#include <type_traits>
#include <utility>

class Player;
class Magazine;
class GameLoopState;
class SerializationState;
class AIState;
class DecisionState;
class ItemState;
class ApplicationState;
class DomainState;

class JSONSerializer final : public Serializer
{
private:
    mutable boost::static_string<GameConfig::LOG_LINE_RESERVE> m_serializationLog;

    template <typename T>
        requires std::is_enum_v<T>
    static auto SerializeChoice(nlohmann::json& data, std::string_view key, std::optional<T> choice) -> void
    {
        if (choice.has_value())
        {
            data.emplace(key, std::to_underlying(choice.value()));
        }
        else
        {
            data.emplace(key, std::to_underlying(GameEnums::SpecialValues::NOTHING));
        }
    }

    static auto SerializePlayer(nlohmann::json& data, const Player& state) -> void;
    static auto SerializeMagazine(nlohmann::json& data, const Magazine& state) -> void;
    static auto SerializeGameLoopState(nlohmann::json& data, const GameLoopState& state) -> void;
    static auto SerializeSerializationState(nlohmann::json& data, const SerializationState& state) -> void;
    static auto SerializeAIState(nlohmann::json& data, const AIState& state) -> void;
    static auto SerializeDecisionState(nlohmann::json& data, const DecisionState& state) -> void;
    static auto SerializeItemState(nlohmann::json& data, const ItemState& state) -> void;

public:
    JSONSerializer();

    auto Serialize(const ApplicationState& app, const DomainState& domain, std::string_view filename) const
        -> void override;
    [[nodiscard]]
    auto GetSerializationLog() const -> std::string_view override;
};

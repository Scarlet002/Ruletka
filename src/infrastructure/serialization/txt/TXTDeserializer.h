#pragma once

#include "Deserializer.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include <boost/static_string/static_string.hpp>
#include <fstream>
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

class TXTDeserializer final : public Deserializer
{
private:
    boost::static_string<GameConfig::LOG_LINE_RESERVE> m_serializationLog;
    const Validator& m_validator;

    template <typename T>
        requires std::is_enum_v<T>
    [[nodiscard]]
    static auto DeserializeChoice(std::ifstream& file) -> std::optional<T>
    {
        auto choice = 0;
        file >> choice;
        if (choice != std::to_underlying(GameEnums::SpecialValues::NOTHING))
        {
            return static_cast<T>(choice);
        }
        return std::nullopt;
    }

    static auto DeserializePlayer(std::ifstream& file, Player& state) -> void;
    static auto DeserializeMagazine(std::ifstream& file, Magazine& state) -> void;
    static auto DeserializeGameLoopState(std::ifstream& file, GameLoopState& state) -> void;
    static auto DeserializeSerializationState(std::ifstream& file, SerializationState& state) -> void;
    static auto DeserializeAIState(std::ifstream& file, AIState& state) -> void;
    static auto DeserializeDecisionState(std::ifstream& file, DecisionState& state) -> void;
    static auto DeserializeItemState(std::ifstream& file, ItemState& state) -> void;
    static auto DeserializeAll(std::string_view path, ApplicationState& app, DomainState& domain) -> void;

public:
    explicit TXTDeserializer(const Validator& validator);

    [[nodiscard]]
    auto GetDeserializationLog() const -> std::string_view override;

    auto Deserialize(ApplicationState& app, DomainState& domain, std::string_view filename) -> void override;
};

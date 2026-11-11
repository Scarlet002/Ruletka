#pragma once

#include "GameConfig.h"
#include "GameEnums.h"
#include "Serializer.h"
#include <boost/static_string/static_string.hpp>
#include <fstream>
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

class TXTSerializer final : public Serializer
{
private:
    mutable boost::static_string<GameConfig::LOG_LINE_RESERVE> m_serializationLog;

    template <typename T>
        requires std::is_enum_v<T>
    static auto SerializeChoice(std::ofstream& file, std::optional<T> choice) -> void
    {
        if (choice.has_value())
        {
            file << static_cast<int>(std::to_underlying(choice.value())) << '\n';
        }
        else
        {
            file << static_cast<int>(std::to_underlying(GameEnums::SpecialValues::NOTHING)) << '\n';
        }
    }

    static auto SerializePlayer(std::ofstream& file, const Player& state) -> void;
    static auto SerializeMagazine(std::ofstream& file, const Magazine& state) -> void;
    static auto SerializeGameLoopState(std::ofstream& file, const GameLoopState& state) -> void;
    static auto SerializeSerializationState(std::ofstream& file, const SerializationState& state) -> void;
    static auto SerializeAIState(std::ofstream& file, const AIState& state) -> void;
    static auto SerializeDecisionState(std::ofstream& file, const DecisionState& state) -> void;
    static auto SerializeItemState(std::ofstream& file, const ItemState& state) -> void;

public:
    TXTSerializer();

    auto Serialize(const ApplicationState& app, const DomainState& domain, std::string_view filename) const
        -> void override;
    [[nodiscard]]
    auto GetSerializationLog() const -> std::string_view override;
};

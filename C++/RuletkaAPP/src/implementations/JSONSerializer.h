#pragma once
#include "ForwardDeclarations.h"
#include "Serializer.h"
#include <string>
#include <deque>
#include <memory>
#include <nlohmann/json.hpp>

class JSONSerializer : public Serializer
{
private:
    struct PlayerData
    {
        std::string name;
        std::string type;
        uint8_t hp;
        uint8_t saws;
        uint8_t beers;
        uint8_t magnifiers;
        uint8_t cellphones;
        uint8_t handcuffs;
        uint8_t inverters;
        uint8_t itemsCount;
    };

    struct MagazineData
    {
        std::deque<uint8_t> magazine;
        float hitProbability;
    };

    std::string serializationLog = "";

    struct ItemStateData
    {
        uint8_t damage;
        bool wereHandCuffsUsed;
        bool wasMagnifierUsed;
        bool wasCellPhoneUsed;
    };

    struct GameLoopStateData
    {
        uint8_t starter;
        bool isOnePlayerAlive;
        bool stateOfGameLoop;
    };

    struct DecisionStateData
    {
        int8_t choice;
        int8_t previousChoice;
        uint8_t currentMenu;
    };

    struct AIStateData
    {
        uint8_t difficulty;
        uint8_t recentDifficulty;
    };

    struct SerializationStateData
    {
        uint8_t serializationType;
    };

    void SerializePlayer(nlohmann::json& data, const PlayerData& pd);
    void SerializeComputer(nlohmann::json& data, const PlayerData& pd);
    void SerializeMagazine(nlohmann::json& data, const MagazineData& md);
    void SerializeGameLoopState(nlohmann::json& data, const GameLoopStateData& gls);
    void SerializeSerializationState(nlohmann::json& data, const SerializationStateData& ss);
    void SerializeAIState(nlohmann::json& data, const AIStateData& ais);
    void SerializeDecisionState(nlohmann::json& data, const DecisionStateData& ds);
    void SerializeItemState(nlohmann::json& data, const ItemStateData& is);

    PlayerData DeserializePlayer(const nlohmann::json& data);
    PlayerData DeserializeComputer(const nlohmann::json& data);
    MagazineData DeserializeMagazine(const nlohmann::json& data);
    GameLoopStateData DeserializeGameLoopState(const nlohmann::json& data);
    SerializationStateData DeserializeSerializationState(const nlohmann::json& data);
    AIStateData DeserializeAIState(const nlohmann::json& data);
    DecisionStateData DeserializeDecisionState(const nlohmann::json& data);
    ItemStateData DeserializeItemState(const nlohmann::json& data);

    void ValidatePlayer(const PlayerData& pd);
    void ValidateComputer(const PlayerData& pd);
    void ValidateMagazine(const MagazineData& md);
    void ValidateGameLoopState(const GameLoopStateData& data);
    void ValidateSerializationState(const SerializationStateData& data);
    void ValidateAIState(const AIStateData& data);
    void ValidateDecisionState(const DecisionStateData& data);
    void ValidateItemState(const ItemStateData& data);

public:
    explicit JSONSerializer() = default;

    void Serialize(const std::shared_ptr<IGameState> gs,
        const std::string& fileName) override;

    void Deserialize(std::shared_ptr<IGameState> gs,
        const std::string& fileName) override;

    std::string GetSerializationLog() const noexcept override;
};
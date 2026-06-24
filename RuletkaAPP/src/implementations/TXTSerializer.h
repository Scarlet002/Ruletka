#pragma once
#include "ForwardDeclarations.h"
#include "Serializer.h"
#include <string>
#include <deque>
#include <memory>

class TXTSerializer : public Serializer
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
        uint8_t bulletCount;
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

    void SerializePlayer(std::ofstream& file, const PlayerData& data);
    void SerializeComputer(std::ofstream& file, const PlayerData& data);
    void SerializeMagazine(std::ofstream& file, const MagazineData& data);
    void SerializeGameLoopState(std::ofstream& file, const GameLoopStateData& data);
    void SerializeSerializationState(std::ofstream& file, const SerializationStateData& data);
    void SerializeAIState(std::ofstream& file, const AIStateData& data);
    void SerializeDecisionState(std::ofstream& file, const DecisionStateData& data);
    void SerializeItemState(std::ofstream& file, const ItemStateData& data);

    PlayerData DeserializePlayer(std::ifstream& file);
    PlayerData DeserializeComputer(std::ifstream& file);
    MagazineData DeserializeMagazine(std::ifstream& file);
    GameLoopStateData DeserializeGameLoopState(std::ifstream& file);
    SerializationStateData DeserializeSerializationState(std::ifstream& file);
    AIStateData DeserializeAIState(std::ifstream& file);
    DecisionStateData DeserializeDecisionState(std::ifstream& file);
    ItemStateData DeserializeItemState(std::ifstream& file);

    void ValidatePlayer(const PlayerData& pd);
    void ValidateComputer(const PlayerData& pd);
    void ValidateMagazine(const MagazineData& md);
    void ValidateGameLoopState(const GameLoopStateData& data);
    void ValidateSerializationState(const SerializationStateData& data);
    void ValidateAIState(const AIStateData& data);
    void ValidateDecisionState(const DecisionStateData& data);
    void ValidateItemState(const ItemStateData& data);

public:
    explicit TXTSerializer() = default;

    void Serialize(const std::shared_ptr<IGameState> gs,
        const std::string& fileName) override;

    void Deserialize(std::shared_ptr<IGameState> gs,
        const std::string& fileName) override;

    std::string GetSerializationLog() const noexcept override;
};
#include "TXTDeserializer.h"
#include "AIState.h"
#include "ApplicationState.h"
#include "DecisionState.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "HP.h"
#include "Inventory.h"
#include "ItemState.h"
#include "Magazine.h"
#include "Player.h"
#include "SaveConfig.h"
#include "SerializationState.h"
#include "Validator.h"
#include <array>
#include <boost/static_string/static_string.hpp>
#include <cstdint>
#include <exception>
#include <filesystem>
#include <format>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

namespace
{
using BufferMagazine = std::array<GameEnums::MagazineChamber, GameConfig::MAX_BULLETS>;
} //namespace

TXTDeserializer::TXTDeserializer(const Validator& validator) : m_validator(validator)
{
    m_serializationLog.reserve(GameConfig::LOG_LINE_RESERVE);
}

auto TXTDeserializer::DeserializePlayer(std::ifstream& file, Player& state) -> void
{
    std::string name;
    name.reserve(GameConfig::MAX_FILENAME_LENGTH);
    file >> name;
    if (name.size() > GameConfig::MAX_FILENAME_LENGTH)
    {
        throw std::runtime_error("Invalid player name in file!");
    }
    state.SetName(name);

    auto type = 0U;
    file >> type;
    state.SetType(static_cast<GameEnums::PlayerType>(type));

    auto hitPoints = 0U;
    file >> hitPoints;

    auto& playerHP = state.GetHP();
    playerHP.SetHP(static_cast<uint8_t>(hitPoints));

    auto& playerInventory = state.GetInventory();
    for (const auto& item : GameConfig::ITEM_TYPES)
    {
        auto count = 0U;
        file >> count;
        playerInventory.SetItemCount(item.second, static_cast<uint8_t>(count));
    }
}

auto TXTDeserializer::DeserializeMagazine(std::ifstream& file, Magazine& state) -> void
{
    auto newMagazine = BufferMagazine{};
    for (auto index = 0UZ; index < GameConfig::MAX_BULLETS; ++index)
    {
        auto bullet = 0U;
        file >> bullet;
        newMagazine[index] = static_cast<GameEnums::MagazineChamber>(bullet);
    }
    auto magazineHead = 0U;
    file >> magazineHead;
    state.SetMagazine({.m_magazine = newMagazine, .m_head = static_cast<uint8_t>(magazineHead)});

    auto hitProbability = GameConfig::MIN_PROBABILITY;
    file >> hitProbability;
    state.SetHitProbability(hitProbability);
}

auto TXTDeserializer::DeserializeGameLoopState(std::ifstream& file, GameLoopState& state) -> void
{
    using namespace GameEnums;
    auto starter = 0U;
    auto isInRestartMenu = 0U;
    auto stateOfGameLoop = 0U;
    auto currentMenu = 0U;
    file >> starter >> isInRestartMenu >> stateOfGameLoop >> currentMenu;
    state.SetStarter(static_cast<PlayerType>(starter));
    state.SetIsInRestartMenu(static_cast<YesNo>(isInRestartMenu));
    state.SetStateOfGameLoop(static_cast<YesNo>(stateOfGameLoop));
    state.SetCurrentMenu(static_cast<Window>(currentMenu));
}

auto TXTDeserializer::DeserializeSerializationState(std::ifstream& file, SerializationState& state) -> void
{
    using namespace GameEnums;
    auto serializationType = 0;
    file >> serializationType;
    state.SetSerializationType(static_cast<SerializationFormat>(serializationType));
}

auto TXTDeserializer::DeserializeAIState(std::ifstream& file, AIState& state) -> void
{
    using namespace GameEnums;
    auto difficulty = 0;
    file >> difficulty;
    state.SetDifficulty(static_cast<Difficulty>(difficulty));
}

auto TXTDeserializer::DeserializeDecisionState(std::ifstream& file, DecisionState& state) -> void
{
    state.SetMainChoice(DeserializeChoice<GameEnums::MainChoice>(file));
    state.SetItemChoice(DeserializeChoice<GameEnums::ItemType>(file));
    state.SetDifficultyChoice(DeserializeChoice<GameEnums::Difficulty>(file));
    state.SetYesNoChoice(DeserializeChoice<GameEnums::YesNo>(file));
    state.SetUIChoice(DeserializeChoice<GameEnums::UIType>(file));
    state.SetSerializationChoice(DeserializeChoice<GameEnums::SerializationFormat>(file));
}

auto TXTDeserializer::DeserializeItemState(std::ifstream& file, ItemState& state) -> void
{
    using namespace GameEnums;
    auto damage = 0U;
    auto wereHandCuffsUsed = 0U;
    auto wasMagnifierUsed = 0U;
    auto wasCellPhoneUsed = 0U;
    auto wasInverterUsed = 0U;
    file >> damage >> wereHandCuffsUsed >> wasMagnifierUsed >> wasCellPhoneUsed >> wasInverterUsed;
    state.SetDamage(static_cast<uint8_t>(damage));
    state.SetStateOfHandCuffs(static_cast<YesNo>(wereHandCuffsUsed));
    state.SetStateOfMagnifier(static_cast<YesNo>(wasMagnifierUsed));
    state.SetStateOfCellPhone(static_cast<YesNo>(wasCellPhoneUsed));
    state.SetStateOfInverter(static_cast<YesNo>(wasInverterUsed));
}

auto TXTDeserializer::DeserializeAll(std::string_view path, ApplicationState& app, DomainState& domain) -> void
{
    const auto* cpath = path.data();
    std::ifstream gameSave(cpath);
    if (!gameSave.is_open())
    {
        gameSave.close();
        throw std::runtime_error("File loading error!");
    }

    std::string version;
    gameSave >> version;
    if (version != GameConfig::GAME_VERSION)
    {
        throw std::runtime_error("Unsupported save version!");
    }

    DeserializePlayer(gameSave, domain.GetHuman());
    DeserializePlayer(gameSave, domain.GetComputer());
    DeserializeMagazine(gameSave, domain.GetMagazine());
    DeserializeGameLoopState(gameSave, app.GetGameLoopState());
    DeserializeSerializationState(gameSave, app.GetSerializationState());
    DeserializeAIState(gameSave, app.GetAIState());
    DeserializeDecisionState(gameSave, app.GetDecisionState());
    DeserializeItemState(gameSave, domain.GetItemState());

    if (gameSave.fail())
    {
        throw std::runtime_error("Gamestate loading error!");
    }

    gameSave.close();
}

auto TXTDeserializer::GetDeserializationLog() const -> std::string_view
{
    return m_serializationLog;
}

auto TXTDeserializer::Deserialize(ApplicationState& app, DomainState& domain, std::string_view filename) -> void
{
    try
    {
        m_serializationLog.clear();
        const auto saveDirectory =
            filename.starts_with("autosave") ? SaveConfig::GetAutoSaveDirectory() : SaveConfig::GetSaveDirectory();
        boost::static_string<GameConfig::LOG_LINE_RESERVE> path;
        std::format_to(std::back_inserter(path), "{}/{}.txt", saveDirectory, filename);
        auto appSnapshot = app;
        auto domainSnapshot = domain;
        const auto fileSize = std::filesystem::file_size(path.c_str());
        constexpr auto MAX_TXT_FILE_SIZE_IN_BYTES = 500U;
        if (fileSize > MAX_TXT_FILE_SIZE_IN_BYTES)
        {
            throw std::runtime_error("File size is not valid!");
        }
        DeserializeAll(path, appSnapshot, domainSnapshot);
        m_validator.Validate(appSnapshot, domainSnapshot);
        app = appSnapshot;
        domain = std::move(domainSnapshot);
    }
    catch (const std::exception& e)
    {
        auto message = std::string_view(e.what());
        if (message.size() < GameConfig::LOG_LINE_RESERVE)
        {
            m_serializationLog = message;
        }
        else
        {
            m_serializationLog = "Failed to deserialize";
        }
    }
}

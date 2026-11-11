#include "JSONDeserializer.h"
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
#include <format>
#include <fstream>
#include <iterator>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>
#include <string>
#include <string_view>

namespace
{
using BufferMagazine = std::array<GameEnums::MagazineChamber, GameConfig::MAX_BULLETS>;
} //namespace

JSONDeserializer::JSONDeserializer(const Validator& validator) : m_validator(validator)
{
    m_serializationLog.reserve(GameConfig::LOG_LINE_RESERVE);
}

auto JSONDeserializer::DeserializePlayer(const nlohmann::json& data, Player& state) -> void
{
    using namespace GameEnums;
    const auto prefix = std::string(state.GetTypeString());
    state.SetName(data.value(prefix + "_name", state.GetName()));
    state.SetType(data.value(prefix + "_type", PlayerType::HUMAN));

    auto& playerHP = state.GetHP();
    playerHP.SetHP(data.value(prefix + "_HP", GameConfig::MIN_PLAYER_HP));

    auto& playerInventory = state.GetInventory();
    playerInventory.SetItemCount(ItemType::SAW,
                                 static_cast<uint8_t>(data.value(prefix + "_saws", GameConfig::MIN_ITEMS)));
    playerInventory.SetItemCount(ItemType::BEER,
                                 static_cast<uint8_t>(data.value(prefix + "_beers", GameConfig::MIN_ITEMS)));
    playerInventory.SetItemCount(ItemType::MAGNIFIER,
                                 static_cast<uint8_t>(data.value(prefix + "_magnifiers", GameConfig::MIN_ITEMS)));
    playerInventory.SetItemCount(ItemType::CELLPHONE,
                                 static_cast<uint8_t>(data.value(prefix + "_cellphones", GameConfig::MIN_ITEMS)));
    playerInventory.SetItemCount(ItemType::HANDCUFFS,
                                 static_cast<uint8_t>(data.value(prefix + "_handcuffs", GameConfig::MIN_ITEMS)));
    playerInventory.SetItemCount(ItemType::INVERTER,
                                 static_cast<uint8_t>(data.value(prefix + "_inverters", GameConfig::MIN_ITEMS)));
}

auto JSONDeserializer::DeserializeMagazine(const nlohmann::json& data, Magazine& state) -> void
{
    if (!data.contains("magazine") || !data.contains("magazineHead"))
    {
        return;
    }
    if (data["magazine"].is_array() && data["magazine"] <= GameConfig::MAX_BULLETS &&
        data["magazineHead"].is_number_unsigned() && data["magazineHead"] <= GameConfig::MAX_BULLETS)
    {
        state.SetMagazine({.m_magazine = BufferMagazine(data["magazine"]), .m_head = data["magazineHead"]});
    }
    state.SetHitProbability(data.value("hitProbability", GameConfig::MIN_PROBABILITY));
}

auto JSONDeserializer::DeserializeGameLoopState(const nlohmann::json& data, GameLoopState& state) -> void
{
    state.SetStarter(data.value("starter", GameEnums::PlayerType::HUMAN));
    state.SetIsInRestartMenu(data.value("isInRestartMenu", GameEnums::YesNo::NO));
    state.SetStateOfGameLoop(data.value("stateOfGameLoop", GameEnums::YesNo::NO));
    state.SetCurrentMenu(data.value("Menu", GameEnums::Window::MAIN_MENU));
}

auto JSONDeserializer::DeserializeSerializationState(const nlohmann::json& data, SerializationState& state) -> void
{
    state.SetSerializationType(data.value("serializationType", GameEnums::SerializationFormat::JSON));
}

auto JSONDeserializer::DeserializeAIState(const nlohmann::json& data, AIState& state) -> void
{
    state.SetDifficulty(data.value("difficulty", GameConfig::DEFAULT_DIFFICULTY));
}

auto JSONDeserializer::DeserializeDecisionState(const nlohmann::json& data, DecisionState& state) -> void
{
    state.SetMainChoice(DeserializeChoice<GameEnums::MainChoice>(data, "MainChoice"));
    state.SetItemChoice(DeserializeChoice<GameEnums::ItemType>(data, "ItemChoice"));
    state.SetDifficultyChoice(DeserializeChoice<GameEnums::Difficulty>(data, "DifficultyChoice"));
    state.SetYesNoChoice(DeserializeChoice<GameEnums::YesNo>(data, "YesNoChoice"));
    state.SetUIChoice(DeserializeChoice<GameEnums::UIType>(data, "UIChoice"));
    state.SetSerializationChoice(DeserializeChoice<GameEnums::SerializationFormat>(data, "SerializationChoice"));
}

auto JSONDeserializer::DeserializeItemState(const nlohmann::json& data, ItemState& state) -> void
{
    state.SetDamage(data.value("damage", GameConfig::DEFAULT_DAMAGE));
    state.SetStateOfHandCuffs(data.value("wereHandCuffsUsed", GameEnums::YesNo::NO));
    state.SetStateOfMagnifier(data.value("wasMagnifierUsed", GameEnums::YesNo::NO));
    state.SetStateOfCellPhone(data.value("wasCellPhoneUsed", GameEnums::YesNo::NO));
    state.SetStateOfInverter(data.value("wasInverterUsed", GameEnums::YesNo::NO));
}

auto JSONDeserializer::DeserializeAll(const nlohmann::json& data, ApplicationState& app, DomainState& domain) -> void
{
    const auto version = data.value("version", GameConfig::GAME_VERSION);
    if (version != GameConfig::GAME_VERSION)
    {
        throw std::runtime_error("Unsupported save version!");
    }

    DeserializePlayer(data, domain.GetHuman());
    DeserializePlayer(data, domain.GetComputer());
    DeserializeMagazine(data, domain.GetMagazine());
    DeserializeGameLoopState(data, app.GetGameLoopState());
    DeserializeSerializationState(data, app.GetSerializationState());
    DeserializeAIState(data, app.GetAIState());
    DeserializeDecisionState(data, app.GetDecisionState());
    DeserializeItemState(data, domain.GetItemState());
}

auto JSONDeserializer::GetDeserializationLog() const -> std::string_view
{
    return m_serializationLog;
}

auto JSONDeserializer::Deserialize(ApplicationState& app, DomainState& domain, std::string_view filename) -> void
{
    try
    {
        m_serializationLog.clear();
        const auto saveDir =
            filename.starts_with("autosave") ? SaveConfig::GetAutoSaveDirectory() : SaveConfig::GetSaveDirectory();
        boost::static_string<GameConfig::LOG_LINE_RESERVE> path;
        std::format_to(std::back_inserter(path), "{}/{}.json", saveDir, filename);
        std::ifstream gameSave(path.c_str());
        if (!gameSave.is_open())
        {
            gameSave.close();
            throw std::runtime_error("File loading error!");
        }

        const auto data = nlohmann::json::parse(gameSave);
        gameSave.close();

        auto appSnapshot = app;
        auto domainSnapshot = domain;
        DeserializeAll(data, appSnapshot, domainSnapshot);
        m_validator.Validate(appSnapshot, domainSnapshot);
        DeserializeAll(data, app, domain);
    }
    catch (const std::exception& e)
    {
        m_serializationLog = e.what();
    }
}

#include "JSONSerializer.h"
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
#include <boost/static_string/static_string.hpp>
#include <exception>
#include <filesystem>
#include <format>
#include <fstream>
#include <iterator>
#include <nlohmann/json_fwd.hpp>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>

JSONSerializer::JSONSerializer()
{
    m_serializationLog.reserve(GameConfig::LOG_LINE_RESERVE);
}

auto JSONSerializer::GetSerializationLog() const -> std::string_view
{
    return m_serializationLog;
}

auto JSONSerializer::SerializePlayer(nlohmann::json& data, const Player& state) -> void
{
    using namespace GameEnums;
    const auto prefix = std::string(state.GetTypeString());
    data.emplace(prefix + "_name", state.GetName());
    data.emplace(prefix + "_type", state.GetType());

    const auto& playerHP = state.GetHP();
    data.emplace(prefix + "_HP", playerHP.GetHP());

    const auto& playerInventory = state.GetInventory();
    data.emplace(prefix + "_saws", playerInventory.GetItemCount(ItemType::SAW));
    data.emplace(prefix + "_beers", playerInventory.GetItemCount(ItemType::BEER));
    data.emplace(prefix + "_magnifiers", playerInventory.GetItemCount(ItemType::MAGNIFIER));
    data.emplace(prefix + "_cellphones", playerInventory.GetItemCount(ItemType::CELLPHONE));
    data.emplace(prefix + "_handcuffs", playerInventory.GetItemCount(ItemType::HANDCUFFS));
    data.emplace(prefix + "_inverters", playerInventory.GetItemCount(ItemType::INVERTER));
}

auto JSONSerializer::SerializeMagazine(nlohmann::json& data, const Magazine& state) -> void
{
    data.emplace("magazine", state.GetMagazine().m_magazine);
    data.emplace("magazineHead", state.GetMagazine().m_head);
    data.emplace("hitProbability", state.GetHitProbability());
}

auto JSONSerializer::SerializeGameLoopState(nlohmann::json& data, const GameLoopState& state) -> void
{
    data.emplace("starter", state.GetStarter());
    data.emplace("isInRestartMenu", state.GetIsInRestartMenu());
    data.emplace("stateOfGameLoop", state.GetStateOfGameLoop());
    data.emplace("Menu", state.GetCurrentMenu());
}

auto JSONSerializer::SerializeSerializationState(nlohmann::json& data, const SerializationState& state) -> void
{
    data.emplace("serializationType", state.GetSerializationType());
}

auto JSONSerializer::SerializeAIState(nlohmann::json& data, const AIState& state) -> void
{
    data.emplace("difficulty", state.GetDifficulty());
}

auto JSONSerializer::SerializeDecisionState(nlohmann::json& data, const DecisionState& state) -> void
{
    SerializeChoice(data, "MainChoice", state.GetMainChoice());
    SerializeChoice(data, "ItemChoice", state.GetItemChoice());
    SerializeChoice(data, "DifficultyChoice", state.GetDifficultyChoice());
    SerializeChoice(data, "YesNoChoice", state.GetYesNoChoice());
    SerializeChoice(data, "UIChoice", state.GetUIChoice());
    SerializeChoice(data, "SerializationChoice", state.GetSerializationChoice());
}

auto JSONSerializer::SerializeItemState(nlohmann::json& data, const ItemState& state) -> void
{
    data.emplace("damage", state.GetDamage());
    data.emplace("wereHandCuffsUsed", state.GetStateOfHandCuffs());
    data.emplace("wasMagnifierUsed", state.GetStateOfMagnifier());
    data.emplace("wasCellPhoneUsed", state.GetStateOfCellPhone());
    data.emplace("wasInverterUsed", state.GetStateOfInverter());
}

auto JSONSerializer::Serialize(const ApplicationState& app, const DomainState& domain, std::string_view filename) const
    -> void
{
    try
    {
        m_serializationLog.clear();
        const auto saveDirectory =
            filename.starts_with("autosave") ? SaveConfig::GetAutoSaveDirectory() : SaveConfig::GetSaveDirectory();
        if (!SaveConfig::CreateDirectoryIfNotExists(saveDirectory))
        {
            throw std::runtime_error("Save directory creation error!");
        }

        nlohmann::json data;
        data.emplace("version", GameConfig::GAME_VERSION);
        SerializePlayer(data, domain.GetHuman());
        SerializePlayer(data, domain.GetComputer());
        SerializeMagazine(data, domain.GetMagazine());
        SerializeGameLoopState(data, app.GetGameLoopState());
        SerializeSerializationState(data, app.GetSerializationState());
        SerializeAIState(data, app.GetAIState());
        SerializeDecisionState(data, app.GetDecisionState());
        SerializeItemState(data, domain.GetItemState());

        boost::static_string<GameConfig::LOG_LINE_RESERVE> path;
        std::format_to(std::back_inserter(path), "{}/{}.json", saveDirectory, filename);
        boost::static_string<GameConfig::LOG_LINE_RESERVE> tmpPath;
        std::format_to(std::back_inserter(tmpPath), "{}/{}.tmp", saveDirectory, filename);
        std::ofstream gameSave(tmpPath.c_str());
        if (!gameSave.is_open())
        {
            throw std::runtime_error("File saving error!");
        }

        gameSave << data.dump(4);
        gameSave.close();

        std::error_code errorCode;
        std::filesystem::rename(tmpPath.c_str(), path.c_str(), errorCode);
        if (errorCode)
        {
            throw std::runtime_error("File renaming error");
        }
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

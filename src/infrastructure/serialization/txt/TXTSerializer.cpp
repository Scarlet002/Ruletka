#include "TXTSerializer.h"
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
#include <stdexcept>
#include <string_view>
#include <system_error>
#include <utility>

TXTSerializer::TXTSerializer()
{
    m_serializationLog.reserve(GameConfig::LOG_LINE_RESERVE);
}

auto TXTSerializer::GetSerializationLog() const -> std::string_view
{
    return m_serializationLog;
}

auto TXTSerializer::SerializePlayer(std::ofstream& file, const Player& state) -> void
{
    file << state.GetName() << '\n';
    file << static_cast<int>(state.GetType()) << '\n';

    const auto& playerHp = state.GetHP();
    file << static_cast<int>(playerHp.GetHP()) << '\n';

    const auto& playerInventory = state.GetInventory();
    for (const auto& item : GameConfig::ITEM_TYPES)
    {
        file << static_cast<int>(playerInventory.GetItemCount(item.second)) << '\n';
    }
}

auto TXTSerializer::SerializeMagazine(std::ofstream& file, const Magazine& state) -> void
{
    const auto magazine = state.GetMagazine();
    for (const auto& bullet : magazine.m_magazine)
    {
        file << static_cast<int>(std::to_underlying(bullet)) << '\n';
    }
    file << static_cast<int>(magazine.m_head) << '\n';
    file << state.GetHitProbability() << '\n';
}

auto TXTSerializer::SerializeGameLoopState(std::ofstream& file, const GameLoopState& state) -> void
{
    file << static_cast<int>(std::to_underlying(state.GetStarter())) << '\n';
    file << static_cast<int>(std::to_underlying(state.GetIsInRestartMenu())) << '\n';
    file << static_cast<int>(std::to_underlying(state.GetStateOfGameLoop())) << '\n';
    file << static_cast<int>(std::to_underlying(state.GetCurrentMenu())) << '\n';
}

auto TXTSerializer::SerializeSerializationState(std::ofstream& file, const SerializationState& state) -> void
{
    file << static_cast<int>(std::to_underlying(state.GetSerializationType())) << '\n';
}

auto TXTSerializer::SerializeAIState(std::ofstream& file, const AIState& state) -> void
{
    file << static_cast<int>(std::to_underlying(state.GetDifficulty())) << '\n';
}

auto TXTSerializer::SerializeDecisionState(std::ofstream& file, const DecisionState& state) -> void
{
    SerializeChoice<GameEnums::MainChoice>(file, state.GetMainChoice());
    SerializeChoice<GameEnums::ItemType>(file, state.GetItemChoice());
    SerializeChoice<GameEnums::Difficulty>(file, state.GetDifficultyChoice());
    SerializeChoice<GameEnums::YesNo>(file, state.GetYesNoChoice());
    SerializeChoice<GameEnums::UIType>(file, state.GetUIChoice());
    SerializeChoice<GameEnums::SerializationFormat>(file, state.GetSerializationChoice());
}

auto TXTSerializer::SerializeItemState(std::ofstream& file, const ItemState& state) -> void
{
    file << static_cast<int>(state.GetDamage()) << '\n';
    file << static_cast<int>(std::to_underlying(state.GetStateOfHandCuffs())) << '\n';
    file << static_cast<int>(std::to_underlying(state.GetStateOfMagnifier())) << '\n';
    file << static_cast<int>(std::to_underlying(state.GetStateOfCellPhone())) << '\n';
    file << static_cast<int>(std::to_underlying(state.GetStateOfInverter())) << '\n';
}

auto TXTSerializer::Serialize(const ApplicationState& app, const DomainState& domain, std::string_view filename) const
    -> void
{
    try
    {
        m_serializationLog.clear();
        auto saveDirectory =
            filename.starts_with("autosave") ? SaveConfig::GetAutoSaveDirectory() : SaveConfig::GetSaveDirectory();
        if (!SaveConfig::CreateDirectoryIfNotExists(saveDirectory))
        {
            throw std::runtime_error("Save directory creation error!");
        }

        boost::static_string<GameConfig::LOG_LINE_RESERVE> path;
        std::format_to(std::back_inserter(path), "{}/{}.txt", saveDirectory, filename);
        boost::static_string<GameConfig::LOG_LINE_RESERVE> tmpPath;
        std::format_to(std::back_inserter(tmpPath), "{}/{}.tmp", saveDirectory, filename);
        std::ofstream gameSave(tmpPath.c_str());
        if (!gameSave.is_open())
        {
            throw std::runtime_error("File saving error!");
        }

        gameSave << GameConfig::GAME_VERSION << '\n';
        SerializePlayer(gameSave, domain.GetHuman());
        SerializePlayer(gameSave, domain.GetComputer());
        SerializeMagazine(gameSave, domain.GetMagazine());
        SerializeGameLoopState(gameSave, app.GetGameLoopState());
        SerializeSerializationState(gameSave, app.GetSerializationState());
        SerializeAIState(gameSave, app.GetAIState());
        SerializeDecisionState(gameSave, app.GetDecisionState());
        SerializeItemState(gameSave, domain.GetItemState());

        if (gameSave.fail())
        {
            throw std::runtime_error("Gamestate saving error!");
        }

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

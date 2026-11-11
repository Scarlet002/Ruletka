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
#include <format>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string_view>
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
    for (const auto& bullet : state.GetMagazine().m_magazine)
    {
        file << static_cast<int>(std::to_underlying(bullet)) << '\n';
    }
    file << state.GetHitProbability() << '\n';
}

auto TXTSerializer::SerializeGameLoopState(std::ofstream& file, const GameLoopState& state) -> void
{
    file << static_cast<int>(std::to_underlying(state.GetStarter())) << '\n';
    file << static_cast<int>(std::to_underlying(state.GetIsOnePlayerAlive())) << '\n';
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

        boost::static_string<GameConfig::LOG_LINE_RESERVE> fullPath;
        std::format_to(std::back_inserter(fullPath), "{}/{}.txt", saveDirectory, filename);
        std::ofstream gameSave(fullPath.c_str());
        if (!gameSave.is_open())
        {
            throw std::runtime_error("File saving error!");
        }

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
    }
    catch (const std::exception& e)
    {
        m_serializationLog = e.what();
    }
}

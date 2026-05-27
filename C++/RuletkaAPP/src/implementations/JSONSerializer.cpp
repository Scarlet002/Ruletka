#include "JSONSerializer.h"
#include "SaveConfig.h"
#include "IGameState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "IPlayer.h"
#include "Magazine.h"
#include "ItemState.h"
#include "DecisionState.h"
#include "GameLoopState.h"
#include "SerializationState.h"
#include "AIState.h"
#include "IInventory.h"
#include "HP.h"
#include <fstream>
#include <stdexcept>

std::string JSONSerializer::GetSerializationLog() const noexcept
{
    return serializationLog;
}

void JSONSerializer::SerializePlayer(nlohmann::json& data, const PlayerData& pd)
{
    data["human_name"] = pd.name;
    data["human_type"] = pd.type;
    data["human_HP"] = pd.hp;
    data["human_saws"] = pd.saws;
    data["human_beers"] = pd.beers;
    data["human_magnifiers"] = pd.magnifiers;
    data["human_cellphones"] = pd.cellphones;
    data["human_handcuffs"] = pd.handcuffs;
    data["human_inverters"] = pd.inverters;
    data["human_itemsCount"] = pd.itemsCount;
}

void JSONSerializer::SerializeComputer(nlohmann::json& data, const PlayerData& pd)
{
    data["computer_name"] = pd.name;
    data["computer_type"] = pd.type;
    data["computer_HP"] = pd.hp;
    data["computer_saws"] = pd.saws;
    data["computer_beers"] = pd.beers;
    data["computer_magnifiers"] = pd.magnifiers;
    data["computer_cellphones"] = pd.cellphones;
    data["computer_handcuffs"] = pd.handcuffs;
    data["computer_inverters"] = pd.inverters;
    data["computer_itemsCount"] = pd.itemsCount;
}

void JSONSerializer::SerializeMagazine(nlohmann::json& data, const MagazineData& md)
{
    for (uint8_t item : md.magazine)
        data["magazine"].push_back(item);
    data["hitProbability"] = md.hitProbability;
}

void JSONSerializer::SerializeGameLoopState(nlohmann::json& data, const GameLoopStateData& gls)
{
    data["starter"] = gls.starter;
    data["isOnePlayerAlive"] = gls.isOnePlayerAlive;
    data["stateOfGameLoop"] = gls.stateOfGameLoop;
}

void JSONSerializer::SerializeSerializationState(nlohmann::json& data, const SerializationStateData& ss)
{
    data["serializationType"] = ss.serializationType;
}

void JSONSerializer::SerializeAIState(nlohmann::json& data, const AIStateData& ais)
{
    data["difficulty"] = ais.difficulty;
    data["recentDifficulty"] = ais.recentDifficulty;
}

void JSONSerializer::SerializeDecisionState(nlohmann::json& data, const DecisionStateData& ds)
{
    data["choice"] = ds.choice;
    data["previousChoice"] = ds.previousChoice;
    data["currentMenu"] = ds.currentMenu;
}

void JSONSerializer::SerializeItemState(nlohmann::json& data, const ItemStateData& is)
{
    data["damage"] = is.damage;
    data["wereHandCuffsUsed"] = is.wereHandCuffsUsed;
    data["wasMagnifierUsed"] = is.wasMagnifierUsed;
    data["wasCellPhoneUsed"] = is.wasCellPhoneUsed;
}

JSONSerializer::PlayerData JSONSerializer::DeserializePlayer(const nlohmann::json& data)
{
    PlayerData pd;
    pd.name = data.value("human_name", "");
    pd.type = data.value("human_type", "");
    pd.hp = data.value("human_HP", 0);
    pd.saws = data.value("human_saws", 0);
    pd.beers = data.value("human_beers", 0);
    pd.magnifiers = data.value("human_magnifiers", 0);
    pd.cellphones = data.value("human_cellphones", 0);
    pd.handcuffs = data.value("human_handcuffs", 0);
    pd.inverters = data.value("human_inverters", 0);
    pd.itemsCount = data.value("human_itemsCount", 0);
    return pd;
}

JSONSerializer::PlayerData JSONSerializer::DeserializeComputer(const nlohmann::json& data)
{
    PlayerData pd;
    pd.name = data.value("computer_name", "");
    pd.type = data.value("computer_type", "");
    pd.hp = data.value("computer_HP", 0);
    pd.saws = data.value("computer_saws", 0);
    pd.beers = data.value("computer_beers", 0);
    pd.magnifiers = data.value("computer_magnifiers", 0);
    pd.cellphones = data.value("computer_cellphones", 0);
    pd.handcuffs = data.value("computer_handcuffs", 0);
    pd.inverters = data.value("computer_inverters", 0);
    pd.itemsCount = data.value("computer_itemsCount", 0);
    return pd;
}

JSONSerializer::MagazineData JSONSerializer::DeserializeMagazine(const nlohmann::json& data)
{
    MagazineData md;
    if (data.contains("magazine") && data["magazine"].is_array())
    {
        for (const auto& item : data["magazine"])
            md.magazine.push_back(item.get<uint8_t>());
    }
    md.hitProbability = data.value("hitProbability", 0.0f);
    return md;
}

JSONSerializer::GameLoopStateData JSONSerializer::DeserializeGameLoopState(const nlohmann::json& data)
{
    GameLoopStateData gls;
    gls.starter = data.value("starter", GameEnums::HUMAN);
    gls.isOnePlayerAlive = data.value("isOnePlayerAlive", false);
    gls.stateOfGameLoop = data.value("stateOfGameLoop", true);
    return gls;
}

JSONSerializer::SerializationStateData JSONSerializer::DeserializeSerializationState(const nlohmann::json& data)
{
    SerializationStateData ss;
    ss.serializationType = data.value("serializationType", GameEnums::JSON);
    return ss;
}

JSONSerializer::AIStateData JSONSerializer::DeserializeAIState(const nlohmann::json& data)
{
    AIStateData ais;
    ais.difficulty = data.value("difficulty", GameConfig::defaultDifficulty);
    ais.recentDifficulty = data.value("recentDifficulty", GameConfig::defaultDifficulty);
    return ais;
}

JSONSerializer::DecisionStateData JSONSerializer::DeserializeDecisionState(const nlohmann::json& data)
{
    DecisionStateData ds;
    ds.choice = data.value("choice", GameEnums::NO_CHOICE);
    ds.previousChoice = data.value("previousChoice", GameEnums::EXIT);
    ds.currentMenu = data.value("currentMenu", GameEnums::MAIN_MENU);
    return ds;
}

JSONSerializer::ItemStateData JSONSerializer::DeserializeItemState(const nlohmann::json& data)
{
    ItemStateData is;
    is.damage = data.value("damage", GameConfig::defaultDamage);
    is.wereHandCuffsUsed = data.value("wereHandCuffsUsed", false);
    is.wasMagnifierUsed = data.value("wasMagnifierUsed", false);
    is.wasCellPhoneUsed = data.value("wasCellPhoneUsed", false);
    return is;
}

void JSONSerializer::ValidatePlayer(const PlayerData& pd)
{
    if (pd.type != "human" && pd.type != "Human" && pd.type != "HUMAN")
        throw std::runtime_error("Nieprawidlowy typ gracza w pliku JSON!");
    if (!(pd.hp >= 0 && pd.hp <= GameConfig::maxPlayerHP))
        throw std::runtime_error("Nieprawidlowa wartosc HP gracza w pliku JSON!");
    if (!(pd.saws <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba pil gracza w pliku JSON!");
    if (!(pd.beers <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba piw gracza w pliku JSON!");
    if (!(pd.magnifiers <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba lup gracza w pliku JSON!");
    if (!(pd.cellphones <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba telefonow gracza w pliku JSON!");
    if (!(pd.handcuffs <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba kajdanek gracza w pliku JSON!");
    if (!(pd.inverters <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba inwerterow gracza w pliku JSON!");
    if (!(pd.itemsCount <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba przedmiotow gracza w pliku JSON!");
}

void JSONSerializer::ValidateComputer(const PlayerData& pd)
{
    if (pd.type != "computer" && pd.type != "Computer" && pd.type != "COMPUTER")
        throw std::runtime_error("Nieprawidlowy typ komputera w pliku JSON!");
    if (!(pd.hp >= 0 && pd.hp <= GameConfig::maxPlayerHP))
        throw std::runtime_error("Nieprawidlowa wartosc HP komputera w pliku JSON!");
    if (!(pd.saws <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba pil komputera w pliku JSON!");
    if (!(pd.beers <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba piw komputera w pliku JSON!");
    if (!(pd.magnifiers <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba lup komputera w pliku JSON!");
    if (!(pd.cellphones <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba telefonow komputera w pliku JSON!");
    if (!(pd.handcuffs <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba kajdanek komputera w pliku JSON!");
    if (!(pd.inverters <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba inwerterow komputera w pliku JSON!");
    if (!(pd.itemsCount <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba przedmiotow komputera w pliku JSON!");
}

void JSONSerializer::ValidateMagazine(const MagazineData& md)
{
    for (const auto& bullet : md.magazine)
    {
        if (bullet > GameConfig::bulletTypes)
            throw std::runtime_error("Nieprawidlowy typ pocisku w pliku JSON!");
    }
    if (!(md.magazine.size() >= GameConfig::minBullets && md.magazine.size() <= GameConfig::maxBullets))
        throw std::runtime_error("Nieprawidlowy rozmiar magazynka w pliku JSON!");
    if (md.hitProbability < 0.0f || md.hitProbability > 1.0f)
        throw std::runtime_error("Nieprawidlowe prawdopodobienstwo trafienia w pliku JSON!");
}

void JSONSerializer::ValidateGameLoopState(const GameLoopStateData& data)
{
    if (!(data.starter == GameEnums::COMPUTER || data.starter == GameEnums::HUMAN))
        throw std::runtime_error("Nieprawidlowy starter w pliku JSON!");
    if (!(data.isOnePlayerAlive == 0 || data.isOnePlayerAlive == 1))
        throw std::runtime_error("Nieprawidlowa wartosc flagi zycia graczy w pliku JSON!");
    if (!(data.stateOfGameLoop == 0 || data.stateOfGameLoop == 1))
        throw std::runtime_error("Nieprawidlowa wartosc flagi stanu petli gry w pliku JSON!");
}

void JSONSerializer::ValidateSerializationState(const SerializationStateData& data)
{
    if (!(data.serializationType == GameEnums::JSON || data.serializationType == GameEnums::TXT))
        throw std::runtime_error("Nieprawidlowy typ serializacji w pliku JSON!");
}

void JSONSerializer::ValidateAIState(const AIStateData& data)
{
    if (!(data.difficulty >= GameEnums::NORMAL && data.difficulty <= GameEnums::HARD))
        throw std::runtime_error("Nieprawidlowy poziom trudnosci w pliku JSON!");
    if (!(data.recentDifficulty >= GameEnums::NORMAL && data.recentDifficulty <= GameEnums::HARD))
        throw std::runtime_error("Nieprawidlowy zapamietany poziom trudnosci w pliku JSON!");
}

void JSONSerializer::ValidateDecisionState(const DecisionStateData& data)
{
    if (!(data.choice >= GameEnums::NO_CHOICE && data.choice <= GameEnums::SERIALIZATION))
        throw std::runtime_error("Nieprawidlowy wybor w pliku JSON!");
    if (!(data.previousChoice >= GameEnums::NO_CHOICE && data.previousChoice <= GameEnums::SERIALIZATION))
        throw std::runtime_error("Nieprawidlowy poprzedni wybor w pliku JSON!");
    if (!(data.currentMenu >= GameEnums::MAIN_MENU && data.currentMenu <= GameEnums::RESTART_MENU))
        throw std::runtime_error("Nieprawidlowe okno menu w pliku JSON!");
}

void JSONSerializer::ValidateItemState(const ItemStateData& data)
{
    if (!(data.damage == GameConfig::defaultDamage || data.damage == GameConfig::sawDamage))
        throw std::runtime_error("Nieprawidlowa wartosc obrazen w pliku JSON!");
    if (!(data.wereHandCuffsUsed == 0 || data.wereHandCuffsUsed == 1))
        throw std::runtime_error("Nieprawidlowa wartosc flagi kajdanek w pliku JSON!");
    if (!(data.wasMagnifierUsed == 0 || data.wasMagnifierUsed == 1))
        throw std::runtime_error("Nieprawidlowa wartosc flagi lupy w pliku JSON!");
    if (!(data.wasCellPhoneUsed == 0 || data.wasCellPhoneUsed == 1))
        throw std::runtime_error("Nieprawidlowa wartosc flagi telefonu w pliku JSON!");
}

void JSONSerializer::Serialize(const std::shared_ptr<IGameState> gs, const std::string& fileName)
{
    try
    {
        std::string saveDir = (fileName.find("autosave") == 0)
            ? SaveConfig::GetAutoSaveDirectory() : SaveConfig::GetSaveDirectory();
        if (!SaveConfig::CreateDirectoryIfNotExists(saveDir))
            throw std::runtime_error("Nie mozna utworzyc katalogu zapisow!");

        std::string fullPath = saveDir + "/" + fileName + ".json";
        nlohmann::json data;

        PlayerData humanData;
        humanData.name = gs->GetHuman().GetName();
        humanData.type = gs->GetHuman().GetTypeString();
        humanData.hp = gs->GetHumanHP().GetHP();
        humanData.saws = gs->GetHumanInventory().GetItemCount(GameEnums::SAW);
        humanData.beers = gs->GetHumanInventory().GetItemCount(GameEnums::BEER);
        humanData.magnifiers = gs->GetHumanInventory().GetItemCount(GameEnums::MAGNIFIER);
        humanData.cellphones = gs->GetHumanInventory().GetItemCount(GameEnums::CELLPHONE);
        humanData.handcuffs = gs->GetHumanInventory().GetItemCount(GameEnums::HANDCUFFS);
        humanData.inverters = gs->GetHumanInventory().GetItemCount(GameEnums::INVERTER);
        SerializePlayer(data, humanData);

        PlayerData computerData;
        computerData.name = gs->GetComputer().GetName();
        computerData.type = gs->GetComputer().GetTypeString();
        computerData.hp = gs->GetComputerHP().GetHP();
        computerData.saws = gs->GetComputerInventory().GetItemCount(GameEnums::SAW);
        computerData.beers = gs->GetComputerInventory().GetItemCount(GameEnums::BEER);
        computerData.magnifiers = gs->GetComputerInventory().GetItemCount(GameEnums::MAGNIFIER);
        computerData.cellphones = gs->GetComputerInventory().GetItemCount(GameEnums::CELLPHONE);
        computerData.handcuffs = gs->GetComputerInventory().GetItemCount(GameEnums::HANDCUFFS);
        computerData.inverters = gs->GetComputerInventory().GetItemCount(GameEnums::INVERTER);
        SerializeComputer(data, computerData);

        MagazineData magazineData;
        magazineData.magazine = gs->GetMagazine().GetMagazine();
        magazineData.hitProbability = gs->GetMagazine().GetHitProbability();
        SerializeMagazine(data, magazineData);

        GameLoopStateData glsData;
        glsData.starter = gs->GetGameLoopState().GetStarter();
        glsData.isOnePlayerAlive = gs->GetGameLoopState().GetIsOnePlayerAlive();
        glsData.stateOfGameLoop = gs->GetGameLoopState().GetStateOfGameLoop();
        SerializeGameLoopState(data, glsData);

        SerializationStateData ssData;
        ssData.serializationType = gs->GetSerializationState().GetSerializationType();
        SerializeSerializationState(data, ssData);

        AIStateData aisData;
        aisData.difficulty = gs->GetAIState().GetDifficulty();
        aisData.recentDifficulty = gs->GetAIState().GetRecentDifficulty();
        SerializeAIState(data, aisData);

        DecisionStateData dsData;
        dsData.choice = gs->GetDecisionState().GetChoice();
        dsData.previousChoice = gs->GetDecisionState().GetPreviousChoice();
        dsData.currentMenu = gs->GetDecisionState().GetCurrentMenu();
        SerializeDecisionState(data, dsData);

        ItemStateData isData;
        isData.damage = gs->GetItemState().GetDamage();
        isData.wereHandCuffsUsed = gs->GetItemState().GetStateOfHandCuffs();
        isData.wasMagnifierUsed = gs->GetItemState().GetStateOfMagnifier();
        isData.wasCellPhoneUsed = gs->GetItemState().GetStateOfCellPhone();
        SerializeItemState(data, isData);

        std::ofstream gameSave(fullPath);
        if (!gameSave.is_open())
            throw std::runtime_error("Nie mozna otworzyc pliku!");
        gameSave << data.dump(4);
        gameSave.close();
    }
    catch (const std::exception& e)
    {
        serializationLog = e.what();
    }
}

void JSONSerializer::Deserialize(std::shared_ptr<IGameState> gs, const std::string& fileName)
{
    try
    {
        std::string saveDir = (fileName.find("autosave") == 0)
            ? SaveConfig::GetAutoSaveDirectory() : SaveConfig::GetSaveDirectory();
        std::string fullPath = saveDir + "/" + fileName + ".json";
        std::ifstream gameSave(fullPath);
        if (!gameSave.is_open())
            throw std::runtime_error("Nie mozna otworzyc pliku podczas wczytywania!");

        nlohmann::json data = nlohmann::json::parse(gameSave);
        gameSave.close();

        PlayerData hd = DeserializePlayer(data);
        PlayerData cd = DeserializeComputer(data);
        MagazineData md = DeserializeMagazine(data);
        GameLoopStateData glsData = DeserializeGameLoopState(data);
        SerializationStateData ssData = DeserializeSerializationState(data);
        AIStateData aisData = DeserializeAIState(data);
        DecisionStateData dsData = DeserializeDecisionState(data);
        ItemStateData isData = DeserializeItemState(data);

        ValidatePlayer(hd);
        ValidateComputer(cd);
        ValidateMagazine(md);
        ValidateGameLoopState(glsData);
        ValidateSerializationState(ssData);
        ValidateAIState(aisData);
        ValidateDecisionState(dsData);
        ValidateItemState(isData);

        gs->GetHuman().SetName(hd.name);
        gs->GetHuman().SetType(hd.type);
        gs->GetHumanHP().SetHP(hd.hp);
        gs->GetHumanInventory().SetItemCount(GameEnums::SAW, hd.saws);
        gs->GetHumanInventory().SetItemCount(GameEnums::BEER, hd.beers);
        gs->GetHumanInventory().SetItemCount(GameEnums::MAGNIFIER, hd.magnifiers);
        gs->GetHumanInventory().SetItemCount(GameEnums::CELLPHONE, hd.cellphones);
        gs->GetHumanInventory().SetItemCount(GameEnums::HANDCUFFS, hd.handcuffs);
        gs->GetHumanInventory().SetItemCount(GameEnums::INVERTER, hd.inverters);

        gs->GetComputer().SetName(cd.name);
        gs->GetComputer().SetType(cd.type);
        gs->GetComputerHP().SetHP(cd.hp);
        gs->GetComputerInventory().SetItemCount(GameEnums::SAW, cd.saws);
        gs->GetComputerInventory().SetItemCount(GameEnums::BEER, cd.beers);
        gs->GetComputerInventory().SetItemCount(GameEnums::MAGNIFIER, cd.magnifiers);
        gs->GetComputerInventory().SetItemCount(GameEnums::CELLPHONE, cd.cellphones);
        gs->GetComputerInventory().SetItemCount(GameEnums::HANDCUFFS, cd.handcuffs);
        gs->GetComputerInventory().SetItemCount(GameEnums::INVERTER, cd.inverters);

        gs->GetMagazine().SetMagazine(md.magazine);
        gs->GetMagazine().SetHitProbability(md.hitProbability);
        gs->GetMagazine().CheckBullets();

        gs->GetGameLoopState().SetStarter(glsData.starter);
        gs->GetGameLoopState().SetIsOnePlayerAlive(glsData.isOnePlayerAlive);
        gs->GetGameLoopState().SetStateOfGameLoop(glsData.stateOfGameLoop);

        gs->GetSerializationState().SetSerializationType(ssData.serializationType);

        gs->GetAIState().SetDifficulty(aisData.difficulty);
        gs->GetAIState().SetRecentDifficulty(aisData.recentDifficulty);

        gs->GetDecisionState().SetChoice(dsData.choice);
        gs->GetDecisionState().SetPreviousChoice(dsData.previousChoice);
        gs->GetDecisionState().SetCurrentMenu(dsData.currentMenu);

        gs->GetItemState().SetDamage(isData.damage);
        gs->GetItemState().SetStateOfHandCuffs(isData.wereHandCuffsUsed);
        gs->GetItemState().SetStateOfMagnifier(isData.wasMagnifierUsed);
        gs->GetItemState().SetStateOfCellPhone(isData.wasCellPhoneUsed);
    }
    catch (const std::exception& e)
    {
        serializationLog = e.what();
    }
}
#include "TXTSerializer.h"
#include "SaveConfig.h"
#include "GameEnums.h"
#include "GameConfig.h"
#include "IGameState.h"
#include "HP.h"
#include "IInventory.h"
#include "IPlayer.h"
#include "Magazine.h"
#include "GameLoopState.h"
#include "DecisionState.h"
#include "ItemState.h"
#include "AIState.h"
#include "SerializationState.h"
#include <fstream>
#include <stdexcept>

std::string TXTSerializer::GetSerializationLog() const noexcept
{
    return serializationLog;
}

void TXTSerializer::SerializePlayer(std::ofstream& file, const PlayerData& data)
{
    file << data.name << '\n';
    file << data.type << '\n';
    file << data.hp << '\n';
    file << data.saws << '\n';
    file << data.beers << '\n';
    file << data.magnifiers << '\n';
    file << data.cellphones << '\n';
    file << data.handcuffs << '\n';
    file << data.inverters << '\n';
    file << data.itemsCount << '\n';
}

void TXTSerializer::SerializeComputer(std::ofstream& file, const PlayerData& data)
{
    file << data.name << '\n';
    file << data.type << '\n';
    file << data.hp << '\n';
    file << data.saws << '\n';
    file << data.beers << '\n';
    file << data.magnifiers << '\n';
    file << data.cellphones << '\n';
    file << data.handcuffs << '\n';
    file << data.inverters << '\n';
    file << data.itemsCount << '\n';
}

void TXTSerializer::SerializeMagazine(std::ofstream& file, const MagazineData& data)
{
    file << data.bulletCount << '\n';
    for (uint8_t item : data.magazine)
        file << item << '\n';
    file << data.hitProbability << '\n';
}

void TXTSerializer::SerializeGameLoopState(std::ofstream& file, const GameLoopStateData& data)
{
    file << data.starter << '\n';
    file << data.isOnePlayerAlive << '\n';
    file << data.stateOfGameLoop << '\n';
}

void TXTSerializer::SerializeSerializationState(std::ofstream& file, const SerializationStateData& data)
{
    file << data.serializationType << '\n';
}

void TXTSerializer::SerializeAIState(std::ofstream& file, const AIStateData& data)
{
    file << data.difficulty << '\n';
    file << data.recentDifficulty << '\n';
}

void TXTSerializer::SerializeDecisionState(std::ofstream& file, const DecisionStateData& data)
{
    file << data.choice << '\n';
    file << data.previousChoice << '\n';
    file << data.currentMenu << '\n';
}

void TXTSerializer::SerializeItemState(std::ofstream& file, const ItemStateData& data)
{
    file << data.damage << '\n';
    file << data.wereHandCuffsUsed << '\n';
    file << data.wasMagnifierUsed << '\n';
    file << data.wasCellPhoneUsed << '\n';
}

TXTSerializer::PlayerData TXTSerializer::DeserializePlayer(std::ifstream& file)
{
    PlayerData pd;
    file >> pd.name >> pd.type;
    file >> pd.hp >> pd.saws >> pd.beers >> pd.magnifiers
        >> pd.cellphones >> pd.handcuffs >> pd.inverters >> pd.itemsCount;
    return pd;
}

TXTSerializer::PlayerData TXTSerializer::DeserializeComputer(std::ifstream& file)
{
    PlayerData pd;
    file >> pd.name >> pd.type;
    file >> pd.hp >> pd.saws >> pd.beers >> pd.magnifiers
        >> pd.cellphones >> pd.handcuffs >> pd.inverters >> pd.itemsCount;
    return pd;
}

TXTSerializer::MagazineData TXTSerializer::DeserializeMagazine(std::ifstream& file)
{
    MagazineData md;
    file >> md.bulletCount;
    for (uint8_t i = 0; i < md.bulletCount; ++i)
    {
        uint8_t bullet;
        file >> bullet;
        md.magazine.push_back(bullet);
    }
    file >> md.hitProbability;
    return md;
}

TXTSerializer::GameLoopStateData TXTSerializer::DeserializeGameLoopState(std::ifstream& file)
{
    GameLoopStateData data;
    file >> data.starter;
    file >> data.isOnePlayerAlive;
    file >> data.stateOfGameLoop;
    return data;
}

TXTSerializer::SerializationStateData TXTSerializer::DeserializeSerializationState(std::ifstream& file)
{
    SerializationStateData data;
    file >> data.serializationType;
    return data;
}

TXTSerializer::AIStateData TXTSerializer::DeserializeAIState(std::ifstream& file)
{
    AIStateData data;
    file >> data.difficulty;
    file >> data.recentDifficulty;
    return data;
}

TXTSerializer::DecisionStateData TXTSerializer::DeserializeDecisionState(std::ifstream& file)
{
    DecisionStateData data;
    file >> data.choice;
    file >> data.previousChoice;
    file >> data.currentMenu;
    return data;
}

TXTSerializer::ItemStateData TXTSerializer::DeserializeItemState(std::ifstream& file)
{
    ItemStateData data;
    file >> data.damage;
    file >> data.wereHandCuffsUsed;
    file >> data.wasMagnifierUsed;
    file >> data.wasCellPhoneUsed;
    return data;
}

void TXTSerializer::ValidatePlayer(const PlayerData& pd)
{
    if (pd.type != "human" && pd.type != "Human" && pd.type != "HUMAN")
        throw std::runtime_error("Nieprawidlowy typ gracza w pliku TXT!");
    if (!(pd.hp >= 0 && pd.hp <= GameConfig::maxPlayerHP))
        throw std::runtime_error("Nieprawidlowa wartosc HP gracza w pliku TXT!");
    if (!(pd.saws <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba pil gracza w pliku TXT!");
    if (!(pd.beers <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba piw gracza w pliku TXT!");
    if (!(pd.magnifiers <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba lup gracza w pliku TXT!");
    if (!(pd.cellphones <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba telefonow gracza w pliku TXT!");
    if (!(pd.handcuffs <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba kajdanek gracza w pliku TXT!");
    if (!(pd.inverters <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba inwerterow gracza w pliku TXT!");
    if (!(pd.itemsCount <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba przedmiotow gracza w pliku TXT!");

    uint8_t sum = pd.saws + pd.beers + pd.magnifiers + pd.cellphones + pd.handcuffs + pd.inverters;
    if (pd.itemsCount != sum)
        throw std::runtime_error("Niespojna liczba przedmiotow gracza w pliku TXT!");
}

void TXTSerializer::ValidateComputer(const PlayerData& pd)
{
    if (pd.type != "computer" && pd.type != "Computer" && pd.type != "COMPUTER")
        throw std::runtime_error("Nieprawidlowy typ komputera w pliku TXT!");
    if (!(pd.hp >= 0 && pd.hp <= GameConfig::maxPlayerHP))
        throw std::runtime_error("Nieprawidlowa wartosc HP komputera w pliku TXT!");
    if (!(pd.saws <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba pil komputera w pliku TXT!");
    if (!(pd.beers <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba piw komputera w pliku TXT!");
    if (!(pd.magnifiers <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba lup komputera w pliku TXT!");
    if (!(pd.cellphones <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba telefonow komputera w pliku TXT!");
    if (!(pd.handcuffs <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba kajdanek komputera w pliku TXT!");
    if (!(pd.inverters <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba inwerterow komputera w pliku TXT!");
    if (!(pd.itemsCount <= GameConfig::maxItemsFiveSlots))
        throw std::runtime_error("Nieprawidlowa liczba przedmiotow komputera w pliku TXT!");

    uint8_t sum = pd.saws + pd.beers + pd.magnifiers + pd.cellphones + pd.handcuffs + pd.inverters;
    if (pd.itemsCount != sum)
        throw std::runtime_error("Niespojna liczba przedmiotow komputera w pliku TXT!");
}

void TXTSerializer::ValidateMagazine(const MagazineData& md)
{
    if (md.bulletCount > GameConfig::maxBullets)
        throw std::runtime_error("Zadeklarowana liczba pociskow przekracza maksymalna!");
    for (const auto& bullet : md.magazine)
    {
        if (bullet > GameConfig::bulletTypes)
            throw std::runtime_error("Nieprawidlowy typ pocisku w pliku TXT!");
    }
    if (md.magazine.size() != md.bulletCount)
        throw std::runtime_error("Nieprawidlowa liczba pociskow w pliku TXT (za malo)");
    if (!(md.bulletCount >= GameConfig::minBullets && md.magazine.size() <= GameConfig::maxBullets))
        throw std::runtime_error("Nieprawidlowy rozmiar magazynka w pliku TXT!");
    if (md.hitProbability < 0.0f || md.hitProbability > 1.0f)
        throw std::runtime_error("Nieprawidlowe prawdopodobienstwo trafienia w pliku TXT!");
}

void TXTSerializer::ValidateGameLoopState(const GameLoopStateData& data)
{
    if (!(data.starter == GameEnums::COMPUTER || data.starter == GameEnums::HUMAN))
        throw std::runtime_error("Nieprawidlowy starter w pliku TXT!");
    if (!(data.isOnePlayerAlive == 0 || data.isOnePlayerAlive == 1))
        throw std::runtime_error("Nieprawidlowa wartosc flagi zycia graczy w pliku TXT!");
    if (!(data.stateOfGameLoop == 0 || data.stateOfGameLoop == 1))
        throw std::runtime_error("Nieprawidlowa wartosc flagi stanu petli gry w pliku TXT!");
}

void TXTSerializer::ValidateSerializationState(const SerializationStateData& data)
{
    if (!(data.serializationType == GameEnums::JSON || data.serializationType == GameEnums::TXT))
        throw std::runtime_error("Nieprawidlowy typ serializacji w pliku TXT!");
}

void TXTSerializer::ValidateAIState(const AIStateData& data)
{
    if (!(data.difficulty >= GameEnums::NORMAL && data.difficulty <= GameEnums::HARD))
        throw std::runtime_error("Nieprawidlowy poziom trudnosci w pliku TXT!");
    if (!(data.recentDifficulty >= GameEnums::NORMAL && data.recentDifficulty <= GameEnums::HARD))
        throw std::runtime_error("Nieprawidlowy zapamietany poziom trudnosci w pliku TXT!");
}

void TXTSerializer::ValidateDecisionState(const DecisionStateData& data)
{
    if (!(data.choice >= GameEnums::NO_CHOICE && data.choice <= GameEnums::SERIALIZATION))
        throw std::runtime_error("Nieprawidlowy wybor w pliku TXT!");
    if (!(data.previousChoice >= GameEnums::NO_CHOICE && data.previousChoice <= GameEnums::SERIALIZATION))
        throw std::runtime_error("Nieprawidlowy poprzedni wybor w pliku TXT!");
    if (!(data.currentMenu >= GameEnums::MAIN_MENU && data.currentMenu <= GameEnums::RESTART_MENU))
        throw std::runtime_error("Nieprawidlowe okno menu w pliku TXT!");
}

void TXTSerializer::ValidateItemState(const ItemStateData& data)
{
    if (!(data.damage == GameConfig::defaultDamage || data.damage == GameConfig::sawDamage))
        throw std::runtime_error("Nieprawidlowa wartosc obrazen w pliku TXT!");
    if (!(data.wereHandCuffsUsed == 0 || data.wereHandCuffsUsed == 1))
        throw std::runtime_error("Nieprawidlowa wartosc flagi kajdanek w pliku TXT!");
    if (!(data.wasMagnifierUsed == 0 || data.wasMagnifierUsed == 1))
        throw std::runtime_error("Nieprawidlowa wartosc flagi lupy w pliku TXT!");
    if (!(data.wasCellPhoneUsed == 0 || data.wasCellPhoneUsed == 1))
        throw std::runtime_error("Nieprawidlowa wartosc flagi telefonu w pliku TXT!");
}

void TXTSerializer::Serialize(const std::shared_ptr<IGameState> gs, const std::string& fileName)
{
    try
    {
        std::string saveDir;
        if (fileName.find("autosave") == 0)
            saveDir = SaveConfig::GetAutoSaveDirectory();
        else
            saveDir = SaveConfig::GetSaveDirectory();

        if (!SaveConfig::CreateDirectoryIfNotExists(saveDir))
            throw std::runtime_error("Nie mozna utworzyc katalogu zapisow!");

        std::string fullPath = saveDir + "/" + fileName + ".txt";
        std::ofstream gameSave(fullPath);
        if (!gameSave.is_open())
            throw std::runtime_error("Nie mozna otworzyc pliku! ");

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
        SerializePlayer(gameSave, humanData);

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
        SerializeComputer(gameSave, computerData);

        MagazineData magazineData;
        magazineData.bulletCount = gs->GetMagazine().GetMagazineSize();
        magazineData.magazine = gs->GetMagazine().GetMagazine();
        magazineData.hitProbability = gs->GetMagazine().GetHitProbability();
        SerializeMagazine(gameSave, magazineData);

        GameLoopStateData glsData;
        glsData.starter = gs->GetGameLoopState().GetStarter();
        glsData.isOnePlayerAlive = gs->GetGameLoopState().GetIsOnePlayerAlive();
        glsData.stateOfGameLoop = gs->GetGameLoopState().GetStateOfGameLoop();
        SerializeGameLoopState(gameSave, glsData);

        SerializationStateData ssData;
        ssData.serializationType = gs->GetSerializationState().GetSerializationType();
        SerializeSerializationState(gameSave, ssData);

        AIStateData aisData;
        aisData.difficulty = gs->GetAIState().GetDifficulty();
        aisData.recentDifficulty = gs->GetAIState().GetRecentDifficulty();
        SerializeAIState(gameSave, aisData);

        DecisionStateData dsData;
        dsData.choice = gs->GetDecisionState().GetChoice();
        dsData.previousChoice = gs->GetDecisionState().GetPreviousChoice();
        dsData.currentMenu = gs->GetDecisionState().GetCurrentMenu();
        SerializeDecisionState(gameSave, dsData);

        ItemStateData isData;
        isData.damage = gs->GetItemState().GetDamage();
        isData.wereHandCuffsUsed = gs->GetItemState().GetStateOfHandCuffs();
        isData.wasMagnifierUsed = gs->GetItemState().GetStateOfMagnifier();
        isData.wasCellPhoneUsed = gs->GetItemState().GetStateOfCellPhone();
        SerializeItemState(gameSave, isData);

        if (gameSave.fail())
            throw std::runtime_error("Blad podczas zapisu stanu gry!");
        gameSave.close();
    }
    catch (const std::exception& e)
    {
        serializationLog = e.what();
    }
}

void TXTSerializer::Deserialize(std::shared_ptr<IGameState> gs, const std::string& fileName)
{
    try
    {
        std::string saveDir;
        if (fileName.find("autosave") == 0)
            saveDir = SaveConfig::GetAutoSaveDirectory();
        else
            saveDir = SaveConfig::GetSaveDirectory();

        std::string fullPath = saveDir + "/" + fileName + ".txt";
        std::ifstream gameSave(fullPath);
        if (!gameSave.is_open())
            throw std::runtime_error("Nie mozna otworzyc pliku TXT podczas wczytywania!");

        PlayerData hd = DeserializePlayer(gameSave);
        PlayerData cd = DeserializeComputer(gameSave);
        MagazineData md = DeserializeMagazine(gameSave);
        GameLoopStateData glsData = DeserializeGameLoopState(gameSave);
        SerializationStateData ssData = DeserializeSerializationState(gameSave);
        AIStateData aisData = DeserializeAIState(gameSave);
        DecisionStateData dsData = DeserializeDecisionState(gameSave);
        ItemStateData isData = DeserializeItemState(gameSave);

        if (gameSave.fail())
            throw std::runtime_error("Blad odczytu stanu gry!");

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

        gameSave.close();
    }
    catch (const std::exception& e)
    {
        serializationLog = e.what();
    }
}
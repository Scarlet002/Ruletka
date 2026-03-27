#include "SaveJSONManager.h"
#include "SaveConfig.h"
#include "GameState.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstdint>
#include "json.hpp"

void SaveJSONManager::SaveGameState(const GameState& state,
    const std::string& fileName) const
{
    std::string saveDir;
    if (fileName.find("autosave") == 0)
    {
        saveDir = SaveConfig::GetAutoSaveDirectory();
    }
    else { saveDir = SaveConfig::GetSaveDirectory(); }

    if (!SaveConfig::CreateDirectoryIfNotExists(saveDir))
    {
        throw std::runtime_error("Nie mozna utworzyc katalogu zapisow!");
    }

    std::string fullPath = saveDir + "/" + fileName;
    nlohmann::json data;

    // Human data
    data["human_HP"] = state.human->GetHP();
    std::vector<uint8_t> humanInventory = state.human->GetInventory();
    for (uint8_t i : humanInventory)
    {
        data["human_inventory"].push_back(i);
    }
    data["human_Saws"] = state.human->GetSaws();
    data["human_Beers"] = state.human->GetBeers();
    data["human_Magnifiers"] = state.human->GetMagnifiers();
    data["human_Inverters"] = state.human->GetInverters();
    data["human_HandCuffs"] = state.human->GetHandCuffs();
    data["human_CellPhones"] = state.human->GetCellPhones();

    // Computer data
    data["computer_HP"] = state.computer->GetHP();
    std::vector<uint8_t> computerInventory = state.computer->GetInventory();
    for (uint8_t i : computerInventory)
    {
        data["computer_inventory"].push_back(i);
    }
    data["computer_Saws"] = state.computer->GetSaws();
    data["computer_Beers"] = state.computer->GetBeers();
    data["computer_Magnifiers"] = state.computer->GetMagnifiers();
    data["computer_Inverters"] = state.computer->GetInverters();
    data["computer_HandCuffs"] = state.computer->GetHandCuffs();
    data["computer_CellPhones"] = state.computer->GetCellPhones();

    // Magazine data
    data["magazine_full"] = state.magazine->ShowFull();
    data["magazine_empty"] = state.magazine->ShowEmpty();
    data["magazine_bullet_count"] = state.magazine->GetMagazineSize();
    std::vector<uint8_t> magazine = state.magazine->GetMagazine();
    for (uint8_t i : magazine)
    {
        data["magazine"].push_back(i);
    }

    // Turn data
    data["Starter"] = state.turn->GetStarter();
    data["difficulty"] = state.turn->GetDifficulty();
    data["choice"] = state.turn->GetChoice();
    data["shooter"] = state.turn->GetShooter();
    data["target"] = state.turn->GetTarget();
    data["item"] = state.turn->GetItem();
    data["damage"] = state.turn->GetDamage();
    data["WereHandCuffsUsed"] = state.turn->GetStateOfHandCuffs();
    data["WasInventoryShownForComputer"] = state.turn->GetStateOfInventory();
    data["WasMagnifierUsed"] = state.turn->GetStateOfMagnifier();
    data["WasCellPhoneUsed"] = state.turn->GetStateOfCellPhone();

    std::ofstream gameSave(fullPath);
    if (!gameSave.is_open())
    {
        throw std::runtime_error("Nie mozna otworzyc pliku!");
    }

    gameSave << data.dump(4);
    gameSave.close();
}
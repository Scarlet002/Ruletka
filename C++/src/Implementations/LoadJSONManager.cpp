#include "LoadJSONManager.h"
#include "SaveConfig.h"
#include "GameState.h"
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cstdint>
#include "json.hpp"

void LoadJSONManager::LoadGameState(GameState& state,
    const std::string& fileName)
{
    std::string saveDir = "";
    if (fileName.find("autosave") == 0)
        { saveDir = SaveConfig::GetAutoSaveDirectory(); }
    else { saveDir = SaveConfig::GetSaveDirectory(); }
    std::string fullPath = saveDir + "/" + fileName;
    std::ifstream gameSave(fullPath);
    if (!gameSave.is_open())
        { throw std::runtime_error("Nie mozna otworzyc pliku podczas wczytywania!"); }
    nlohmann::json data = nlohmann::json::parse(gameSave);

    state.turn->SetStarter(data["Starter"]);
    state.turn->SetDifficulty(data["difficulty"]);
    state.turn->SetChoice(data["choice"]);
    state.turn->SetShooter(data["shooter"]);
    state.turn->SetTarget(data["target"]);
    state.turn->SetItem(data["item"]);
    state.turn->SetDamage(data["damage"]);
    state.turn->SetStateOfHandCuffs(data["WereHandCuffsUsed"]);
    state.turn->SetStateOfMagnifier(data["WasMagnifierUsed"]);
    state.turn->SetStateOfCellPhone(data["WasCellPhoneUsed"]);

    state.human->SetHP(data["human_HP"]);
    state.human->SetInventory(data["human_inventory"]);
    state.human->SetSaws(data["human_Saws"]);
    state.human->SetBeers(data["human_Beers"]);
    state.human->SetMagnifiers(data["human_Magnifiers"]);
    state.human->SetInverters(data["human_Inverters"]);
    state.human->SetHandCuffs(data["human_HandCuffs"]);
    state.human->SetCellPhones(data["human_CellPhones"]);

    state.computer->SetHP(data["computer_HP"]);
    state.computer->SetInventory(data["computer_inventory"]);
    state.computer->SetSaws(data["computer_Saws"]);
    state.computer->SetBeers(data["computer_Beers"]);
    state.computer->SetMagnifiers(data["computer_Magnifiers"]);
    state.computer->SetInverters(data["computer_Inverters"]);
    state.computer->SetHandCuffs(data["computer_HandCuffs"]);
    state.computer->SetCellPhones(data["computer_CellPhones"]);

    state.magazine->SetMagazine(data["magazine"]);
    state.magazine->SetFull(data["magazine_full"]);
    state.magazine->SetEmpty(data["magazine_empty"]);
    state.magazine->SetBulletCount(data["magazine_bullet_count"]);
    state.magazine->CheckBullets();
}
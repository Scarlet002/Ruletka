#include "SaveTXTManager.h"
#include "SaveConfig.h"
#include "GameState.h"
#include <string>
#include <fstream>
#include <iostream>
#include <cstdint>

void SaveTXTManager::SaveGameState(const GameState& state,
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

    std::string fullPath = saveDir + "/" + fileName + ".txt";
    std::ofstream gameSave(fullPath);
    if (!gameSave.is_open())
    { 
        throw std::runtime_error("Nie mozna otworzyc pliku! ");
    }
    if (gameSave.fail())
    { 
        throw std::runtime_error("Blad podczas zapisu stanu gry!");
    }

    gameSave << state.human->GetHP() << '\n';
    std::vector<uint8_t> humanInventory = state.human->GetInventory();
    uint8_t humanInventorySize = humanInventory.size();
    gameSave << humanInventorySize << '\n';

    for (const uint8_t& item : humanInventory)
    { 
        gameSave << item << '\n';
    }

    gameSave << state.human->GetSaws() << '\n';
    gameSave << state.human->GetBeers() << '\n';
    gameSave << state.human->GetMagnifiers() << '\n';
    gameSave << state.human->GetInverters() << '\n';
    gameSave << state.human->GetHandCuffs() << '\n';
    gameSave << state.human->GetCellPhones() << '\n';

    gameSave << state.computer->GetHP() << '\n';
    std::vector<uint8_t> computerInventory = state.computer->GetInventory();
    uint8_t computerInventorySize = computerInventory.size();
    gameSave << computerInventorySize << '\n';

    for (const uint8_t& item : computerInventory)
    { 
        gameSave << item << '\n';
    }

    gameSave << state.computer->GetSaws() << '\n';
    gameSave << state.computer->GetBeers() << '\n';
    gameSave << state.computer->GetMagnifiers() << '\n';
    gameSave << state.computer->GetInverters() << '\n';
    gameSave << state.computer->GetHandCuffs() << '\n';
    gameSave << state.computer->GetCellPhones() << '\n';

    gameSave << state.magazine->GetMagazineSize() << '\n';

    std::vector<uint8_t> magazine = state.magazine->GetMagazine();
    for (const uint8_t& item : magazine)
    { 
        gameSave << item << '\n';
    }

    gameSave << state.turn->GetStarter() << '\n';
    gameSave << state.turn->GetDifficulty() << '\n';
    gameSave << state.turn->GetChoice() << '\n';
    gameSave << state.turn->GetShooter() << '\n';
    gameSave << state.turn->GetTarget() << '\n';
    gameSave << state.turn->GetItem() << '\n';
    gameSave << state.turn->GetDamage() << '\n';
    gameSave << state.turn->GetStateOfHandCuffs() << '\n';
    gameSave << state.turn->GetStateOfInventory() << '\n';
    gameSave << state.turn->GetStateOfMagnifier() << '\n';
    gameSave << state.turn->GetStateOfCellPhone() << '\n';

    gameSave.close();
}
#include "SaveJSONManager.h"
#include "GameState.h"
#include "SaveConfig.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "json.hpp"

using nlohmann::json;
using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::vector;
using std::exception;

void SaveJSONManager::SaveGameState(const GameState& gameState, const string& fileName) const
{
    try
    {
        string saveDir;

        if (fileName.find("autosave") == 0)
        {
            saveDir = SaveConfig::GetAutoSaveDirectory();
        }
        else
        {
            saveDir = SaveConfig::GetSaveDirectory();
        }

        if (!SaveConfig::CreateDirectoryIfNotExists(saveDir))
        {
            cout << "Nie mozna utworzyc katalogu zapisow!" << endl;
            return;
        }

        string fullPath = saveDir + "/" + fileName;

        json data;
        data["human_HP"] = gameState.human.GetHP();
        for (int i : gameState.human.GetInventory())
            data["human_inventory"].push_back(i);

        data["human_Saws"] = gameState.human.GetSaws();
        data["human_Beers"] = gameState.human.GetBeers();
        data["human_Magnifiers"] = gameState.human.GetMagnifiers();
        data["human_Inverters"] = gameState.human.GetInverters();
        data["human_HandCuffs"] = gameState.human.GetHandCuffs();
        data["human_CellPhones"] = gameState.human.GetCellPhones();

        data["computer_HP"] = gameState.computer.GetHP();
        for (int i : gameState.computer.GetInventory())
            data["computer_inventory"].push_back(i);

        data["computer_Saws"] = gameState.computer.GetSaws();
        data["computer_Beers"] = gameState.computer.GetBeers();
        data["computer_Magnifiers"] = gameState.computer.GetMagnifiers();
        data["computer_Inverters"] = gameState.computer.GetInverters();
        data["computer_HandCuffs"] = gameState.computer.GetHandCuffs();
        data["computer_CellPhones"] = gameState.computer.GetCellPhones();

        data["magazine_full"] = gameState.magazine.ShowFull();
        data["magazine_empty"] = gameState.magazine.ShowEmpty();
        data["magazine_bullet_count"] = gameState.magazine.ShowBulletCount();

        data["Starter"] = gameState.gameStateManager.GetStarter();
        data["difficulty"] = gameState.ai.GetDifficulty();
        data["choice"] = gameState.gameStateManager.GetChoice();
        data["shooter"] = gameState.gameStateManager.GetShooter();
        data["target"] = gameState.gameStateManager.GetTarget();
        data["item"] = gameState.gameStateManager.GetItem();
        data["damage"] = gameState.gameStateManager.GetDamage();
        data["WereHandCuffsUsed"] = gameState.gameStateManager.GetStateOfHandCuffs();

        for (int i : gameState.magazine.GetMagazine())
            data["magazine"].push_back(i);

        ofstream gameSave(fullPath);
        if (!gameSave.is_open())
        {
            cout << "Nie mozna otworzyc pliku!" << endl;
            return;
        }
        if (gameSave.fail())
        {
            cout << "Blad podczas zapisu stanu gry!" << endl;
            return;
        }

        gameSave << data.dump(4);
        gameSave.close();
    }
    catch (const json::exception& e)
    {
        cout << "Blad pliku JSON: " << e.what() << endl;
    }
    catch (const exception& e)
    {
        cout << "Blad zapisywania: " << e.what() << endl;
    }
}
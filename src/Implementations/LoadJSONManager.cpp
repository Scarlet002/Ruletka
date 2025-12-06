#include "LoadJSONManager.h"
#include "GameState.h"
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "json.hpp"

using nlohmann::json;
using std::ifstream;
using std::vector;
using std::endl;
using std::cout;
using std::exception;
using std::string;

void LoadJSONManager::LoadGameState(GameState& gameState, const string& fileName) const
{
    try
    {
        ifstream gameSave(fileName);
        if (!gameSave.is_open())
        {
            cout << "Nie mozna otworzyc pliku podczas wczytywania!" << endl;
            return;
        }
        json data = json::parse(gameSave);

        int hpHuman = data["human_HP"];
        int hpComputer = data["computer_HP"];
        int full = data["magazine_full"];
        int empty = data["magazine_empty"];
        int bulletCount = data["magazine_bullet_count"];
        int Starter = data["Starter"];
        int difficulty = data["difficulty"];
        int choice = data["choice"];
        int shooter = data["shooter"];
        int target = data["target"];
        int item = data["item"];
        int damage = data["damage"];
        bool wereHandCuffsUsed = data["WereHandCuffsUsed"];

        gameState.human.SetHP(hpHuman);
        gameState.computer.SetHP(hpComputer);
        gameState.magazine.SetFull(full);
        gameState.magazine.SetEmpty(empty);
        gameState.magazine.SetBulletCount(bulletCount);
        gameState.gameStateManager.SetStarter(Starter);
        gameState.ai.SetDifficulty(difficulty);
        gameState.gameStateManager.SetChoice(choice);
        gameState.gameStateManager.SetShooter(shooter);
        gameState.gameStateManager.SetTarget(target);
        gameState.gameStateManager.SetItem(item);
        gameState.gameStateManager.SetDamage(damage);
        gameState.gameStateManager.SetStateOfHandCuffs(wereHandCuffsUsed);

        vector<int> humanInventory;
        for (int i : data["human_inventory"]) 
        {
            humanInventory.push_back(i);
        }
        gameState.human.SetInventory(humanInventory);

        gameState.human.SetSaws(data["human_Saws"]);
        gameState.human.SetBeers(data["human_Beers"]);
        gameState.human.SetMagnifiers(data["human_Magnifiers"]);
        gameState.human.SetInverters(data["human_Inverters"]);
        gameState.human.SetHandCuffs(data["human_HandCuffs"]);
        gameState.human.SetCellPhones(data["human_CellPhones"]);

        vector<int> computerInventory;
        for (int i : data["computer_inventory"]) 
        {
            computerInventory.push_back(i);
        }
        gameState.computer.SetInventory(computerInventory);

        gameState.computer.SetSaws(data["computer_Saws"]);
        gameState.computer.SetBeers(data["computer_Beers"]);
        gameState.computer.SetMagnifiers(data["computer_Magnifiers"]);
        gameState.computer.SetInverters(data["computer_Inverters"]);
        gameState.computer.SetHandCuffs(data["computer_HandCuffs"]);
        gameState.computer.SetCellPhones(data["computer_CellPhones"]);

        vector<int> newMagazine;
        for (int i = 0; i < bulletCount; i++)
        {
            newMagazine.push_back(data["magazine"][i]);
        }
        gameState.magazine.SetMagazine(newMagazine);
    }
    catch (const json::exception& e)
    {
        cout << "Blad pliku JSON: " << e.what() << endl;
    }
    catch (const exception& e)
    {
        cout << "Blad wczytywania: " << e.what() << endl;
    }
}
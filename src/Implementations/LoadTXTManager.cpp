#include "LoadTXTManager.h"
#include "GameState.h"
#include "SaveConfig.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>

using std::ifstream;
using std::vector;
using std::endl;
using std::cout;
using std::string;
using std::exception;

void LoadTXTManager::LoadGameState(GameState& gameState, const string& fileName) const
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

        string fullPath = saveDir + "/" + fileName;

        ifstream gameSave(fullPath);
        if (!gameSave.is_open())
        {
            cout << "Nie mozna otworzyc pliku podczas wczytywania!" << endl;
            return;
        }

        int bullet, hpHuman, itemsHuman, sawsHuman, beersHuman, magnifiersHuman, invertersHuman, handCuffsHuman, cellPhonesHuman,
            hpComputer, itemsComputer, sawsComputer, beersComputer, magnifiersComputer, invertersComputer, handCuffsComputer, cellPhonesComputer,
            full, empty, bulletCount, starter, difficulty, choice, shooter, target, item, itemHuman, itemComputer, damage; 
        bool wereHandCuffsUsed;

        gameSave >> hpHuman >> itemsHuman;

        gameState.human.SetHP(hpHuman);
        vector<int> newHumanInventory;
        for (int i = 0; i < itemsHuman; i++)
        {
            gameSave >> itemHuman;
            newHumanInventory.push_back(itemHuman);
        }

        gameSave >> sawsHuman >> beersHuman >> magnifiersHuman >> invertersHuman >> handCuffsHuman >> cellPhonesHuman;

        gameState.human.SetInventory(newHumanInventory);
        gameState.human.SetSaws(sawsHuman);
        gameState.human.SetBeers(beersHuman);
        gameState.human.SetMagnifiers(magnifiersHuman);
        gameState.human.SetInverters(invertersHuman);
        gameState.human.SetHandCuffs(handCuffsHuman);
        gameState.human.SetCellPhones(cellPhonesHuman);

        gameSave >> hpComputer >> itemsComputer;

        gameState.computer.SetHP(hpComputer);
        vector<int> newComputerInventory;
        for (int i = 0; i < itemsComputer; i++)
        {
            gameSave >> itemComputer;
            newComputerInventory.push_back(itemComputer);
        }

        gameSave >> sawsComputer >> beersComputer >> magnifiersComputer >> invertersComputer >> handCuffsComputer >> cellPhonesComputer;

        gameState.computer.SetInventory(newComputerInventory);
        gameState.computer.SetSaws(sawsComputer);
        gameState.computer.SetBeers(beersComputer);
        gameState.computer.SetMagnifiers(magnifiersComputer);
        gameState.computer.SetInverters(invertersComputer);
        gameState.computer.SetHandCuffs(handCuffsComputer);
        gameState.computer.SetCellPhones(cellPhonesComputer);

        gameSave >> full >> empty >> bulletCount >> starter >> difficulty >> choice >> shooter >> target >> item >> damage >> wereHandCuffsUsed;

        gameState.magazine.SetFull(full);
        gameState.magazine.SetEmpty(empty);
        gameState.magazine.SetBulletCount(bulletCount);

        gameState.gameStateManager.SetStarter(starter);
        gameState.ai.SetDifficulty(difficulty);
        gameState.gameStateManager.SetChoice(choice);
        gameState.gameStateManager.SetShooter(shooter);
        gameState.gameStateManager.SetTarget(target);
        gameState.gameStateManager.SetItem(item);
        gameState.gameStateManager.SetDamage(damage);
        gameState.gameStateManager.SetStateOfHandCuffs(wereHandCuffsUsed);

        vector<int> newMagazine;
        for (int i = 0; i < bulletCount; i++)
        {
            gameSave >> bullet;
            newMagazine.push_back(bullet);
        }

        gameState.magazine.SetMagazine(newMagazine);

    }
    catch (const exception& e)
    {
        cout << "Blad wczytywania: " << e.what() << endl;
    }
}
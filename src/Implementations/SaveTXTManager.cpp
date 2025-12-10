#include "SaveTXTManager.h"
#include "GameState.h"
#include "SaveConfig.h"
#include <string>
#include <fstream>
#include <iostream>

using std::exception;
using std::cout;
using std::endl;
using std::ofstream;

void SaveTXTManager::SaveGameState(const GameState& gameState, const string& fileName) const
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

        ofstream gameSave(fullPath);
        if (!gameSave.is_open())
        {
            cout << "Nie mozna otworzyc pliku! " << endl;
            return;
        }
        if (gameSave.fail())
        {
            cout << "Blad podczas zapisu stanu gry!" << endl;
            return;
        }

        gameSave << gameState.human.GetHP() << endl;
        int itemsHuman = gameState.human.GetInventory().size();
        gameSave << itemsHuman << endl;
        for (int i : gameState.human.GetInventory())
        {
            gameSave << i << endl;
        }
        gameSave << gameState.human.GetSaws() << endl;
        gameSave << gameState.human.GetBeers() << endl;
        gameSave << gameState.human.GetMagnifiers() << endl;
        gameSave << gameState.human.GetInverters() << endl;
        gameSave << gameState.human.GetHandCuffs() << endl;
        gameSave << gameState.human.GetCellPhones() << endl;

        gameSave << gameState.computer.GetHP() << endl;
        int itemsComputer = gameState.computer.GetInventory().size();
        gameSave << itemsComputer << endl;
        for (int i : gameState.computer.GetInventory())
        {
            gameSave << i << endl;
        }
        gameSave << gameState.computer.GetSaws() << endl;
        gameSave << gameState.computer.GetBeers() << endl;
        gameSave << gameState.computer.GetMagnifiers() << endl;
        gameSave << gameState.computer.GetInverters() << endl;
        gameSave << gameState.computer.GetHandCuffs() << endl;
        gameSave << gameState.computer.GetCellPhones() << endl;

        gameSave << gameState.magazine.ShowFull() << endl;
        gameSave << gameState.magazine.ShowEmpty() << endl;
        gameSave << gameState.magazine.ShowBulletCount() << endl;

        gameSave << gameState.gameStateManager.GetStarter() << endl;
        gameSave << gameState.ai.GetDifficulty() << endl;
        gameSave << gameState.gameStateManager.GetChoice() << endl;
        gameSave << gameState.gameStateManager.GetShooter() << endl;
        gameSave << gameState.gameStateManager.GetTarget() << endl;
        gameSave << gameState.gameStateManager.GetItem() << endl;
        gameSave << gameState.gameStateManager.GetDamage() << endl;
        gameSave << gameState.gameStateManager.GetStateOfHandCuffs() << endl;

        for (int i : gameState.magazine.GetMagazine())
            gameSave << i << endl;

        gameSave.close();
    }

    catch (const exception& e)
    {
        cout << "Blad zapisywania: " << e.what() << endl;
    }
}
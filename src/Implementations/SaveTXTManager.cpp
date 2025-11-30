#include "SaveTXTManager.h"
#include "GameState.h"
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
        ofstream gameSave(fileName);
        if (!gameSave.is_open())
        {
            cout << "Nie mozna otworzyc pliku podczas zapisu!" << endl;
            return;
        }
        if (gameSave.fail())
        {
            cout << "Blad podczas zapisu stanu gry!" << endl;
            return;
        }
        gameSave << gameState.human.GetHP() << endl;
        gameSave << gameState.computer.GetHP() << endl;
        gameSave << gameState.magazine.ShowFull() << endl;
        gameSave << gameState.magazine.ShowEmpty() << endl;
        gameSave << gameState.magazine.ShowBulletCount() << endl;
        gameSave << gameState.gameStateManager.GetStarter() << endl;
        gameSave << gameState.ai.GetDifficulty() << endl;
        gameSave << gameState.gameStateManager.GetChoice() << endl;

        for (int i : gameState.magazine.GetMagazine())
            gameSave << i << endl;

        gameSave.close();
    }
    catch (const exception& e)
    {
        cout << "Blad zapisywania: " << e.what() << endl;
    }
}
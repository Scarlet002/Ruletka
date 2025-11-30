#include "LoadTXTManager.h"
#include "GameState.h"
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
        ifstream gameSave(fileName);
        if (!gameSave.is_open())
        {
            cout << "Nie mozna otworzyc pliku podczas wczytywania!" << endl;
            return;
        }

        int bullet, hpHuman, hpComputer, full, empty, bulletCount, Starter, difficulty, choice;
        gameSave >> hpHuman >> hpComputer >> full >> empty >> bulletCount >> Starter >> difficulty >> choice;

        gameState.human.SetHP(hpHuman);
        gameState.computer.SetHP(hpComputer);
        gameState.magazine.SetFull(full);
        gameState.magazine.SetEmpty(empty);
        gameState.magazine.SetBulletCount(bulletCount);
        gameState.gameStateManager.SetStarter(Starter);
        gameState.ai.SetDifficulty(difficulty);
        gameState.gameStateManager.SetChoice(choice);

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
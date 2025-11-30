#include "SaveJSONManager.h"
#include "GameState.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "json.hpp"

using nlohmann::json;
using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::exception;

void SaveJSONManager::SaveGameState(const GameState& gameState, const string& fileName) const
{
    try
    {
        json data;
        data["human_HP"] = gameState.human.GetHP();
        data["computer_HP"] = gameState.computer.GetHP();
        data["magazine_full"] = gameState.magazine.ShowFull();
        data["magazine_empty"] = gameState.magazine.ShowEmpty();
        data["magazine_bullet_count"] = gameState.magazine.ShowBulletCount();
        data["Starter"] = gameState.gameStateManager.GetStarter();
        data["difficulty"] = gameState.ai.GetDifficulty();
        data["choice"] = gameState.gameStateManager.GetChoice();
        for (int i : gameState.magazine.GetMagazine())
            data["magazine"].push_back(i);

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
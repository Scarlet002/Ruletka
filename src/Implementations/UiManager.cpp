#include "UiManager.h"
#include "GameState.h"
#include "InputValidatorManager.h"
#include "Player.h"
#include "GameEnums.h"
#include <string>
#include <iostream>
#include "json.hpp"

using nlohmann::json;
using std::cout;
using std::endl;
using std::string;

void UiManager::DisplayStats(const GameState& gameState) const
{
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Poziom trudnosci: ";
    ShowAIDifficulty(gameState.ai.GetDifficulty());
    cout << endl;
    cout << "Statystyki:" << endl;
    cout << "czlowiek HP: " << gameState.human.GetHP() << endl;
    cout << "komputer HP: " << gameState.computer.GetHP() << endl;
    cout << "Pelne pociski: " << gameState.magazine.ShowFull() << endl;
    cout << "Puste pociski: " << gameState.magazine.ShowEmpty() << endl;
    cout << "Liczba pociskow: " << gameState.magazine.ShowBulletCount() << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}

void UiManager::ScrollScreen() const { for (int i = 0; i < 30; i++) cout << endl; }

void UiManager::Menu() const
{
    cout << "Wybierz co chcesz zrobic:" << endl;
    cout << "0 - Sprobuj odzyskac 1 HP" << endl;
    cout << "1 - Strzel w komputera" << endl;
    cout << "5 - Zapisz gre" << endl;
    cout << "6 - Wczytaj gre" << endl;
    cout << "7 - Wybierz poziom trudnosci" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}

void UiManager::DifficultyMenu() const
{
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Wybierz poziom trudnosci:" << endl;
    cout << "0 - latwy" << endl;
    cout << "1 - normalny" << endl;
    cout << "2 - trudny" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}

void UiManager::ShowAIDifficulty(const int difficulty) const
{
    if (difficulty == GameEnums::EASY)
    {
        cout << "latwy";
    }
    else if (difficulty == GameEnums::NORMAL)
    {
        cout << "normalny";
    }
    else
    {
        cout << "trudny";
    }
}

void UiManager::InputSaveTXT(string& fileName)
{
    fileName = InputValidatorManager::GetValidatedInput("Podaj nazwe zapisu: ", InputValidatorManager::IsValidFileName);
    fileName += ".txt";
}

void UiManager::InputLoadTXT(string& fileName)
{
    fileName = InputValidatorManager::GetValidatedInput("Podaj nazwe zapisu do wczytania: ", InputValidatorManager::IsValidFileName);
    fileName += ".txt";
}

void UiManager::InputSaveJSON(string& fileName)
{
    fileName = InputValidatorManager::GetValidatedInput("Podaj nazwe zapisu: ", InputValidatorManager::IsValidFileName);
    fileName += ".json";
}

void UiManager::InputLoadJSON(string& fileName)
{
    fileName = InputValidatorManager::GetValidatedInput("Podaj nazwe zapisu do wczytania: ", InputValidatorManager::IsValidFileName);
    fileName += ".json";
}

void UiManager::InputdifficultyLevel(GameState& gameState)
{
    string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 2): ", InputValidatorManager::IsValidDifficultyChoice);
    gameState.ai.SetDifficulty(stoi(input));
}

bool UiManager::WantsToContinue(GameState& gameState)
{
    string ans = InputValidatorManager::GetValidatedInput("Czy chcesz kontynuowac gre? (t/n): ", InputValidatorManager::IsValidYesNo);
    if (ans == "t" || ans == "T")
    {
        gameState.human.ResetHP();
        gameState.computer.ResetHP();
        gameState.magazine.Reload();
        ScrollScreen();
        return true;
    }
    else
    {
        ScrollScreen();
        ThankYou();
        return false;
    }
}

void UiManager::ComputerChoosing() const { cout << "Wybiera komputer!" << endl; }
void UiManager::ComputerStarts() const { cout << "Zaczyna komputer!" << endl; }
void UiManager::HumanStarts() const { cout << "Zaczynasz ty!" << endl; }
void UiManager::ShowPointer() const { cout << "										*" << endl; }
void UiManager::NewLine() const { cout << endl; }
void UiManager::AutoSaveDone() const { cout << "Zapis automatyczny zakonczony: "; }
void UiManager::ShowAutoSaveName(string& autoSaveFileName) const { cout << autoSaveFileName; }
void UiManager::SavingSucces() const { cout << "Pomyslnie zapisano stan gry!" << endl; }
void UiManager::LoadingSucces() const { cout << "Pomyslnie wczytano stan gry!" << endl; }
void UiManager::DifficultyChangeSucces() const { cout << "Pomyslnie zmieniono poziom trudnosci!" << endl; }
void UiManager::InvalidInput() const { cout << "Nieprawidlowy wybor. Straciles ture!" << endl; }
void UiManager::ComputerWin() const { cout << "Komputer wygrywa gre!" << endl; }
void UiManager::HumanWin() const { cout << "Wygrywasz gre!" << endl; }
void UiManager::EndOfBullets() const { cout << "Koniec pociskow! Przeladowanie!" << endl; }
void UiManager::ThankYou() const { cout << "Dziekuje za gre! Do zobaczenia!" << endl; }
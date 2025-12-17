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
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Poziom trudnosci: ";
    ShowAIDifficulty(gameState.ai.GetDifficulty());
    cout << endl << endl;
    cout << "Statystyki:" << endl;
    cout << endl;
    cout << "czlowiek HP: " << gameState.human.GetHP() << endl;
    cout << "czlowiek Pily: " << gameState.human.GetSaws() << endl;
    cout << "czlowiek Piwa: " << gameState.human.GetBeers() << endl;
    cout << "czlowiek Lupy: " << gameState.human.GetMagnifiers() << endl;
    cout << "czlowiek Telefony: " << gameState.human.GetCellPhones() << endl;
    cout << "czlowiek Kajdanki: " << gameState.human.GetHandCuffs() << endl;
    cout << "czlowiek Inwertery: " << gameState.human.GetInverters() << endl;
    cout << endl;
    cout << "komputer HP: " << gameState.computer.GetHP() << endl;
    cout << "komputer Pily: " << gameState.computer.GetSaws() << endl;
    cout << "komputer Piwa: " << gameState.computer.GetBeers() << endl;
    cout << "komputer Lupy: " << gameState.computer.GetMagnifiers() << endl;
    cout << "komputer Telefony: " << gameState.computer.GetCellPhones() << endl;
    cout << "komputer Kajdanki: " << gameState.computer.GetHandCuffs() << endl;
    cout << "komputer Inwertery: " << gameState.computer.GetInverters() << endl;
    cout << endl;
    cout << "Pelne pociski: " << gameState.magazine.ShowFull() << endl;
    cout << "Puste pociski: " << gameState.magazine.ShowEmpty() << endl;
    cout << "Liczba pociskow: " << gameState.magazine.ShowBulletCount() << endl;
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
}

void UiManager::ScrollScreen() const { for (int i = 0; i < 30; i++) cout << endl; }

void UiManager::Menu() const
{
    cout << "Wybierz co chcesz zrobic:" << endl;
    cout << "0 - Sprobuj odzyskac 1 HP" << endl;
    cout << "1 - Strzel w komputer" << endl;
    cout << "2 - Uzyj przedmiotu" << endl;
    cout << "3 - Zakoncz gre" << endl;
    cout << "4 - Zapisz gre" << endl;
    cout << "5 - Wczytaj gre" << endl;
    cout << "6 - Wybierz poziom trudnosci" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
}

void UiManager::DifficultyMenu() const
{
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Wybierz poziom trudnosci:" << endl;
    cout << "0 - latwy" << endl;
    cout << "1 - normalny" << endl;
    cout << "2 - trudny" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
}

void UiManager::InventoryMenu() const
{
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
    cout << "Wybierz przedmiot ktory chcesz uzyc:" << endl;
    cout << "0 - Nie uzywaj zadnego przedmiotu" << endl;
    cout << "1 - Kajdanki" << endl;
    cout << "2 - Piwo" << endl;
    cout << "3 - Lupa" << endl;
    cout << "4 - Pila" << endl;
    cout << "5 - Telefon" << endl;
    cout << "6 - Inwerter" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
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

void UiManager::ItemUseSuccesHuman(GameState& gameState) const
{
    if (gameState.gameStateManager.GetItem() == GameEnums::NOITEMS)
    {
        cout << "Nie uzyles zadnego przedmiotu!";
    }
    else if (gameState.gameStateManager.GetItem() == GameEnums::CELLPHONE && gameState.human.GetCellPhones() > 0)
    {
        gameState.human.UseCellPhone(gameState);
        cout << "Pomyslnie uzyles telefonu!";
    }
    else if (gameState.gameStateManager.GetItem() == GameEnums::SAW && gameState.human.GetSaws() > 0)
    {
        gameState.human.UseSaw(gameState);
        cout << "Pomyslnie uzyles pily!";
    }
    else if (gameState.gameStateManager.GetItem() == GameEnums::BEER && gameState.human.GetBeers() > 0)
    {
        gameState.human.UseBeer(gameState);
        cout << "Pomyslnie wypiles piwo!";
    }
    else if (gameState.gameStateManager.GetItem() == GameEnums::MAGNIFIER && gameState.human.GetMagnifiers() > 0)
    {
        gameState.human.UseMagnifier(gameState);
        cout << "Pomyslnie uzyles lupy!";
    }
    else if (gameState.gameStateManager.GetItem() == GameEnums::HANDCUFFS && gameState.human.GetHandCuffs() > 0)
    {
        gameState.human.UseHandCuffs(gameState);
        cout << "Pomyslnie uzyles kajdanek!";
    }
    else if (gameState.gameStateManager.GetItem() == GameEnums::INVERTER && gameState.human.GetInverters() > 0)
    {
        gameState.human.UseInverter(gameState);
        cout << "Pomyslnie uzyles inwertera!";
    }
    else
    {
        cout << "Nie masz tego przedmiotu!";
    }
}

void UiManager::ItemUseSuccesComputer(GameState& gameState) const
{
    if (gameState.gameStateManager.GetItem() == GameEnums::NOITEMS)
    {
        cout << "Komputer nie uzyl zadnego przedmiotu!" << endl;
    }
    else if (gameState.gameStateManager.GetItem() == GameEnums::CELLPHONE && gameState.computer.GetCellPhones() > 0)
    {
        gameState.computer.UseCellPhone(gameState);
        cout << "Komputer pomyslnie uzyl telefonu!" << endl;
    }
    else if (gameState.gameStateManager.GetItem() == GameEnums::SAW && gameState.computer.GetSaws() > 0)
    {
        gameState.computer.UseSaw(gameState);
        cout << "Komputer pomyslnie uzyl pily!" << endl;
    }
    else if (gameState.gameStateManager.GetItem() == GameEnums::BEER && gameState.computer.GetBeers() > 0)
    {
        gameState.computer.UseBeer(gameState);
        cout << "Komputer pomyslnie uzyl piwo!" << endl;
    }
    else if (gameState.gameStateManager.GetItem() == GameEnums::MAGNIFIER && gameState.computer.GetMagnifiers() > 0)
    {
        gameState.computer.UseMagnifier(gameState);
        cout << "Komputer pomyslnie uzyl lupy!" << endl;
    }
    else if (gameState.gameStateManager.GetItem() == GameEnums::HANDCUFFS && gameState.computer.GetHandCuffs() > 0)
    {
        gameState.computer.UseHandCuffs(gameState);
        cout << "Komputer pomyslnie uzyl kajdanek!" << endl;
    }
    else if (gameState.gameStateManager.GetItem() == GameEnums::INVERTER && gameState.computer.GetInverters() > 0)
    {
        gameState.computer.UseInverter(gameState);
        cout << "Komputer pomyslnie uzyl inwertera!" << endl;
    }
    else
    {
        cout << "Komputer nie ma tego przedmiotu!" << endl;
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

void UiManager::InputItemChoice(GameState& gameState)
{
    string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 6): ", InputValidatorManager::IsValidItemChoice);
    gameState.gameStateManager.SetItem(stoi(input));
}

bool UiManager::WantsToContinue(GameState& gameState)
{
    string ans = InputValidatorManager::GetValidatedInput("Czy chcesz kontynuowac gre? (t/n): ", InputValidatorManager::IsValidYesNo);
    if (ans == "t" || ans == "T")
    {
        gameState.human.ResetHP();
        gameState.computer.ResetHP();
        gameState.magazine.Reload();
        gameState.human.ResetInventory(gameState);
        gameState.human.GetNumberOfItems(gameState);
        gameState.computer.ResetInventory(gameState);
        gameState.computer.GetNumberOfItems(gameState);
        Clear();
        DisplayStats(gameState);
        return true;
    }
    else
    {
        Clear();
        ThankYou();
        return false;
    }
}

void UiManager::ComputerChoosing() const { cout << "Wybiera komputer!" << endl; }
void UiManager::ComputerStarts() const { cout << "Zaczyna komputer!" << endl; }
void UiManager::HumanStarts() const { cout << "Zaczynasz ty!" << endl; }
void UiManager::ShowPointer() const { cout << "								*" << endl; }
void UiManager::NewLine() const { cout << endl; }
void UiManager::AutoSaveDone() const { cout << "Zapis automatyczny zakonczony: "; }
void UiManager::ShowAutoSaveName(string& autoSaveFileName) const 
{ 
    cout << autoSaveFileName << endl;
    cout << "-------------------------------------------------------------------------------------------------------------" << endl;
}
void UiManager::SavingSucces() const { cout << "Pomyslnie zapisano stan gry!"; }
void UiManager::LoadingSucces() const { cout << "Pomyslnie wczytano stan gry!"; }
void UiManager::DifficultyChangeSucces() const { cout << "Pomyslnie zmieniono poziom trudnosci!"; }
void UiManager::InvalidInput() const { cout << "Nieprawidlowy wybor." << endl; }
void UiManager::ComputerWin() const { cout << "Komputer wygrywa gre!" << endl; }
void UiManager::HumanWin() const { cout << "Wygrywasz gre!" << endl; }
void UiManager::EndOfBullets() const { cout << "Koniec pociskow! Przeladowanie!" << endl; }
void UiManager::ThankYou() const { cout << "Dziekuje za gre! Do zobaczenia!" << endl; }
void UiManager::Clear() const 
{
#ifdef _WIN32
    system("cls");
#endif 
}
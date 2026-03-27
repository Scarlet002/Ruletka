#include "InputValidatorManager.h"
#include "UiManager.h"
#include "GameState.h"
#include "Player.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "json.hpp"
#include <string>
#include <vector>
#include <cstdint>
#include <iostream>

UiManager::UiManager(const GameState& state) 
    : state(state) 
    { log.reserve(GameConfig::maxLogsInLine); }

void UiManager::DisplayLastTurnLog()
{
    if (log.size() != 0)
    {
        for (uint8_t i = 0; i < log.size(); ++i)
        {
            if (i != 0)
            {
                if (i % GameConfig::maxLogsInLine == 0) { std::cout << '\n'; }
                std::cout << " -> ";
            }
            std::cout << log[i];
        }
    }
    log.clear();
    NewLine();
}
int UiManager::HumanDecision()
{
    std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 6): ",
        InputValidatorManager::IsValidMenuChoice);
    uint8_t choice = stoi(input);
	return choice;
}
void UiManager::DisplayStats() const
{
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
    std::cout << "Poziom trudnosci: ";
    std::cout << GetAIDifficulty(state.turn->GetDifficulty());
    std::cout << '\n' << '\n';
    std::cout << "Statystyki:" << '\n';
    std::cout << '\n';
    std::cout << "czlowiek HP: " << state.human->GetHP() << '\n';
    std::cout << "czlowiek Pily: " << state.human->GetSaws() << '\n';
    std::cout << "czlowiek Piwa: " << state.human->GetBeers() << '\n';
    std::cout << "czlowiek Lupy: " << state.human->GetMagnifiers() << '\n';
    std::cout << "czlowiek Telefony: " << state.human->GetCellPhones() << '\n';
    std::cout << "czlowiek Kajdanki: " << state.human->GetHandCuffs() << '\n';
    std::cout << "czlowiek Inwertery: " << state.human->GetInverters() << '\n';
    std::cout << '\n';
    std::cout << "komputer HP: " << state.computer->GetHP() << '\n';
    std::cout << "komputer Pily: " << state.computer->GetSaws() << '\n';
    std::cout << "komputer Piwa: " << state.computer->GetBeers() << '\n';
    std::cout << "komputer Lupy: " << state.computer->GetMagnifiers() << '\n';
    std::cout << "komputer Telefony: " << state.computer->GetCellPhones() << '\n';
    std::cout << "komputer Kajdanki: " << state.computer->GetHandCuffs() << '\n';
    std::cout << "komputer Inwertery: " << state.computer->GetInverters() << '\n';
    std::cout << '\n';
    std::cout << "Pelne pociski: " << state.magazine->ShowFull() << '\n';
    std::cout << "Puste pociski: " << state.magazine->ShowEmpty() << '\n';
    std::cout << "Liczba pociskow: " << state.magazine->ShowBulletCount() << '\n';
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
}
void UiManager::Menu() const
{
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
    std::cout << "Wybierz co chcesz zrobic:" << '\n';
    std::cout << "0 - Sprobuj odzyskac 1 HP" << '\n';
    std::cout << "1 - Strzel w komputer" << '\n';
    std::cout << "2 - Uzyj przedmiotu" << '\n';
    std::cout << "3 - Zakoncz gre" << '\n';
    std::cout << "4 - Zapisz gre" << '\n';
    std::cout << "5 - Wczytaj gre" << '\n';
    std::cout << "6 - Wybierz poziom trudnosci" << '\n';
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
}
void UiManager::DifficultyMenu() const
{
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
    std::cout << "Wybierz poziom trudnosci:" << '\n';
    std::cout << "0 - latwy" << '\n';
    std::cout << "1 - normalny" << '\n';
    std::cout << "2 - trudny" << '\n';
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
}
void UiManager::InventoryMenu() const
{
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
    std::cout << "Wybierz przedmiot ktory chcesz uzyc:" << '\n';
    std::cout << "0 - Nie uzywaj zadnego przedmiotu" << '\n';
    std::cout << "1 - Kajdanki" << '\n';
    std::cout << "2 - Piwo" << '\n';
    std::cout << "3 - Lupa" << '\n';
    std::cout << "4 - Pila" << '\n';
    std::cout << "5 - Telefon" << '\n';
    std::cout << "6 - Inwerter" << '\n';
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
}
std::string UiManager::GetAIDifficulty(const int difficulty) const
{
    if (difficulty == GameEnums::EASY) { return "latwy"; }
    else if (difficulty == GameEnums::NORMAL) { return "normalny"; }
    else { return "trudny"; }
}
void UiManager::InputSaveTXT()
{
    fileName = InputValidatorManager::GetValidatedInput("Podaj nazwe zapisu: ",
        InputValidatorManager::IsValidFileName);
    fileName += ".txt";
}
void UiManager::InputLoadTXT()
{
    fileName = InputValidatorManager::GetValidatedInput("Podaj nazwe zapisu do wczytania: ",
        InputValidatorManager::IsValidFileName);
    fileName += ".txt";
}
void UiManager::InputSaveJSON()
{
    fileName = InputValidatorManager::GetValidatedInput("Podaj nazwe zapisu: ",
        InputValidatorManager::IsValidFileName);
    fileName += ".json";
}
void UiManager::InputLoadJSON()
{
    fileName = InputValidatorManager::GetValidatedInput("Podaj nazwe zapisu do wczytania: ",
        InputValidatorManager::IsValidFileName);
    fileName += ".json";
}
int UiManager::InputdifficultyLevel()
{
    std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 2): ",
        InputValidatorManager::IsValidDifficultyChoice);
    uint8_t choice = (stoi(input));
	return choice;
}
int UiManager::InputItemChoice()
{
    std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 6): ",
        InputValidatorManager::IsValidItemChoice);
    uint8_t choice = (stoi(input));
    return choice;
}
bool UiManager::WantsToContinue()
{
    std::string input = InputValidatorManager::GetValidatedInput("Czy chcesz kontynuowac gre? (t/n): ",
        InputValidatorManager::IsValidYesNo);
    if (input == "t" || input == "T") { return true; }
    else { return false; }
}
void UiManager::Clear() const
{
#ifdef _WIN32
    system("cls");
#endif 
}
std::string UiManager::GetFileName() const { return fileName; }
void UiManager::SetFileName(std::string newFileName) { fileName = newFileName; }
void UiManager::ClearLog() { log.clear(); }
void UiManager::SetLog(const std::vector<std::string>& newLog) { log = newLog; }
const std::vector<std::string>& UiManager::GetLog() const { return log; }
std::string UiManager::GetRecentLogLine() const { return log.back(); }
void UiManager::SetRecentLogLine(std::string newLogLine) { log.push_back(newLogLine); }
void UiManager::ShowPointer() const { std::cout << "								*" << '\n'; }
void UiManager::ComputerChoosing() const { std::cout << "Wybiera komputer!" << '\n'; }
void UiManager::ComputerStarts() const { std::cout << "Zaczyna komputer!" << '\n'; }
void UiManager::HumanStarts() const { std::cout << "Zaczynasz ty!" << '\n'; }
void UiManager::NewLine() const { std::cout << '\n'; }
void UiManager::AutoSaveDone() const { std::cout << "Zapis automatyczny zakonczony: "; }
std::string UiManager::GetAutoSaveName() const { return autoSaveFileName; }
void UiManager::SavingSucces() const { std::cout << "Pomyslnie zapisano stan gry!"; }
void UiManager::LoadingSucces() const { std::cout << "Pomyslnie wczytano stan gry!"; }
void UiManager::DifficultyChangeSucces() const { std::cout << "Pomyslnie zmieniono poziom trudnosci!"; }
void UiManager::InvalidInput() const { std::cout << "Nieprawidlowy wybor!" << '\n'; }
void UiManager::ComputerWin() const { std::cout << "Komputer wygrywa gre!" << '\n'; }
void UiManager::HumanWin() const { std::cout << "Wygrywasz gre!" << '\n'; }
void UiManager::EndOfBullets() const { std::cout << "Koniec pociskow! Przeladowanie!" << '\n'; }
void UiManager::ThankYou() const { std::cout << "Dziekuje za gre! Do zobaczenia!" << '\n'; }
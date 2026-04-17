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
#include <windows.h>

UiManager::UiManager(const GameState& state) 
    : state(state) 
{ 
    log.reserve(GameConfig::maxLogsInLine);
	recentLog.reserve(GameConfig::maxLogsInLine);
}

void UiManager::ResetUI()
{
    Clear();
    ClearLog();
}

bool UiManager::Initialize()
{
    return true;
}

void UiManager::Render()
{
    Clear();
    DisplayStats();
    DisplayLastTurnLog();
    if (state.turn->GetCurrentMenu() == GameEnums::MAIN_MENU)
    {
        Menu();
    }
    else if (state.turn->GetCurrentMenu() == GameEnums::DIFFICULTY_MENU)
    {
        DifficultyMenu();
    }
    else  if (state.turn->GetCurrentMenu() == GameEnums::INVENTORY_MENU)
    {
        InventoryMenu();
    }
	else if (state.turn->GetCurrentMenu() == GameEnums::RESTART_MENU)
    {
        RestartMenu();
    }
}

void UiManager::DisplayLastTurnLog()
{
    if (!GetLog().empty())
    {
        SetRecentLog(GetLog());
        if (state.turn->GetStarter() == GameEnums::HUMAN)
        {
            ClearLog();
        }
    }

    for (const auto& line : GetRecentLog())
    {
        std::cout << line << '\n';
    }
}
 
int8_t UiManager::Decision()
{
    if (state.turn->GetCurrentMenu() == GameEnums::SAVE_MENU
        || state.turn->GetCurrentMenu() == GameEnums::LOAD_MENU)
    {
        std::string input = InputValidatorManager::GetValidatedInput("Podaj nazwe pliku: ",
            InputValidatorManager::IsValidFileName);
        fileName = input;
		return state.turn->GetCurrentMenu() == GameEnums::SAVE_MENU ? GameEnums::SAVE : GameEnums::LOAD;
    }
    else
    {
        std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 6): ",
            InputValidatorManager::IsValidMenuChoice);
        int8_t choice = static_cast<int8_t>(stoi(input));
        return choice;
    }
}
 
void UiManager::DisplayStats() const
{
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
    std::cout << "Poziom trudnosci: ";
    std::cout << GetAIDifficulty(state.turn->GetDifficulty());
    std::cout << '\n' << '\n';
    std::cout << "Statystyki:" << '\n';
    std::cout << '\n';
    std::cout << "czlowiek HP: " << std::to_string(state.human->GetHP()) << '\n';
    std::cout << "czlowiek Pily: " << std::to_string(state.human->GetSaws()) << '\n';
    std::cout << "czlowiek Piwa: " << std::to_string(state.human->GetBeers()) << '\n';
    std::cout << "czlowiek Lupy: " << std::to_string(state.human->GetMagnifiers()) << '\n';
    std::cout << "czlowiek Telefony: " << std::to_string(state.human->GetCellPhones()) << '\n';
    std::cout << "czlowiek Kajdanki: " << std::to_string(state.human->GetHandCuffs()) << '\n';
    std::cout << "czlowiek Inwertery: " << std::to_string(state.human->GetInverters()) << '\n';
    std::cout << '\n';
    std::cout << "komputer HP: " << std::to_string(state.computer->GetHP()) << '\n';
    std::cout << "komputer Pily: " << std::to_string(state.computer->GetSaws()) << '\n';
    std::cout << "komputer Piwa: " << std::to_string(state.computer->GetBeers()) << '\n';
    std::cout << "komputer Lupy: " << std::to_string(state.computer->GetMagnifiers()) << '\n';
    std::cout << "komputer Telefony: " << std::to_string(state.computer->GetCellPhones()) << '\n';
    std::cout << "komputer Kajdanki: " << std::to_string(state.computer->GetHandCuffs()) << '\n';
    std::cout << "komputer Inwertery: " << std::to_string(state.computer->GetInverters()) << '\n';
    std::cout << '\n';
    std::cout << "Pelne pociski: " << std::to_string(state.magazine->GetFull()) << '\n';
    std::cout << "Puste pociski: " << std::to_string(state.magazine->GetEmpty()) << '\n';
    std::cout << "Liczba pociskow: " << std::to_string(state.magazine->GetMagazineSize()) << '\n';
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
    std::cout << "0 - Normalny" << '\n';
    std::cout << "1 - Latwy" << '\n';
    std::cout << "2 - Trudny" << '\n';
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
}

void UiManager::RestartMenu() const
{
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
    std::cout << "Wybierz czy chcesz zagrac ponownie:" << '\n';
    std::cout << "0 - Nie" << '\n';
    std::cout << "1 - Tak" << '\n';
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
 
std::string UiManager::GetAIDifficulty(const int8_t difficulty) const
{
    if (difficulty == GameEnums::EASY) { return "latwy"; }
    else if (difficulty == GameEnums::NORMAL) { return "normalny"; }
    else { return "trudny"; }
}
 
std::string UiManager::GetFilename() const { return fileName; }
 
int8_t UiManager::InputDifficultyLevel()
{
    std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 2): ",
        InputValidatorManager::IsValidDifficultyChoice);
    uint8_t choice = stoi(input);
	return choice;
}
 
int8_t UiManager::InputItemChoice()
{
    std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 6): ",
        InputValidatorManager::IsValidItemChoice);
    uint8_t choice = stoi(input);
    return choice;
}
 
int8_t UiManager::HandleGameOverInput()
{
    std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor(0 - 1): ",
        InputValidatorManager::IsValidYesNo);
    uint8_t choice = stoi(input);
    return choice;
}
 
void UiManager::Clear() const
{
    #ifdef _WIN32
        system("cls");
    #endif
}
 
bool UiManager::GetUIType() const { return true; }

void UiManager::ClearLog() { log.clear(); }
 
void UiManager::SetLog(const std::vector<std::string>& newLog) { log = newLog; }
 
const std::vector<std::string>& UiManager::GetLog() const { return log; }
 
std::string UiManager::GetRecentLogLine() const { return log.back(); }
 
void UiManager::SetRecentLogLine(std::string newLogLine) { log.push_back(newLogLine); }

void UiManager::SetRecentLog(const std::vector<std::string>& newRecentLog) { recentLog = newRecentLog; }

const std::vector<std::string>& UiManager::GetRecentLog() const { return recentLog; }
 
void UiManager::ShowPointer() const { std::cout << "								*" << '\n'; }
 
void UiManager::ComputerChoosing() const { std::cout << "Wybiera komputer!" << '\n'; }
 
void UiManager::ComputerStarts() const { std::cout << "Zaczyna komputer!" << '\n'; }
 
void UiManager::HumanStarts() const { std::cout << "Zaczynasz ty!" << '\n'; }
 
void UiManager::NewLine() const { std::cout << '\n'; }
 
void UiManager::AutoSaveDone() const { std::cout << "Zapis automatyczny zakonczony: "; }
 
void UiManager::SavingSucces() const { std::cout << "Pomyslnie zapisano stan gry!"; }
 
void UiManager::LoadingSucces() const { std::cout << "Pomyslnie wczytano stan gry!"; }
 
void UiManager::DifficultyChangeSucces() const { std::cout << "Pomyslnie zmieniono poziom trudnosci!"; }
 
void UiManager::InvalidInput() const { std::cout << "Nieprawidlowy wybor!" << '\n'; }
 
void UiManager::ComputerWin() const { std::cout << "Komputer wygrywa gre!" << '\n'; }
 
void UiManager::HumanWin() const { std::cout << "Wygrywasz gre!" << '\n'; }
 
void UiManager::EndOfBullets() const { std::cout << "Koniec pociskow! Przeladowanie!" << '\n'; }
 
void UiManager::ThankYou() const { std::cout << "Dziekuje za gre! Do zobaczenia!" << '\n'; }
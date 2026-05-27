#include "InputValidatorManager.h"
#include "ConsoleUI.h"
#include "IGameState.h"
#include "LogObserver.h"
#include "Player.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "IPlayer.h"
#include "DecisionState.h"
#include "Magazine.h"
#include "AIState.h"
#include "SerializationState.h"
#include "json.hpp"
#include <string>
#include <deque>
#include <cstdint>
#include <iostream>

ConsoleUI::ConsoleUI(const std::shared_ptr<IGameState> gs)
    : gs(gs) 
    , log() {}

void ConsoleUI::ResetUI()
{
    Clear();
    ClearLog();
}

void ConsoleUI::Render()
{
    Clear();
    DisplayStats();
    DisplayLastTurnLog();
    if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::MAIN_MENU)
    {
        Menu();
    }
    else if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::DIFFICULTY_MENU)
    {
        DifficultyMenu();
    }
    else  if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::INVENTORY_MENU)
    {
        InventoryMenu();
    }
    else if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::SERIALIZATION_MENU)
    {
        SerializationMenu();
    }
	else if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::RESTART_MENU)
    {
        RestartMenu();
    }
}

void ConsoleUI::DisplayLastTurnLog()
{   
    if (log.size() >= GameConfig::maxLogsRendered)
    {
        log.pop_front();
    }

    for (const auto& line : log)
    {
        std::cout << line << '\n';
    }
}
 
int8_t ConsoleUI::Decision() noexcept
{
    if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::SAVE_MENU
        || gs->GetDecisionState().GetCurrentMenu() == GameEnums::LOAD_MENU)
    {
        std::string input = InputValidatorManager::GetValidatedInput("Podaj nazwe pliku: ",
            InputValidatorManager::IsValidFileName);
        fileName = input;
		return gs->GetDecisionState().GetCurrentMenu() == GameEnums::SAVE_MENU ? GameEnums::SAVE : GameEnums::LOAD;
    }
    else if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::DIFFICULTY_MENU)
    {
        int8_t choice = InputDifficultyLevel();
        return choice;
    }
    else if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::INVENTORY_MENU)
    {
        int8_t choice = InputItemChoice();
        return choice;
	}
    else if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::RESTART_MENU)
    {
        int8_t choice = InputRestartChoice();
        return choice;
	}
    else if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::SERIALIZATION_MENU)
    {
        int8_t choice = InputSerializationType();
        return choice;
    }
    else
    {
        std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 6): ",
            InputValidatorManager::IsValidMenuChoice);
        int8_t choice = static_cast<int8_t>(stoi(input));
        return choice;
    }
}
 
void ConsoleUI::DisplayStats() const
{
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
    std::cout << "Poziom trudnosci: ";
    std::cout << GetAIDifficulty(gs->GetAIState().GetDifficulty()) << '\n';
    std::cout << "Format serializacji: ";
    std::cout << GetSerializationType(gs->GetSerializationState().GetSerializationType());
    std::cout << '\n' << '\n';
    std::cout << "Statystyki:" << '\n';
    std::cout << '\n';
    std::cout << gs->GetHuman().GetName() + " HP: " + std::to_string(gs->GetHumanHP().GetHP()) << '\n';
    std::cout << gs->GetHuman().GetName() + " Pily: " + std::to_string(gs->GetHumanInventory().GetItemCount(GameEnums::SAW)) << '\n';
    std::cout << gs->GetHuman().GetName() + " Piwa: " + std::to_string(gs->GetHumanInventory().GetItemCount(GameEnums::BEER)) << '\n';
    std::cout << gs->GetHuman().GetName() + " Lupy: " + std::to_string(gs->GetHumanInventory().GetItemCount(GameEnums::MAGNIFIER)) << '\n';
    std::cout << gs->GetHuman().GetName() + " Telefony: " + std::to_string(gs->GetHumanInventory().GetItemCount(GameEnums::CELLPHONE)) << '\n';
    std::cout << gs->GetHuman().GetName() + " Kajdanki: " + std::to_string(gs->GetHumanInventory().GetItemCount(GameEnums::HANDCUFFS)) << '\n';
    std::cout << gs->GetHuman().GetName() + " Inwertery: " + std::to_string(gs->GetHumanInventory().GetItemCount(GameEnums::INVERTER)) << '\n';
    std::cout << '\n';
    std::cout <<  gs->GetComputer().GetName() << " HP: " << std::to_string(gs->GetComputerHP().GetHP()) << '\n';
    std::cout << gs->GetComputer().GetName() + " Pily: " + std::to_string(gs->GetComputerInventory().GetItemCount(GameEnums::SAW)) << '\n';
    std::cout << gs->GetComputer().GetName() + " Piwa: " + std::to_string(gs->GetComputerInventory().GetItemCount(GameEnums::BEER)) << '\n';
    std::cout << gs->GetComputer().GetName() + " Lupy: " + std::to_string(gs->GetComputerInventory().GetItemCount(GameEnums::MAGNIFIER)) << '\n';
    std::cout << gs->GetComputer().GetName() + " Telefony: " + std::to_string(gs->GetComputerInventory().GetItemCount(GameEnums::CELLPHONE)) << '\n';
    std::cout << gs->GetComputer().GetName() + " Kajdanki: " + std::to_string(gs->GetComputerInventory().GetItemCount(GameEnums::HANDCUFFS)) << '\n';
    std::cout << gs->GetComputer().GetName() + " Inwertery: " + std::to_string(gs->GetComputerInventory().GetItemCount(GameEnums::INVERTER)) << '\n';
    std::cout << '\n';
    std::cout << "Pelne pociski: " << std::to_string(gs->GetMagazine().GetFull()) << '\n';
    std::cout << "Puste pociski: " << std::to_string(gs->GetMagazine().GetEmpty()) << '\n';
    std::cout << "Liczba pociskow: " << std::to_string(gs->GetMagazine().GetMagazineSize()) << '\n';
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
}
 
void ConsoleUI::Menu() const
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
	std::cout << "7 - Wybierz format serializacji" << '\n';
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
}
 
void ConsoleUI::DifficultyMenu() const
{
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
    std::cout << "Wybierz poziom trudnosci:" << '\n';
    std::cout << "0 - Normalny" << '\n';
    std::cout << "1 - Latwy" << '\n';
    std::cout << "2 - Trudny" << '\n';
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
}

void ConsoleUI::RestartMenu() const
{
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
    std::cout << "Wybierz czy chcesz zagrac ponownie:" << '\n';
    std::cout << "0 - Nie" << '\n';
    std::cout << "1 - Tak" << '\n';
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
}

void ConsoleUI::SerializationMenu() const
{
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
    std::cout << "Wybierz format serializacji:" << '\n';
    std::cout << "0 - JSON" << '\n';
    std::cout << "1 - TXT" << '\n';
    std::cout << "-------------------------------------------------------------------------------------------------------------" << '\n';
}
 
void ConsoleUI::InventoryMenu() const
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
 
std::string ConsoleUI::GetAIDifficulty(const int8_t difficulty) const noexcept
{
    if (difficulty == GameEnums::EASY) { return "Latwy"; }
    else if (difficulty == GameEnums::NORMAL) { return "Normalny"; }
    else { return "Trudny"; }
}

std::string ConsoleUI::GetSerializationType(const int8_t serializationType) const noexcept
{
    if (serializationType == GameEnums::JSON) { return "JSON"; }
    else { return "TXT"; }
}
 
std::string ConsoleUI::GetFilename() const noexcept { return fileName; }
 
int8_t ConsoleUI::InputDifficultyLevel() noexcept
{
    std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 2): ",
        InputValidatorManager::IsValidDifficultyChoice);
    uint8_t choice = stoi(input);
	return choice;
}

int8_t ConsoleUI::InputSerializationType() noexcept
{
    std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 1): ",
        InputValidatorManager::IsValidSerializationChoice);
    uint8_t choice = stoi(input);
    return choice;
}
 
int8_t ConsoleUI::InputItemChoice() noexcept
{
    std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 6): ",
        InputValidatorManager::IsValidItemChoice);
    uint8_t choice = stoi(input);
    return choice;
}

int8_t ConsoleUI::InputRestartChoice() noexcept
{
    std::string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 1): ",
        InputValidatorManager::IsValidYesNo);
    uint8_t choice = stoi(input);
    return choice;
}

std::string ConsoleUI::GetRecentLogLine() const noexcept
{
    if (log.empty()) { return ""; }
    return log.back();
}
 
void ConsoleUI::Clear() const
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void ConsoleUI::Initialize() { /**/ } //musze cos z tym zrobic

bool ConsoleUI::GetUIType() const noexcept { return true; }

void ConsoleUI::ClearLog() { log.clear(); }
 
const std::deque<std::string>& ConsoleUI::GetLog() const noexcept { return log; }

void ConsoleUI::GetRecentLogUpdate(std::string newLogUpdate) { log.push_back(newLogUpdate); }
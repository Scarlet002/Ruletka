#include "AIStrategyManager.h"
#include "AutoSaveManager.h"
#include "GameConfig.h"
#include "GameConsoleVersion.h"
#include "GameEnums.h"
#include "ILoadManager.h"
#include "InputValidatorManager.h"
#include "ISaveAsyncManager.h"
#include "ISaveSyncManager.h"
#include "IUiManager.h"
#include "LoadJSONManager.h"
#include "LoadTXTManager.h" 
#include "MagazineManager.h"
#include "Player.h"              
#include "SaveJSONManager.h"
#include "SaveTXTManager.h" 
#include "TurnManager.h"
#include "UiManager.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <cstdint>

GameConsoleVersion::GameConsoleVersion() 
    : saver(std::make_unique<SaveJSONManager>())
	, loader(std::make_unique<LoadJSONManager>())
	, asyncSaver(std::make_unique<AutoSaveManager>(*saver))
	, ui(std::make_unique<UiManager>(state))
    , ai(std::make_unique<AIStrategyManager>(state)) {};

void GameConsoleVersion::NewRound()
{
    state.magazine->Reload();
    state.human->GetRandomItem();
	state.human->GetNumberOfItems();
	state.computer->GetRandomItem();
	state.computer->GetNumberOfItems();
    ui->Clear();
    ui->DisplayStats();
}
void GameConsoleVersion::NewLoop()
{
	std::string autoSaveFileName = ui->GetAutoSaveName();
    if (!asyncSaver->IsSaving()) 
    { 
        GameState snapshot;
        snapshot.CopyStateToSnapshot(state);
        asyncSaver->SaveGameStateAsync(std::move(snapshot));
    }
    ui->Clear();
    ui->DisplayStats();
    ui->AutoSaveDone();
	uint8_t counter = asyncSaver->GetSaveCounter();
    std::cout << autoSaveFileName 
        + std::to_string(counter) 
        + ".json" << '\n';
    ui->DisplayLastTurnLog();
    ui->Menu();
}
bool GameConsoleVersion::WhoWon()
{
    if (!state.human->IsAlive())
    {
        asyncSaver->SetSaveCounter(0);
        ui->ComputerWin();
        return true;
    }
    if (!state.computer->IsAlive())
    {
        asyncSaver->SetSaveCounter(0);
        ui->HumanWin();
        return true;
    }
    return false;
}
void GameConsoleVersion::Initialize()
{
	state.human->ResetHP();
	state.computer->ResetHP();
	state.magazine->Reload();
	state.human->ResetInventory();
	state.computer->ResetInventory();
    ai->SetStrategy(GameConfig::defaultDifficulty);
    ui->ClearLog();
	state.turn->SetDifficulty(GameConfig::defaultDifficulty);
    state.turn->RandomizeStarter();
    if (state.turn->GetStarter() == GameEnums::STARTER_HUMAN) 
        { ui->HumanStarts(); }
    else { ui->ComputerStarts(); }
}
void GameConsoleVersion::VerifyMagazine()
{
    if (state.magazine->IsEmpty())
    {
        throw std::runtime_error("Brak pociskow w magazynku!");
    }
}
void GameConsoleVersion::ChangeTurnHandler(IPlayer& turnHandler)
{
    if (!state.turn->GetStateOfHandCuffs())
    {
        if (turnHandler.GetType())
        {
            state.turn->SetStarter(GameEnums::STARTER_COMPUTER);
        }
        else { state.turn->SetStarter(GameEnums::STARTER_HUMAN); }
    }
    else { state.turn->SetStateOfHandCuffs(GameEnums::HANDCUFFS_NOT_USED); }
}
void GameConsoleVersion::CloseInventoryForAI(IPlayer& turnHandler)
{
    if (!turnHandler.GetType())
    {
        state.turn->SetStateOfInventory(GameEnums::INVENTORY_NOT_SHOWN);
    }
}
void GameConsoleVersion::ProcessHeal(IPlayer& turnHandler)
{
    VerifyMagazine();
    if (state.magazine->CheckBulletType())
    {
        uint8_t damage = state.turn->GetDamage();
        state.magazine->DecreaseFullCount();
        turnHandler.LoseHP(damage);
        std::string logLine = turnHandler.GetName()
            + " stracil "
            + std::to_string(damage)
            + " HP!";
        ui->SetRecentLogLine(logLine);
    }
    else
    {
        state.magazine->DecreaseEmptyCount();
        turnHandler.RegainHP();
        std::string logLine = turnHandler.GetName()
            + " odzyskal 1 HP!";
        ui->SetRecentLogLine(logLine);
    }
    state.magazine->DecreaseBulletCount();
    state.turn->SetDamage(GameConfig::defaultDamage);
    state.turn->SetStateOfCellPhone(false);
    state.turn->SetStateOfMagnifier(false);
    ChangeTurnHandler(turnHandler);
}
void GameConsoleVersion::ProcessShot(IPlayer& turnHandler, IPlayer& target)
{
    VerifyMagazine();
    if (state.magazine->CheckBulletType())
    {
        uint8_t damage = state.turn->GetDamage();
        state.magazine->DecreaseFullCount();
        target.LoseHP(damage);
        std::string logLine = turnHandler.GetName()
            + " trafil " 
            + target.GetName() 
            + " i zadal mu "
            + std::to_string(damage) 
            + " obrazen!";
        ui->SetRecentLogLine(logLine);
    }
    else
    {
        state.magazine->DecreaseEmptyCount();
        std::string logLine = turnHandler.GetName()
            + " nie trafil " 
            + target.GetName()
            + "!";
        ui->SetRecentLogLine(logLine);
    }
    state.magazine->DecreaseBulletCount();
    state.turn->SetDamage(GameConfig::defaultDamage);
    state.turn->SetStateOfCellPhone(false);
    state.turn->SetStateOfMagnifier(false);
    ChangeTurnHandler(turnHandler);
}
void GameConsoleVersion::HandleHandCuffs(IPlayer& turnHandler)
{
    std::string logLine = "";
    if (turnHandler.GetHandCuffs() == 0)
    {
        logLine = turnHandler.GetName()
            + " nie ma tego przedmiotu!";
    }
    else
    {
        turnHandler.UseItem(state.turn->GetChoice());
        state.turn->SetStateOfHandCuffs(GameEnums::HANDCUFFS_USED);
        logLine = turnHandler.GetName()
            + " uzyl kajdanek! Otrzymuje dodatkowy ruch!";
    }
    ui->SetRecentLogLine(logLine);
}
void GameConsoleVersion::HandleBeer(IPlayer& turnHandler)
{
    std::string logLine = "";
    if (turnHandler.GetBeers() == 0)
    {
        logLine = turnHandler.GetName()
            + " nie ma tego przedmiotu!";
    }
    else
    {
        VerifyMagazine();
        turnHandler.UseItem(state.turn->GetChoice());
        if (state.magazine->CheckBulletType())
        {
            state.magazine->DecreaseFullCount();
        }
        else { state.magazine->DecreaseEmptyCount(); }
        state.magazine->DecreaseBulletCount();
        logLine = turnHandler.GetName()
            + " uzyl piwa! Usuwa pierwszy pocisk!";
    }
    ui->SetRecentLogLine(logLine);
}
void GameConsoleVersion::HandleMagnifier(IPlayer& turnHandler)
{
    std::string logLine = "";
    if (turnHandler.GetMagnifiers() == 0)
    {
        logLine = turnHandler.GetName()
            + " nie ma tego przedmiotu!";
    }
    else
    {
        turnHandler.UseItem(state.turn->GetChoice());
        logLine = turnHandler.GetName()
            + " uzyl lupy! ";
        state.turn->SetHitProbability(state.magazine->CheckBulletType());
        state.turn->SetStateOfMagnifier(true);
        if (turnHandler.GetType())
        {
            logLine += "Piewszy pocisk jest ";
            if (state.magazine->CheckBulletType()) { logLine += "pelny!"; }
            else { logLine += "pusty!"; }
        }
    }
    ui->SetRecentLogLine(logLine);
}
void GameConsoleVersion::HandleSaw(IPlayer& turnHandler)
{
    std::string logLine = "";
    if (turnHandler.GetSaws() == 0)
    {
        logLine = turnHandler.GetName()
            + " nie ma tego przedmiotu!";
    }
    else
    {
        turnHandler.UseItem(state.turn->GetChoice());
        state.turn->SetDamage(GameConfig::sawDamage);
        logLine = turnHandler.GetName()
            + " uzyl pily! Obrazenia zwiekszone dla kolejnego strzalu";
    }
    ui->SetRecentLogLine(logLine);
}
void GameConsoleVersion::HandleCellPhone(IPlayer& turnHandler)
{
    std::string logLine = "";
    if (turnHandler.GetCellPhones() == 0)
    {
        logLine = turnHandler.GetName()
            + " nie ma tego przedmiotu!";
    }
    else
    {
        turnHandler.UseItem(state.turn->GetChoice());
        logLine = turnHandler.GetName()
            + " uzyl telefonu! ";
        state.turn->SetHitProbability(state.magazine->CheckBulletType());
        state.turn->SetStateOfCellPhone(true);
        if (turnHandler.GetType())
        {
            uint8_t randomBullet = rand() % state.magazine->GetMagazineSize();
            if (state.magazine->CheckBulletTypeCellPhone(randomBullet))
            {
                logLine += std::to_string(randomBullet + 1)
                    + " pocisk jest pelny!";
            }
            else {
                logLine += std::to_string(randomBullet + 1)
                    + " pocisk jest pusty!";
            }
        }
    }
    ui->SetRecentLogLine(logLine);
}
void GameConsoleVersion::HandleInverter(IPlayer& turnHandler)
{
    std::string logLine = "";
    if (turnHandler.GetInverters() == 0)
    {
        logLine = turnHandler.GetName()
            + " nie ma tego przedmiotu!";
    }
    else
    {
        turnHandler.UseItem(state.turn->GetChoice());
        state.magazine->InvertBulletType();
        logLine = turnHandler.GetName()
            + " uzyl inwertera! Zmieniono typ pocisku!";
    }
    ui->SetRecentLogLine(logLine);
}
void GameConsoleVersion::HandleInventory(IPlayer& turnHandler)
{
    if (!turnHandler.GetType())
    {
        state.turn->SetStateOfInventory(GameEnums::INVENTORY_SHOWN);
        state.turn->SetChoice(ai->MakeDecision());
    }
    else
    {
        ui->InventoryMenu();
        state.turn->SetChoice(ui->InputItemChoice());
    }
    std::string logLine = "";
    switch (state.turn->GetChoice())
    {
    case GameEnums::NO_ITEMS:
        logLine = turnHandler.GetName()
            + " nie uzyl zadnego przedmiotu!";
        ui->SetRecentLogLine(logLine);
        break;
    case GameEnums::HANDCUFFS:
        HandleHandCuffs(turnHandler);
        break;
    case GameEnums::BEER:
        HandleBeer(turnHandler);
        break;
    case GameEnums::MAGNIFIER:
        HandleMagnifier(turnHandler);
        break;
    case GameEnums::SAW:
        HandleSaw(turnHandler);
        break;
    case GameEnums::CELLPHONE:
        HandleCellPhone(turnHandler);
        break;
    case GameEnums::INVERTER:
        HandleInverter(turnHandler);
        break;
    default:
        ui->InvalidInput();
        logLine = "Nieprawidlowy wybor!";
        ui->SetRecentLogLine(logLine);
        break;
    }
    CloseInventoryForAI(turnHandler);
}
void GameConsoleVersion::HandleExit(bool& isRunning)
{
    isRunning = false;
    ui->Clear();
    ui->ThankYou();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
void GameConsoleVersion::HandleSave()
{
    ui->InputSaveJSON();
    std::string fileName = ui->GetFileName();
    saver->SaveGameState(state, fileName);
    std:: string logLine = "Gra zostala zapisana jako "
        + fileName 
        + "!";
    ui->SetRecentLogLine(logLine);
}
void GameConsoleVersion::HandleLoad()
{
    ui->InputLoadJSON();
    std::string fileName = ui->GetFileName();
    loader->LoadGameState(state, fileName);
    std::string logLine = "Gra zostala wczytana z pliku " 
        + fileName 
        + "!";
    ui->SetRecentLogLine(logLine);
}
void GameConsoleVersion::HandleDifficulty()
{
    ui->DifficultyMenu();
    state.turn->SetDifficulty(ui->InputdifficultyLevel());
    ai->SetStrategy(state.turn->GetDifficulty());
    std::string logLine = "Poziom trudnosci zostal ustawiony na "
        + ui->GetAIDifficulty(state.turn->GetDifficulty()) 
        + "!";
    ui->NewLine();
    ui->SetRecentLogLine(logLine);
}
void GameConsoleVersion::ProcessTurn(IPlayer& turnHandler,
    IPlayer& target, bool& isRunning)
{
    if (!state.turn->GetStateOfMagnifier()
        && !state.turn->GetStateOfCellPhone())
    {
        state.turn->SetHitProbability(state.magazine->CalculateHitProbability());
    }
    uint8_t choice = 0;
    if (turnHandler.GetType())
    {
        NewLoop();
        choice = ui->HumanDecision();
    }
    else
    {
        ui->ComputerChoosing();
        choice = ai->MakeDecision();
    }
    state.turn->SetChoice(choice);
    switch (choice)
    {
        case GameEnums::HEAL:
            ProcessHeal(turnHandler);
            break;
        case GameEnums::SHOOT:
            ProcessShot(turnHandler, target);
		    break;
        case GameEnums::USEITEM:
            HandleInventory(turnHandler);
            break;
        case GameEnums::EXIT:
            HandleExit(isRunning);
            break;
        case GameEnums::SAVE:
            HandleSave();
            break;
        case GameEnums::LOAD:
            HandleLoad();
            break;
        case GameEnums::DIFFICULTY:
            HandleDifficulty();
            break;
        default:
            ui->InvalidInput();
            break;
    }
}
void GameConsoleVersion::Run()
{
    bool isRunning = true;
    Initialize();
    do
    {
        state.magazine->CheckBullets();
        if (state.turn->GetStarter() == GameEnums::STARTER_HUMAN)
        {
            ProcessTurn(*state.human, *state.computer, isRunning);
        }
        else { ProcessTurn(*state.computer, *state.human, isRunning); }
        if (WhoWon()) 
        {
            ui->Clear();
            ui->DisplayStats();
            ui->DisplayLastTurnLog();
            if (!ui->WantsToContinue())
            {
                isRunning = false;
                ui->Clear();
                ui->ThankYou();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                ui->Clear();
            }
            else { Initialize(); }
        }
        if (state.magazine->IsOutOfBullets()) { NewRound(); }
    } while (isRunning);
}
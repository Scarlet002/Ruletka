#include "AIStrategyManager.h"
#include "AutoSaveManager.h"
#include "GameConfig.h"
#include "GameEngine.h"
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
#include "UiSFMLManager.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <cstdint>

GameEngine::GameEngine()
    : saver(std::make_unique<SaveJSONManager>())
    , loader(std::make_unique<LoadJSONManager>())
    , asyncSaver(std::make_unique<AutoSaveManager>(*saver))
    , ai(std::make_unique<AIStrategyManager>(state))
{
    if (false) // <- to bêdzie zmienione, ale jeszcze nie mam g³ownego menu gdzie gracz wybiera sobie implementacjê
    {
        ui = std::make_unique<UiManager>(state);
    }
    else
    {
        ui = std::make_unique<UiSFMLManager>(state);
        ui->Initialize();
    }
    Initialize();
};

void GameEngine::NewRound()
{
    state.magazine->Reload();
    state.human->GetRandomItem();
    state.human->GetNumberOfItems();
    state.computer->GetRandomItem();
    state.computer->GetNumberOfItems();
}

void GameEngine::HandleAutosave()
{
    if (state.turn->GetChoice() == GameEnums::HEAL
        || state.turn->GetChoice() == GameEnums::SHOOT)
    {
        if (!asyncSaver->IsSaving())
        {
            asyncSaver->SaveGameStateAsync(state);
            std::string logLine = "Wykonano zapis: autosave"
                + std::to_string(asyncSaver->GetSaveCounter());
            ui->SetRecentLogLine(logLine);
        }
    }
}

void GameEngine::Initialize()
{
    ui->ResetUI();
    state.turn->SetPreviousChoice(GameEnums::EXIT);
    state.turn->SetIsOnePlayerAlive(false);
    state.turn->SetCurrentMenu(GameEnums::MAIN_MENU);
    state.human->ResetHP();
    state.computer->ResetHP();
    state.magazine->Reload();
    state.human->ResetInventory();
    state.computer->ResetInventory();
    ai->SetStrategy(GameConfig::defaultDifficulty);
    state.turn->SetDifficulty(GameConfig::defaultDifficulty);
    state.turn->RandomizeStarter();
}

void GameEngine::VerifyMagazine()
{
    if (state.magazine->IsEmpty())
    {
        throw std::runtime_error("Brak pociskow w magazynku!");
    }
}

void GameEngine::ChangeTurnHandler(IPlayer& turnHandler)
{
    if (!state.turn->GetStateOfHandCuffs())
    {
        if (turnHandler.GetType())
        {
            state.turn->SetStarter(GameEnums::COMPUTER);
        }
        else { state.turn->SetStarter(GameEnums::HUMAN); }
    }
    else { state.turn->SetStateOfHandCuffs(GameEnums::ITEM_NOT_USED); }
}

void GameEngine::CloseInventoryForAI(IPlayer& turnHandler)
{
    if (!turnHandler.GetType())
    {
        state.turn->SetCurrentMenu(GameEnums::MAIN_MENU);
    }
}

void GameEngine::ProcessHeal(IPlayer& turnHandler)
{
    VerifyMagazine();
    if (state.magazine->CheckBulletType(GameEnums::LOADED))
    {
        uint8_t damage = state.turn->GetDamage();
        turnHandler.LoseHP(damage);
        std::string logLine = turnHandler.GetName()
            + " stracil "
            + std::to_string(damage)
            + " HP!";
        ui->SetRecentLogLine(logLine);
    }
    else
    {
        turnHandler.RegainHP();
        std::string logLine = turnHandler.GetName()
            + " odzyskal 1 HP!";
        ui->SetRecentLogLine(logLine);
    }
    state.magazine->UpdateMagazineState(GameEnums::LOADED);
    state.turn->SetDamage(GameConfig::defaultDamage);
    state.turn->SetStateOfCellPhone(false);
    state.turn->SetStateOfMagnifier(false);
    ChangeTurnHandler(turnHandler);
}

void GameEngine::ProcessShot(IPlayer& turnHandler, IPlayer& target)
{
    VerifyMagazine();
    if (state.magazine->CheckBulletType(GameEnums::LOADED))
    {
        uint8_t damage = state.turn->GetDamage();
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
        std::string logLine = turnHandler.GetName()
            + " nie trafil "
            + target.GetName()
            + "!";
        ui->SetRecentLogLine(logLine);
    }
    state.magazine->UpdateMagazineState(GameEnums::LOADED);
    state.turn->SetDamage(GameConfig::defaultDamage);
    state.turn->SetStateOfCellPhone(false);
    state.turn->SetStateOfMagnifier(false);
    ChangeTurnHandler(turnHandler);
}

void GameEngine::HandleHandCuffs(IPlayer& turnHandler)
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
        state.turn->SetStateOfHandCuffs(GameEnums::ITEM_USED);
        logLine = turnHandler.GetName()
            + " uzyl kajdanek! Otrzymuje dodatkowy ruch!";
    }
    ui->SetRecentLogLine(logLine);
}

void GameEngine::HandleBeer(IPlayer& turnHandler)
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
        state.magazine->UpdateMagazineState(GameEnums::LOADED);
        logLine = turnHandler.GetName()
            + " uzyl piwa! Usuwa pierwszy pocisk!";
    }
    ui->SetRecentLogLine(logLine);
}

void GameEngine::HandleMagnifier(IPlayer& turnHandler)
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
        state.turn->SetHitProbability(state.magazine->CheckBulletType(GameEnums::LOADED));
        state.turn->SetStateOfMagnifier(true);
        if (turnHandler.GetType())
        {
            logLine += "Piewszy pocisk jest ";
            if (state.magazine->CheckBulletType(GameEnums::LOADED)) { logLine += "pelny!"; }
            else { logLine += "pusty!"; }
        }
    }
    ui->SetRecentLogLine(logLine);
}

void GameEngine::HandleSaw(IPlayer& turnHandler)
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

void GameEngine::HandleCellPhone(IPlayer& turnHandler)
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
        state.turn->SetHitProbability(state.magazine->CheckBulletType(GameEnums::LOADED));
        state.turn->SetStateOfCellPhone(true);
        if (turnHandler.GetType())
        {
            uint8_t randomBullet = rand() % state.magazine->GetMagazineSize();
            if (state.magazine->CheckBulletType(randomBullet))
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

void GameEngine::HandleInverter(IPlayer& turnHandler)
{
    std::string logLine = "";
    if (turnHandler.GetInverters() <= 0)
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

void GameEngine::HandleInventory(IPlayer& turnHandler)
{
    if (!turnHandler.GetType())
    {
        state.turn->SetChoice(ai->Decision());
    }
    else
    {
        state.turn->SetChoice(ui->Decision());
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
    case GameEnums::NO_CHOICE:
		break;
    default:
        logLine = "Nieprawidlowy wybor!";
        ui->SetRecentLogLine(logLine);
        break;
    }
    if (state.turn->GetChoice() != GameEnums::NO_CHOICE)
    {
        state.turn->SetCurrentMenu(GameEnums::MAIN_MENU);
    }
}

void GameEngine::HandleExit(bool& isRunning)
{
    isRunning = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void GameEngine::HandleSave()
{
    if (ui->Decision() != GameEnums::NO_CHOICE)
    {
        std::string fileName = ui->GetFilename();
        saver->SaveGameState(state, fileName);
        std::string logLine = "Gra zostala zapisana jako "
            + fileName
            + "!";
        ui->SetRecentLogLine(logLine);
        state.turn->SetCurrentMenu(GameEnums::MAIN_MENU);
    }
}

void GameEngine::HandleLoad()
{
    if (ui->Decision() != GameEnums::NO_CHOICE)
    {
        std::string fileName = ui->GetFilename();
        loader->LoadGameState(state, fileName);
        std::string logLine = "Gra zostala wczytana z pliku "
            + fileName
            + "!";
        ui->SetRecentLogLine(logLine);
        state.turn->SetCurrentMenu(GameEnums::MAIN_MENU);
    }
}

void GameEngine::HandleDifficulty()
{
    int8_t choice = ui->Decision();
    if (state.turn->GetRecentDifficulty() != state.turn->GetDifficulty())
    {
        state.turn->SetRecentDifficulty(state.turn->GetDifficulty());
    }
    if (choice != GameEnums::NO_CHOICE)
    {
        state.turn->SetDifficulty(choice);
        ai->SetStrategy(state.turn->GetDifficulty());
        std::string logLine = "Poziom trudnosci: "
            + ui->GetAIDifficulty(state.turn->GetDifficulty())
            + "!";
        ui->SetRecentLogLine(logLine);
        state.turn->SetCurrentMenu(GameEnums::MAIN_MENU);
    }
}

void GameEngine::HandleRestart(bool& isRunning)
{
    state.turn->SetChoice(ui->Decision());
    if (state.turn->GetChoice() == GameEnums::RESTART_YES)
    {
        Initialize();
        ui->ResetUI();
    }
    if (state.turn->GetChoice() == GameEnums::RESTART_NO) 
    { 
        HandleExit(isRunning);
    }
}

void GameEngine::ProcessTurn(IPlayer& turnHandler,
    IPlayer& target, bool& isRunning)
{
    if (state.turn->GetCurrentMenu() == GameEnums::MAIN_MENU)
    {
        HandleMainMenu(turnHandler, target, isRunning);
    }
    else if (state.turn->GetCurrentMenu() == GameEnums::DIFFICULTY_MENU)
    {
        HandleDifficulty();
    }
    else if (state.turn->GetCurrentMenu() == GameEnums::INVENTORY_MENU)
    {
        HandleInventory(turnHandler);
    }
    else if (state.turn->GetCurrentMenu() == GameEnums::SAVE_MENU)
    {
        HandleSave();
    }
    else if (state.turn->GetCurrentMenu() == GameEnums::LOAD_MENU)
    {
        HandleLoad();
    }
    else
    {
        HandleRestart(isRunning);
    }
}

void GameEngine::HandleMainMenu(IPlayer& turnHandler,
    IPlayer& target, bool& isRunning)
{
    if (!state.turn->GetStateOfMagnifier()
        && !state.turn->GetStateOfCellPhone())
    {
        state.turn->SetHitProbability(state.magazine->CalculateHitProbability());
    }
    int8_t choice = GameEnums::NO_CHOICE;
    if (turnHandler.GetType())
    {
        choice = ui->Decision();
        HandleAutosave();
    }
    else
    {
        choice = ai->Decision();
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
		state.turn->SetCurrentMenu(GameEnums::INVENTORY_MENU);
        break;
    case GameEnums::EXIT:
        HandleExit(isRunning);
        break;
    case GameEnums::SAVE:
        state.turn->SetCurrentMenu(GameEnums::SAVE_MENU);
        break;
    case GameEnums::LOAD:
        state.turn->SetCurrentMenu(GameEnums::LOAD_MENU);
        break;
    case GameEnums::DIFFICULTY:
        state.turn->SetCurrentMenu(GameEnums::DIFFICULTY_MENU);
        break;
    case GameEnums::NO_CHOICE:
        break;
    default:
        break;
    }
}

void GameEngine::Run()
{
    bool isRunning = true;
    do
    {
        if (ui->GetUIType())
        {
            ui->Render();
        }
        else
        {
            if (state.turn->GetChoice() != state.turn->GetPreviousChoice())
            {
                ui->Render();
            }
        }
        if (state.turn->GetStarter() == GameEnums::HUMAN)
        {
            ProcessTurn(*state.human, *state.computer, isRunning);
        }
        else { ProcessTurn(*state.computer, *state.human, isRunning); }
		CheckGameConditions(isRunning);
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    } while (isRunning);
}

void GameEngine::CheckGameConditions(bool& isRunning)
{
    if (!state.human->IsAlive()
        || !state.computer->IsAlive())
    {
        state.turn->SetCurrentMenu(GameEnums::RESTART_MENU);
        state.turn->SetIsOnePlayerAlive(true);
        asyncSaver->SetSaveCounter(0);
    }
    if (state.magazine->IsEmpty()
        && !state.turn->GetIsOnePlayerAlive()) { NewRound(); }
}
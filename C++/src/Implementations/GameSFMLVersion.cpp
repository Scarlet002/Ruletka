#include "GameSFMLVersion.h"
#include "GameEnums.h"
#include <iostream>
#include <thread>

GameSFMLVersion::GameSFMLVersion(LoadJSONManager& loaderJSON, SaveJSONManager& saverJSON)
    : magazine(gameConfig), gameStateManager(gameConfig),
    human("Gracz", "human", gameConfig),
    computer("Komputer", "computer", gameConfig),
    ai(), log(),
    gameState(static_cast<IPlayer&>(human),
        static_cast<IPlayer&>(computer),
        static_cast<IMagazineManager&>(magazine),
        static_cast<IGameStateManager&>(gameStateManager),
        gameConfig,
        static_cast<IAiManager&>(ai),
        log),
    loaderJSON(loaderJSON), saverJSON(saverJSON),
    ui(gameState),
    gameRunning(true), playerTurn(false), gameOver(false),
    filename(""), autoSaveFileName("")
{
    asyncSaver = std::make_unique<AutoSaveManager>(saverJSON, gameState);

    if (!ui.Initialize()) {
        std::cerr << "Blad inicjalizacji UI!" << std::endl;
        gameRunning = false;
        return;
    }

    ui.SetGameReference(this);
    InitializeGame();
}

void GameSFMLVersion::InitializeGame() {
    human.ResetHP();
    computer.ResetHP();
    magazine.Reload();
    human.ResetInventory(gameState);
    computer.ResetInventory(gameState);
    gameStateManager.RandomizeStarter();
    gameStateManager.SetStateOfHandCuffs(false);
    gameStateManager.SetDamage(gameConfig.defaultDamage);
    asyncSaver->SetSaveCounter(0);
    ui.ClearLog(gameState);


    ai.SetDifficulty(gameConfig.defaultDifficulty);
    gameStateManager.SetChoice(GameEnums::NO_CHOICE);
    gameStateManager.SetItem(GameEnums::NO_ITEMS);

    if (gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN) {
        playerTurn = true;
        ui.AddToLog(gameState, "Zaczynasz Ty!");
        ui.AddToLog(gameState, "Twoja tura - wybierz akcje!");
    }
    else {
        playerTurn = false;
        ui.AddToLog(gameState, "Zaczyna komputer!");
    }

    gameOver = false;
    gameState.wasAutoSaved = false;
    gameState.wasLogCleared = false;

    gameState.currentGameState = GameEnums::STATE_RUNNING;
    gameState.waitingForRestartChoice = false;
    ui.ClearLog(gameState);
}

void GameSFMLVersion::Run() {
    while (gameRunning && ui.IsWindowOpen()) {

        CheckGameConditions();

        if (playerTurn && !gameOver)
        {
            ui.ProcessEvents(gameState);
        }

        CheckGameConditions();

        if (!playerTurn && !gameOver) {
            ProcessComputerTurn();
        }

        CheckGameConditions();

        ui.Render(gameState);

        sf::sleep(sf::milliseconds(16));
    }
}

void GameSFMLVersion::HandlePlayerChoice(int choice) {
    if (gameOver || !playerTurn) {
        ui.AddToLog(gameState, "Nie twoja tura!");
        return;
    }

    std::cout << "Gracz wybral: " << choice << std::endl;

    switch (choice) {
    case GameEnums::HEAL:
    case GameEnums::SHOOT:
        ProcessPlayerAction(choice);
        break;

    case GameEnums::USEITEM:
        ui.ShowItemMenu(true);
        ui.AddToLog(gameState, "Wybierz przedmiot...");
        break;

    case GameEnums::SAVE:
        ui.ShowSaveLoadMenu(true);
        ui.StartFilenameInput(GameEnums::SAVE);
        break;

    case GameEnums::LOAD:
        ui.ShowSaveLoadMenu(true);
        ui.StartFilenameInput(GameEnums::LOAD);
        break;

    case GameEnums::DIFFICULTY:
        ui.ShowDifficultyMenu(true);
        ui.AddToLog(gameState, "Wybierz poziom trudnosci...");
        break;

    case GameEnums::EXIT:
        gameRunning = false;
        break;

    case GameEnums::EASY:
    case GameEnums::NORMAL:
    case GameEnums::HARD:
        HandleDifficultyChoice(choice);
        break;

    case GameEnums::RESTART_YES:
        if (ui.IsRestartButtonCreated())
        {
            HandleRestartChoice(GameEnums::RESTART_YES);
        }
        break;

    case GameEnums::RESTART_NO:
        if (ui.IsRestartButtonCreated())
        {
            HandleRestartChoice(GameEnums::RESTART_NO);
        }
        break;

    default:
        break;
    }
}

void GameSFMLVersion::ProcessPlayerAction(int action) {
    gameState.wasAutoSaved = false;
    gameState.gameStateManager.SetChoice(action);

    if (action == GameEnums::HEAL)
    {
        gameState.gameStateManager.SetTarget(GameEnums::TARGET_HUMAN);
        gameState.gameStateManager.SetShooter(GameEnums::SHOOTER_HUMAN);
        gameState.human.Shoot(gameState);
        gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);
        ui.AddToLog(gameState, "Probujesz odzyskac HP!");
    }
    else
    {
        gameState.gameStateManager.SetTarget(GameEnums::TARGET_COMPUTER);
        gameState.gameStateManager.SetShooter(GameEnums::SHOOTER_HUMAN);
        gameState.human.Shoot(gameState);
        gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);
        ui.AddToLog(gameState, "Strzelasz w komputer!");
    }

    if (!gameState.wasLogCleared)
    {
        gameState.wasLogCleared = true;
        ui.ClearLog(gameState);
    }

    if (!gameState.wasAutoSaved)
    {
        gameState.wasAutoSaved = true;
        asyncSaver->SaveGameStateAsync(gameState, autoSaveFileName);
        gameState.log.push_back("Autozapis wykonany: " + autoSaveFileName);
    }

    if (!gameStateManager.GetStateOfHandCuffs()) {
        SwitchTurn();
    }
    else
    {
        gameStateManager.SetStateOfHandCuffs(false);
        ui.AddToLog(gameState, "Komputer traci ture (kajdanki)!");
        playerTurn = true;
    }

    ui.ShowItemMenu(false);
    ui.ShowSaveLoadMenu(false);
    ui.ShowDifficultyMenu(false);
    ui.ShowRestartMenu(false);
    gameState.wasLogCleared = false;
    gameState.wasMagazineShown = false;
}

void GameSFMLVersion::HandleItemChoice(int item) {
    if (gameOver || !playerTurn) {
        return;
    }

    ui.ShowItemMenu(false);

    UseItem(item);

    ui.AddToLog(gameState, "Wybierz akcje (strzel lub lecz)");
}

void GameSFMLVersion::UseItem(int item) {
    switch (item) {
    case GameEnums::CELLPHONE:
        if (human.GetCellPhones() > 0)
        {
            human.UseCellPhone(gameState);
            ui.AddToLog(gameState, "Uzyles telefonu!");
        }
        else {
            ui.AddToLog(gameState, "Nie masz telefonu!");
        }
        break;

    case GameEnums::SAW:
        if (human.GetSaws() > 0)
        {
            human.UseSaw(gameState);
            ui.AddToLog(gameState, "Uzyles pily!");
        }
        else {
            ui.AddToLog(gameState, "Nie masz pily!");
        }
        break;

    case GameEnums::BEER:
        if (human.GetBeers() > 0) {
            human.UseBeer(gameState);
            ui.AddToLog(gameState, "Uzyles piwa!");
        }
        else {
            ui.AddToLog(gameState, "Nie masz piwa!");
        }
        break;

    case GameEnums::MAGNIFIER:
        if (human.GetMagnifiers() > 0) {
            human.UseMagnifier(gameState);
            ui.AddToLog(gameState, "Uzyles lupy!");
        }
        else {
            ui.AddToLog(gameState, "Nie masz lupy!");
        }
        break;

    case GameEnums::HANDCUFFS:
        if (human.GetHandCuffs() > 0) {
            human.UseHandCuffs(gameState);
            ui.AddToLog(gameState, "Uzyles kajdanek!");
        }
        else {
            ui.AddToLog(gameState, "Nie masz kajdanek!");
        }
        break;

    case GameEnums::INVERTER:
        if (human.GetInverters() > 0) {
            human.UseInverter(gameState);
            ui.AddToLog(gameState, "Uzyles inwertera!");
        }
        else {
            ui.AddToLog(gameState, "Nie masz inwertera!");
        }
        break;

    case GameEnums::NO_ITEMS:
        ui.AddToLog(gameState, "Nie uzyto przedmiotu");
        break;

    default:
        ui.AddToLog(gameState, "Nieprawidlowy przedmiot!");
        break;
    }
}

void GameSFMLVersion::ProcessComputerTurn() {

    int difficulty = ai.GetDifficulty();

    if (difficulty == GameEnums::EASY) {
        ai.EasyAI(gameState);
    }
    else if (difficulty == GameEnums::NORMAL) {
        ai.NormalAI(gameState);
    }
    else {
        ai.HardAI(gameState);
    }

    int computerChoice = gameState.gameStateManager.GetChoice();

    if (computerChoice == GameEnums::SHOOT) {
        gameState.gameStateManager.SetTarget(GameEnums::TARGET_HUMAN);
        gameState.gameStateManager.SetShooter(GameEnums::SHOOTER_COMPUTER);
        gameState.computer.Shoot(gameState);
        gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);
        ui.AddToLog(gameState, "Komputer strzela w Ciebie!");
    }
    else {
        gameState.gameStateManager.SetTarget(GameEnums::TARGET_COMPUTER);
        gameState.gameStateManager.SetShooter(GameEnums::SHOOTER_COMPUTER);
        gameState.computer.Shoot(gameState);
        gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);
        ui.AddToLog(gameState, "Komputer probuje leczyc!");
    }

    if (!gameStateManager.GetStateOfHandCuffs()) {
        SwitchTurn();
    }
    else {
        gameStateManager.SetStateOfHandCuffs(false);
        ui.AddToLog(gameState, "Tracisz ture (kajdanki)!");
        playerTurn = false;
    }

    gameStateManager.SetChoice(GameEnums::NO_CHOICE);
    gameStateManager.SetItem(GameEnums::NO_ITEMS);
}

void GameSFMLVersion::SwitchTurn() {
    playerTurn = !playerTurn;

    if (playerTurn) {
        gameStateManager.SetStarter(GameEnums::STARTER_HUMAN);
        ui.AddToLog(gameState, "Twoja tura!");
    }
    else {
        gameStateManager.SetStarter(GameEnums::STARTER_COMPUTER);
    }
}

void GameSFMLVersion::CheckGameConditions() {
    if (!human.isAlive())
    {
        gameOver = true;
        gameState.currentGameState = GameEnums::STATE_COMPUTER_WIN;
        gameState.waitingForRestartChoice = true;
        ui.ProcessEvents(gameState);
    }
    else if (!computer.isAlive())
    {
        gameOver = true;
        gameState.currentGameState = GameEnums::STATE_HUMAN_WIN;
        gameState.waitingForRestartChoice = true;
        ui.ProcessEvents(gameState);
    }

    if (magazine.IsOutOfBullets()) {
        ui.AddToLog(gameState, "Koniec pociskow! Przeladowanie!");
        magazine.Reload();
        human.GetRandomItem(gameState);
        human.GetNumberOfItems(gameState);
        computer.GetRandomItem(gameState);
        computer.GetNumberOfItems(gameState);
    }
}

void GameSFMLVersion::HandleDifficultyChoice(int difficulty) {
    if (difficulty >= GameEnums::EASY && difficulty <= GameEnums::HARD) {
        ai.SetDifficulty(difficulty);
        ui.AddToLog(gameState, "Zmieniono poziom trudnosci!");
    }

    gameState.wasLogCleared = false;
    ui.ShowDifficultyMenu(false);
}

void GameSFMLVersion::HandleRestartChoice(int choice) {
    if (choice == GameEnums::RESTART_YES)
    {
        ui.ShowRestartMenu(false);

        InitializeGame();

        ui.ResetUI(gameState);

        ui.AddToLog(gameState, "Nowa gra! Zaczynamy!");
    }
    else
    {
        ui.ShowRestartMenu(false);
        gameRunning = false;
        ui.CloseWindow();
    }
}

void GameSFMLVersion::HandleSaveLoadWithFilename(int action, const std::string& filename) {
    if (action == GameEnums::SAVE) {
        saverJSON.SaveGameState(gameState, filename);
        ui.AddToLog(gameState, "Zapisano gre do: " + filename + ".json");
    }
    else if (action == GameEnums::LOAD) {
        try {
            loaderJSON.LoadGameState(gameState, filename);
            ui.AddToLog(gameState, "Wczytano gre z: " + filename + ".json");

            playerTurn = (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN);
            gameOver = false;
        }
        catch (const std::exception& e) {
            ui.AddToLog(gameState, "Blad wczytywania: " + std::string(e.what()));
        }
    }

    gameState.wasLogCleared = false;
    ui.ShowSaveLoadMenu(false);
}

GameSFMLVersion::~GameSFMLVersion() {
    gameRunning = false;
}
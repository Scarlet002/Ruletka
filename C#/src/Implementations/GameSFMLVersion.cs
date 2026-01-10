using System;
using System.Collections.Generic;
using SFML.System;

public class GameSFMLVersion : IGameSFML
{
    private GameConfig gameConfig = new GameConfig();
    private IMagazineManager magazine;
    private IGameStateManager gameStateManager;
    private IPlayer human;
    private IPlayer computer;
    private IAiManager ai = new AiManager();
    private List<string> log = new List<string>();

    private ILoadManager loaderJSON;
    private ISaveSyncManager saverJSON;
    private GameState gameState;

    private ISaveAsyncManager asyncSaver;
    private IUiSFMLManager ui;

    private bool gameRunning;
    private string autoSaveFileName;
    private string filename;

    private bool playerTurn;
    private bool gameOver;

    public GameSFMLVersion(LoadJSONManager loaderJSON, SaveJSONManager saverJSON)
    {
        this.loaderJSON = loaderJSON;
        this.saverJSON = saverJSON;

        magazine = new MagazineManager(gameConfig);
        gameStateManager = new GameStateManager(gameConfig);
        human = new Player("Gracz", "human", gameConfig);
        computer = new Player("Komputer", "computer", gameConfig);

        gameState = new GameState(human, computer, magazine, gameStateManager, gameConfig, ai, log);
        asyncSaver = new AutoSaveManager(saverJSON, gameState);
        ui = new UiSFMLManager(gameState);

        gameRunning = true;
        playerTurn = false;
        gameOver = false;
        filename = "";
        autoSaveFileName = "";

        if (!ui.Initialize())
        {
            Console.Error.WriteLine("Blad inicjalizacji UI!");
            gameRunning = false;
            return;
        }

        ai.SetDifficulty((int)gameConfig.defaultDifficulty);
        ui.SetGameReference(this);
        InitializeGame();
    }

    public void InitializeGame()
    {
        human.ResetHP();
        computer.ResetHP();
        magazine.Reload();
        human.ResetInventory(gameState);
        computer.ResetInventory(gameState);
        gameStateManager.RandomizeStarter();
        gameStateManager.SetStateOfHandCuffs(false);
        gameStateManager.SetDamage(gameConfig.defaultDamage);
        asyncSaver.SetSaveCounter(0);
        ui.ClearLog(gameState);

        gameStateManager.SetChoice((int)GameEnums.Choice.NO_CHOICE);
        gameStateManager.SetItem((int)GameEnums.Item.NO_ITEMS);

        if (gameStateManager.GetStarter() == (int)GameEnums.Starter.STARTER_HUMAN)
        {
            playerTurn = true;
            ui.AddToLog(gameState, "Zaczynasz Ty!");
            ui.AddToLog(gameState, "Twoja tura - wybierz akcje!");
        }
        else
        {
            playerTurn = false;
            ui.AddToLog(gameState, "Zaczyna komputer!");
        }

        gameOver = false;
        gameState.wasAutoSaved = false;
        gameState.wasLogCleared = false;
        gameState.wasMagazineShown = false;

        gameState.currentGameState = GameEnums.GameStateEnum.STATE_RUNNING;
        gameState.waitingForRestartChoice = false;
        ui.ClearLog(gameState);
    }

    public void Run()
    {
        while (gameRunning && ui.IsWindowOpen())
        {
            CheckGameConditions();

            if (playerTurn && !gameOver)
            {
                ui.ProcessEvents(gameState);
            }

            CheckGameConditions();

            if (!playerTurn && !gameOver)
            {
                ProcessComputerTurn();
            }

            CheckGameConditions();

            ui.Render(gameState);

            System.Threading.Thread.Sleep(16);
        }
    }

    public void HandlePlayerChoice(int choice)
    {
        if (gameOver || !playerTurn)
        {
            ui.AddToLog(gameState, "Nie twoja tura!");
            return;
        }

        Console.WriteLine("Gracz wybral: " + choice);

        switch (choice)
        {
            case (int)GameEnums.Choice.HEAL:
            case (int)GameEnums.Choice.SHOOT:
                ProcessPlayerAction(choice);
                break;

            case (int)GameEnums.Choice.USEITEM:
                ui.ShowItemMenu(true);
                ui.AddToLog(gameState, "Wybierz przedmiot");
                break;

            case (int)GameEnums.Choice.SAVE:
                ui.ShowSaveLoadMenu(true);
                ui.StartFilenameInput((int)GameEnums.Choice.SAVE);
                break;

            case (int)GameEnums.Choice.LOAD:
                ui.ShowSaveLoadMenu(true);
                ui.StartFilenameInput((int)GameEnums.Choice.LOAD);
                break;

            case (int)GameEnums.Choice.DIFFICULTY:
                ui.ShowDifficultyMenu(true);
                ui.AddToLog(gameState, "Wybierz poziom trudnosci");
                break;

            case (int)GameEnums.Choice.EXIT:
                gameRunning = false;
                break;

            case (int)GameEnums.Difficulty.EASY:
            case (int)GameEnums.Difficulty.NORMAL:
            case (int)GameEnums.Difficulty.HARD:
                HandleDifficultyChoice(choice);
                break;

            case (int)GameEnums.RestartChoice.RESTART_YES:
                if (ui.IsRestartButtonCreated())
                {
                    HandleRestartChoice((int)GameEnums.RestartChoice.RESTART_YES);
                }
                break;

            case (int)GameEnums.RestartChoice.RESTART_NO:
                if (ui.IsRestartButtonCreated())
                {
                    HandleRestartChoice((int)GameEnums.RestartChoice.RESTART_NO);
                }
                break;

            default:
                break;
        }
    }

    public void ProcessPlayerAction(int action)
    {
        gameState.wasAutoSaved = false;
        gameState.gameStateManager.SetChoice(action);

        if (action == (int)GameEnums.Choice.HEAL)
        {
            gameState.gameStateManager.SetTarget((int)GameEnums.Target.TARGET_HUMAN);
            gameState.gameStateManager.SetShooter((int)GameEnums.Shooter.SHOOTER_HUMAN);
            gameState.human.Shoot(gameState);
            gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);
            ui.AddToLog(gameState, "Probujesz odzyskac HP!");
        }
        else
        {
            gameState.gameStateManager.SetTarget((int)GameEnums.Target.TARGET_COMPUTER);
            gameState.gameStateManager.SetShooter((int)GameEnums.Shooter.SHOOTER_HUMAN);
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
            string autoSaveComplete = asyncSaver.SaveGameStateAsync(gameState, autoSaveFileName);
            ui.AddToLog(gameState, "Autozapis wykonany: " + autoSaveComplete);
        }

        if (!gameStateManager.GetStateOfHandCuffs())
        {
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

    public void HandleItemChoice(int item)
    {
        if (gameOver || !playerTurn)
        {
            return;
        }

        ui.ShowItemMenu(false);
        UseItem(item);
        ui.AddToLog(gameState, "Wybierz akcje (strzel lub lecz)");
    }

    public void UseItem(int item)
    {
        switch (item)
        {
            case (int)GameEnums.Item.CELLPHONE:
                if (human.GetCellPhones() > 0)
                {
                    human.UseCellPhone(gameState);
                    ui.AddToLog(gameState, "Uzyles telefonu!");
                }
                else
                {
                    ui.AddToLog(gameState, "Nie masz telefonu!");
                }
                break;

            case (int)GameEnums.Item.SAW:
                if (human.GetSaws() > 0)
                {
                    human.UseSaw(gameState);
                    ui.AddToLog(gameState, "Uzyles pily!");
                }
                else
                {
                    ui.AddToLog(gameState, "Nie masz pily!");
                }
                break;

            case (int)GameEnums.Item.BEER:
                if (human.GetBeers() > 0)
                {
                    human.UseBeer(gameState);
                    ui.AddToLog(gameState, "Uzyles piwa!");
                }
                else
                {
                    ui.AddToLog(gameState, "Nie masz piwa!");
                }
                break;

            case (int)GameEnums.Item.MAGNIFIER:
                if (human.GetMagnifiers() > 0)
                {
                    human.UseMagnifier(gameState);
                    ui.AddToLog(gameState, "Uzyles lupy!");
                }
                else
                {
                    ui.AddToLog(gameState, "Nie masz lupy!");
                }
                break;

            case (int)GameEnums.Item.HANDCUFFS:
                if (human.GetHandCuffs() > 0)
                {
                    human.UseHandCuffs(gameState);
                    ui.AddToLog(gameState, "Uzyles kajdanek!");
                }
                else
                {
                    ui.AddToLog(gameState, "Nie masz kajdanek!");
                }
                break;

            case (int)GameEnums.Item.INVERTER:
                if (human.GetInverters() > 0)
                {
                    gameState.wasMagazineShown = true;
                    human.UseInverter(gameState);
                    ui.AddToLog(gameState, "Uzyles inwertera!");
                }
                else
                {
                    ui.AddToLog(gameState, "Nie masz inwertera!");
                }
                break;

            case (int)GameEnums.Item.NO_ITEMS:
                ui.AddToLog(gameState, "Nie uzyto przedmiotu");
                break;

            default:
                ui.AddToLog(gameState, "Nieprawidlowy przedmiot!");
                break;
        }
    }

    public void ProcessComputerTurn()
    {
        int difficulty = ai.GetDifficulty();

        if (difficulty == (int)GameEnums.Difficulty.EASY)
        {
            ai.EasyAI(gameState);
        }
        else if (difficulty == (int)GameEnums.Difficulty.NORMAL)
        {
            ai.NormalAI(gameState);
        }
        else
        {
            ai.HardAI(gameState);
        }

        int computerChoice = gameState.gameStateManager.GetChoice();

        if (computerChoice == (int)GameEnums.Choice.SHOOT)
        {
            gameState.gameStateManager.SetTarget((int)GameEnums.Target.TARGET_HUMAN);
            gameState.gameStateManager.SetShooter((int)GameEnums.Shooter.SHOOTER_COMPUTER);
            gameState.computer.Shoot(gameState);
            gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);
            ui.AddToLog(gameState, "Komputer strzela w Ciebie!");
        }
        else
        {
            gameState.gameStateManager.SetTarget((int)GameEnums.Target.TARGET_COMPUTER);
            gameState.gameStateManager.SetShooter((int)GameEnums.Shooter.SHOOTER_COMPUTER);
            gameState.computer.Shoot(gameState);
            gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);
            ui.AddToLog(gameState, "Komputer probuje leczyc!");
        }

        if (!gameStateManager.GetStateOfHandCuffs())
        {
            SwitchTurn();
        }
        else
        {
            gameStateManager.SetStateOfHandCuffs(false);
            ui.AddToLog(gameState, "Tracisz ture (kajdanki)!");
            playerTurn = false;
        }

        gameStateManager.SetChoice((int)GameEnums.Choice.NO_CHOICE);
        gameStateManager.SetItem((int)GameEnums.Item.NO_ITEMS);
    }

    public void SwitchTurn()
    {
        playerTurn = !playerTurn;

        if (playerTurn)
        {
            gameStateManager.SetStarter((int)GameEnums.Starter.STARTER_HUMAN);
            ui.AddToLog(gameState, "Twoja tura!");
        }
        else
        {
            gameStateManager.SetStarter((int)GameEnums.Starter.STARTER_COMPUTER);
        }
    }

    public void CheckGameConditions()
    {
        if (!human.IsAlive())
        {
            gameOver = true;
            gameState.currentGameState = GameEnums.GameStateEnum.STATE_COMPUTER_WIN;
            gameState.waitingForRestartChoice = true;
            ui.ProcessEvents(gameState);
        }
        else if (!computer.IsAlive())
        {
            gameOver = true;
            gameState.currentGameState = GameEnums.GameStateEnum.STATE_HUMAN_WIN;
            gameState.waitingForRestartChoice = true;
            ui.ProcessEvents(gameState);
        }

        if (magazine.IsOutOfBullets())
        {
            ui.AddToLog(gameState, "Koniec pociskow! Przeladowanie!");
            magazine.Reload();
            human.GetRandomItem(gameState);
            human.GetNumberOfItems(gameState);
            computer.GetRandomItem(gameState);
            computer.GetNumberOfItems(gameState);
        }
    }

    public void HandleDifficultyChoice(int difficulty)
    {
        if (difficulty >= (int)GameEnums.Difficulty.EASY && difficulty <= (int)GameEnums.Difficulty.HARD)
        {
            ai.SetDifficulty(difficulty);
            ui.AddToLog(gameState, "Zmieniono poziom trudnosci!");
        }

        gameState.wasLogCleared = false;
        ui.ShowDifficultyMenu(false);
    }

    public void HandleRestartChoice(int choice)
    {
        if (choice == (int)GameEnums.RestartChoice.RESTART_YES)
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

    public void HandleSaveLoadWithFilename(int action, string filename)
    {
        if (action == (int)GameEnums.Choice.SAVE)
        {
            saverJSON.SaveGameState(gameState, filename);
            ui.AddToLog(gameState, "Zapisano gre do: " + filename + ".json");
        }
        else if (action == (int)GameEnums.Choice.LOAD)
        {
            try
            {
                loaderJSON.LoadGameState(gameState, filename);
                ui.AddToLog(gameState, "Wczytano gre z: " + filename + ".json");

                playerTurn = (gameState.gameStateManager.GetStarter() == (int)GameEnums.Starter.STARTER_HUMAN);
                gameOver = false;
            }
            catch (Exception e)
            {
                ui.AddToLog(gameState, "Blad wczytywania: " + e.Message);
            }
        }

        gameState.wasLogCleared = false;
        ui.ShowSaveLoadMenu(false);
    }
}
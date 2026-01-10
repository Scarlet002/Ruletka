using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;

public class GameConsoleVersion : IGame
{
    private GameConfig gameConfig = new GameConfig();
    private MagazineManager magazine;
    private GameStateManager gameStateManager;
    private AiManager ai = new AiManager();
    private Player human;
    private Player computer;
    private List<string> log = new List<string>();
    private GameState gameState;
    private AutoSaveManager asyncSaver;
    private IUiManager ui;
    private SaveJSONManager saverJSON;
    private LoadJSONManager loaderJSON;
    private string fileName = "";
    private string autoSaveFileName = "";

    public GameConsoleVersion(LoadJSONManager loaderJSON, SaveJSONManager saverJSON)
    {
        this.loaderJSON = loaderJSON;
        this.saverJSON = saverJSON;

        magazine = new MagazineManager(gameConfig);
        gameStateManager = new GameStateManager(gameConfig);
        human = new Player("Czlowiek", "human", gameConfig);
        computer = new Player("Komputer", "computer", gameConfig);

        gameState = new GameState(human, computer, magazine, gameStateManager, gameConfig, ai, log);
        asyncSaver = new AutoSaveManager(saverJSON, gameState);
        ui = new UiManager();
    }

    public void NewRound(GameState gameState, IUiManager ui)
    {
        ui.EndOfBullets();
        gameState.magazine.Reload();
        gameState.human.GetRandomItem(gameState);
        gameState.human.GetNumberOfItems(gameState);
        gameState.computer.GetRandomItem(gameState);
        gameState.computer.GetNumberOfItems(gameState);
        ui.ScrollScreen();
        ui.Clear();
        ui.DisplayStats(gameState);
    }

    public bool WhoWon(GameState gameState, IUiManager ui)
    {
        if (!gameState.human.IsAlive())
        {
            asyncSaver.SetSaveCounter(0);
            ui.ComputerWin();
            return true;
        }
        else if (!gameState.computer.IsAlive())
        {
            asyncSaver.SetSaveCounter(0);
            ui.HumanWin();
            return true;
        }
        return false;
    }

    public void StartGame()
    {
        gameState.human.ResetHP();
        gameState.computer.ResetHP();
        gameState.magazine.Reload();
        gameState.human.ResetInventory(gameState);
        gameState.computer.ResetInventory(gameState);
        gameState.gameStateManager.RandomizeStarter();
        gameState.gameStateManager.SetStateOfHandCuffs(false);
        gameState.log.Clear();
        asyncSaver.SetSaveCounter(0);
        ui.Clear();
        ui.DisplayStats(gameState);

        while (true)
        {
            if (gameState.gameStateManager.GetStarter() == (int)GameEnums.Starter.STARTER_HUMAN)
            {
                asyncSaver.SaveGameStateAsync(gameState, autoSaveFileName);
                ui.AutoSaveDone();
                ui.ShowAutoSaveName(autoSaveFileName);
                ui.Menu();

                if (gameState.log.Count != 0)
                {
                    for (int i = 0; i < gameState.log.Count; i++)
                    {
                        if (i != 0)
                        {
                            if (i % gameConfig.maxLogsInLine == 0)
                            {
                                Console.WriteLine();
                            }
                            Console.Write(" -> ");
                        }
                        Console.Write(gameState.log[i]);
                    }
                }
                gameState.log.Clear();

                ui.NewLine();
                gameState.human.MakeDecision(gameState);

                if (gameState.gameStateManager.GetChoice() == (int)GameEnums.Choice.SHOOT)
                {
                    gameState.gameStateManager.SetShooter((int)GameEnums.Shooter.SHOOTER_HUMAN);
                    gameState.gameStateManager.SetTarget((int)GameEnums.Target.TARGET_COMPUTER);
                    gameState.human.Shoot(gameState);
                    ui.ShowPointer();
                    gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);

                    if (!gameState.gameStateManager.GetStateOfHandCuffs())
                    {
                        gameState.gameStateManager.SetStarter((int)GameEnums.Starter.STARTER_COMPUTER);
                    }
                    else
                    {
                        gameState.gameStateManager.SetStateOfHandCuffs(false);
                    }
                }
                else if (gameState.gameStateManager.GetChoice() == (int)GameEnums.Choice.HEAL)
                {
                    gameState.gameStateManager.SetShooter((int)GameEnums.Shooter.SHOOTER_HUMAN);
                    gameState.gameStateManager.SetTarget((int)GameEnums.Target.TARGET_HUMAN);
                    gameState.human.Shoot(gameState);
                    ui.ShowPointer();
                    gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);

                    if (!gameState.gameStateManager.GetStateOfHandCuffs())
                    {
                        gameState.gameStateManager.SetStarter((int)GameEnums.Starter.STARTER_COMPUTER);
                    }
                    else
                    {
                        gameState.gameStateManager.SetStateOfHandCuffs(false);
                    }
                }
                else if (gameState.gameStateManager.GetChoice() == (int)GameEnums.Choice.USEITEM)
                {
                    ui.InventoryMenu();
                    ui.InputItemChoice(gameState);
                    ui.ItemUseSuccessHuman(gameState);
                    gameState.human.GetNumberOfItems(gameState);
                    ui.ShowPointer();
                }
                else if (gameState.gameStateManager.GetChoice() == (int)GameEnums.Choice.SAVE)
                {
                    ui.InputSaveJSON(ref fileName);
                    saverJSON.SaveGameState(gameState, fileName);
                    ui.SavingSuccess();
                    ui.ShowPointer();
                }
                else if (gameState.gameStateManager.GetChoice() == (int)GameEnums.Choice.LOAD)
                {
                    ui.InputLoadJSON(ref fileName);
                    loaderJSON.LoadGameState(gameState, fileName);
                    ui.LoadingSuccess();
                    ui.ShowPointer();
                }
                else if (gameState.gameStateManager.GetChoice() == (int)GameEnums.Choice.DIFFICULTY)
                {
                    ui.DifficultyMenu();
                    ui.InputDifficultyLevel(gameState);
                    ui.DifficultyChangeSuccess();
                    ui.ShowPointer();
                }
                else if (gameState.gameStateManager.GetChoice() == (int)GameEnums.Choice.EXIT)
                {
                    ui.Clear();
                    ui.ThankYou();
                    Thread.Sleep(1000);
                    break;
                }
            }
            else
            {
                ui.ComputerChoosing();
                gameState.computer.MakeDecision(gameState);

                if (gameState.gameStateManager.GetChoice() == (int)GameEnums.Choice.SHOOT)
                {
                    gameState.gameStateManager.SetShooter((int)GameEnums.Shooter.SHOOTER_COMPUTER);
                    gameState.gameStateManager.SetTarget((int)GameEnums.Target.TARGET_HUMAN);
                    gameState.computer.Shoot(gameState);
                    gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);

                    if (!gameState.gameStateManager.GetStateOfHandCuffs())
                    {
                        gameState.gameStateManager.SetStarter((int)GameEnums.Starter.STARTER_HUMAN);
                    }
                    else
                    {
                        gameState.gameStateManager.SetStateOfHandCuffs(false);
                    }
                    ui.NewLine();
                }
                else
                {
                    gameState.gameStateManager.SetShooter((int)GameEnums.Shooter.SHOOTER_COMPUTER);
                    gameState.gameStateManager.SetTarget((int)GameEnums.Target.TARGET_COMPUTER);
                    gameState.computer.Shoot(gameState);
                    gameState.gameStateManager.SetDamage(gameConfig.defaultDamage);

                    if (!gameState.gameStateManager.GetStateOfHandCuffs())
                    {
                        gameState.gameStateManager.SetStarter((int)GameEnums.Starter.STARTER_HUMAN);
                    }
                    else
                    {
                        gameState.gameStateManager.SetStateOfHandCuffs(false);
                    }
                    ui.NewLine();
                }
            }

            ui.Clear();
            ui.DisplayStats(gameState);

            if (WhoWon(gameState, ui))
            {
                if (!ui.WantsToContinue(gameState))
                {
                    Thread.Sleep(1000);
                    break;
                }
            }

            if (gameState.magazine.IsOutOfBullets())
                NewRound(gameState, ui);
        }
    }
}
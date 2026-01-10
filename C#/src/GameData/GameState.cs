using System.Collections.Generic;

public class GameState
{
    public GameState(IPlayer human, IPlayer computer, IMagazineManager magazine,
        IGameStateManager gameStateManager, GameConfig gameConfig,
        IAiManager ai, List<string> log)
    {
        this.human = human;
        this.computer = computer;
        this.magazine = magazine;
        this.gameStateManager = gameStateManager;
        this.gameConfig = gameConfig;
        this.ai = ai;
        this.log = log;

        waitingForPlayer = true;
        gameRunning = true;
        waitingForRestartChoice = false;
        wasAutoSaved = false;
        wasLogCleared = false;
        wasMagazineShown = false;
        isComputerTurn = false;
        currentGameState = GameEnums.GameStateEnum.STATE_RUNNING;
    }

    public IPlayer human;
    public IPlayer computer;
    public IMagazineManager magazine;
    public IGameStateManager gameStateManager;
    public GameConfig gameConfig;
    public IAiManager ai;
    public List<string> log;

    public bool waitingForPlayer;
    public bool gameRunning;
    public bool waitingForRestartChoice;
    public bool wasAutoSaved;
    public bool wasLogCleared;
    public bool wasMagazineShown;
    public bool isComputerTurn;
    public GameEnums.GameStateEnum currentGameState;
}
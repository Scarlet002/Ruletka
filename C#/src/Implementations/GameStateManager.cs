using System;

public class GameStateManager : IGameStateManager
{
    private GameConfig gameConfig;
    private int starter = (int)GameEnums.Starter.STARTER_HUMAN;
    private int choice = (int)GameEnums.Choice.NO_CHOICE;
    private int target = (int)GameEnums.Target.TARGET_COMPUTER;
    private int shooter = (int)GameEnums.Shooter.SHOOTER_HUMAN;
    private int item = (int)GameEnums.Item.NO_ITEMS;
    private int damage;
    private bool wereHandCuffsUsed = false;
    private string logLine = "";

    public GameStateManager(GameConfig gameConfig)
    {
        this.gameConfig = gameConfig;
        damage = gameConfig.defaultDamage;
    }

    public void SetItem(int newItem) { item = newItem; }
    public void SetStarter(int newStarter) { starter = newStarter; }
    public void SetChoice(int newChoice) { choice = newChoice; }
    public void SetTarget(int newTarget) { target = newTarget; }
    public void SetShooter(int newShooter) { shooter = newShooter; }
    public void SetDamage(int newDamage) { damage = newDamage; }
    public void SetStateOfHandCuffs(bool newState) { wereHandCuffsUsed = newState; }
    public void SetLogLine(string newLogLine) { logLine = newLogLine; }

    public int GetStarter() { return starter; }
    public int GetChoice() { return choice; }
    public int GetTarget() { return target; }
    public int GetShooter() { return shooter; }
    public int GetDamage() { return damage; }
    public int GetItem() { return item; }
    public bool GetStateOfHandCuffs() { return wereHandCuffsUsed; }
    public string GetLogLine() { return logLine; }

    public int RandomizeStarter()
    {
        Random rand = new Random();
        starter = rand.Next(gameConfig.numberOfPlayers);
        return starter;
    }

    public void ResetDamage()
    {
        SetDamage(gameConfig.defaultDamage);
    }
}
using System.Collections.Generic;

public class Player : IPlayer
{
    private DecisionManager decision;
    private ShootingManager gun;
    private InventoryManager inventory;
    private IHpManager hp;
    private string name;
    private string type;

    public Player(string playerName, string playerType, GameConfig gameConfig)
    {
        name = playerName;
        type = playerType;
        decision = new DecisionManager();
        gun = new ShootingManager();
        hp = new HpManager(gameConfig);
        inventory = new InventoryManager(gameConfig);
    }

    public void LoseHP(GameState gameState) { hp.LoseHP(gameState); }
    public void RegainHP() { hp.RegainHP(); }
    public void ResetHP() { hp.ResetHP(); }
    public int GetHP() { return hp.GetHP(); }
    public void SetHP(int newHP) { hp.SetHP(newHP); }
    public bool IsAlive() { return hp.GetHP() > 0; }
    public bool IsHuman() { return type == "human" || type == "Human"; }
    public bool IsComputer() { return type == "computer" || type == "Computer"; }

    public int MakeDecision(GameState gameState) { return decision.MakeDecision(gameState); }

    public void Shoot(GameState gameState) { gun.Shoot(gameState); }

    public int SetFreeSlots(int newFree) { return inventory.SetFreeSlots(newFree); }
    public int SetSaws(int newSaws) { return inventory.SetSaws(newSaws); }
    public int SetBeers(int newBeers) { return inventory.SetBeers(newBeers); }
    public int SetMagnifiers(int newMagnifiers) { return inventory.SetMagnifiers(newMagnifiers); }
    public int SetHandCuffs(int newHandCuffs) { return inventory.SetHandCuffs(newHandCuffs); }
    public int SetInverters(int newInverters) { return inventory.SetInverters(newInverters); }
    public int SetCellPhones(int newCellPhones) { return inventory.SetCellPhones(newCellPhones); }
    public void SetInventory(List<int> newInventory) { inventory.SetInventory(newInventory); }

    public int GetFreeSlots() { return inventory.GetFreeSlots(); }
    public int GetSaws() { return inventory.GetSaws(); }
    public int GetBeers() { return inventory.GetBeers(); }
    public int GetMagnifiers() { return inventory.GetMagnifiers(); }
    public int GetHandCuffs() { return inventory.GetHandCuffs(); }
    public int GetInverters() { return inventory.GetInverters(); }
    public int GetCellPhones() { return inventory.GetCellPhones(); }
    public List<int> GetInventory() { return inventory.GetInventory(); }

    public void GetRandomItem(GameState gameState) { inventory.GetRandomItem(gameState); }
    public void GetNumberOfItems(GameState gameState) { inventory.GetNumberOfItems(gameState); }
    public void ResetInventory(GameState gameState) { inventory.ResetInventory(gameState); }
    public void UseSaw(GameState gameState) { inventory.UseSaw(gameState); }
    public void UseMagnifier(GameState gameState) { inventory.UseMagnifier(gameState); }
    public void UseBeer(GameState gameState) { inventory.UseBeer(gameState); }
    public void UseCellPhone(GameState gameState) { inventory.UseCellPhone(gameState); }
    public void UseInverter(GameState gameState) { inventory.UseInverter(gameState); }
    public void UseHandCuffs(GameState gameState) { inventory.UseHandCuffs(gameState); }
}
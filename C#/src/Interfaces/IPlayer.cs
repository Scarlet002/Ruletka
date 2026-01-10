using System.Collections.Generic;

public interface IPlayer
{
    void LoseHP(GameState gameState);
    void RegainHP();
    void ResetHP();
    int GetHP();
    void SetHP(int newHP);
    bool IsAlive();
    bool IsHuman();
    bool IsComputer();

    int SetFreeSlots(int newFree);
    int SetSaws(int newSaws);
    int SetBeers(int newBeers);
    int SetMagnifiers(int newMagnifiers);
    int SetHandCuffs(int newHandCuffs);
    int SetInverters(int newInverters);
    int SetCellPhones(int newCellPhones);
    void SetInventory(List<int> newInventory);

    int GetFreeSlots();
    int GetSaws();
    int GetBeers();
    int GetMagnifiers();
    int GetHandCuffs();
    int GetInverters();
    int GetCellPhones();
    List<int> GetInventory();

    int MakeDecision(GameState gameState);
    void Shoot(GameState gameState);
    void GetRandomItem(GameState gameState);
    void GetNumberOfItems(GameState gameState);
    void ResetInventory(GameState gameState);
    void UseSaw(GameState gameState);
    void UseMagnifier(GameState gameState);
    void UseBeer(GameState gameState);
    void UseCellPhone(GameState gameState);
    void UseInverter(GameState gameState);
    void UseHandCuffs(GameState gameState);
}
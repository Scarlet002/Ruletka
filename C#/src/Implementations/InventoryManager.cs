using System;
using System.Collections.Generic;

public class InventoryManager : Inventory
{
    private int numberOfItems;
    private int free;
    private int saws;
    private int cellPhones;
    private int beers;
    private int handCuffsAmount;
    private int magnifiers;
    private int inverters;
    private List<int> inventory;
    private GameConfig gameConfig;
    private Item saw;
    private Item magnifier;
    private Item handCuffs;
    private Item beer;
    private Item inverter;
    private Item cellPhone;

    public int inventorySize;

    public InventoryManager(GameConfig gameConfig)
    {
        this.gameConfig = gameConfig;
        free = gameConfig.maxInventorySize;
        numberOfItems = gameConfig.minNumberOfItems;
        saws = gameConfig.minSaws;
        beers = gameConfig.minBeers;
        magnifiers = gameConfig.minMagnifiers;
        handCuffsAmount = gameConfig.minHandCuffs;
        inverters = gameConfig.minInverters;
        cellPhones = gameConfig.minCellPhones;
        inventorySize = gameConfig.maxInventorySize;
        inventory = new List<int>(new int[gameConfig.maxInventorySize]);

        saw = new Saw();
        beer = new Beer();
        magnifier = new Magnifier();
        handCuffs = new HandCuffs();
        inverter = new Inverter();
        cellPhone = new CellPhone();
    }

    public void GetRandomItem(GameState gameState)
    {
        int k = 0;
        Random rand = new Random();

        for (int i = 0; i < inventorySize; i++)
        {
            if (GetFreeSlots() > 0 && k < gameConfig.maxItemsRand)
            {
                if (inventory[i] == (int)GameEnums.Item.NO_ITEMS)
                {
                    inventory[i] = rand.Next(gameState.gameConfig.numberOfItemTypes) + gameState.gameConfig.minItemsRand;
                    SetFreeSlots(GetFreeSlots() - 1);
                    GetNumberOfItems(gameState);
                    k++;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                break;
            }
        }
    }

    public void GetNumberOfItems(GameState gameState)
    {
        SetFreeSlots(gameState.gameConfig.maxInventorySize);
        SetSaws(gameState.gameConfig.minSaws);
        SetBeers(gameState.gameConfig.minBeers);
        SetMagnifiers(gameState.gameConfig.minMagnifiers);
        SetInverters(gameState.gameConfig.minInverters);
        SetCellPhones(gameState.gameConfig.minCellPhones);
        SetHandCuffs(gameState.gameConfig.minHandCuffs);

        int freeCount = 0;
        int sawsCount = 0;
        int beersCount = 0;
        int magnifiersCount = 0;
        int invertersCount = 0;
        int cellPhonesCount = 0;
        int handCuffsCount = 0;

        for (int i = 0; i < inventorySize; i++)
        {
            if (inventory[i] == (int)GameEnums.Item.NO_ITEMS)
            {
                freeCount++;
            }
            else if (inventory[i] == (int)GameEnums.Item.CELLPHONE)
            {
                cellPhonesCount++;
            }
            else if (inventory[i] == (int)GameEnums.Item.BEER)
            {
                beersCount++;
            }
            else if (inventory[i] == (int)GameEnums.Item.SAW)
            {
                sawsCount++;
            }
            else if (inventory[i] == (int)GameEnums.Item.MAGNIFIER)
            {
                magnifiersCount++;
            }
            else if (inventory[i] == (int)GameEnums.Item.INVERTER)
            {
                invertersCount++;
            }
            else if (inventory[i] == (int)GameEnums.Item.HANDCUFFS)
            {
                handCuffsCount++;
            }
        }

        SetFreeSlots(freeCount);
        SetSaws(sawsCount);
        SetBeers(beersCount);
        SetMagnifiers(magnifiersCount);
        SetInverters(invertersCount);
        SetCellPhones(cellPhonesCount);
        SetHandCuffs(handCuffsCount);
    }

    public int SetFreeSlots(int newFree) { return free = newFree; }
    public int SetSaws(int newSaws) { return saws = newSaws; }
    public int SetBeers(int newBeers) { return beers = newBeers; }
    public int SetMagnifiers(int newMagnifiers) { return magnifiers = newMagnifiers; }
    public int SetHandCuffs(int newHandCuffs) { return handCuffsAmount = newHandCuffs; }
    public int SetInverters(int newInverters) { return inverters = newInverters; }
    public int SetCellPhones(int newCellPhones) { return cellPhones = newCellPhones; }

    public void SetInventory(List<int> newInventory)
    {
        inventory = newInventory;
        inventorySize = inventory.Count;
    }

    public int GetFreeSlots() { return free; }
    public int GetSaws() { return saws; }
    public int GetBeers() { return beers; }
    public int GetMagnifiers() { return magnifiers; }
    public int GetHandCuffs() { return handCuffsAmount; }
    public int GetInverters() { return inverters; }
    public int GetCellPhones() { return cellPhones; }
    public List<int> GetInventory() { return inventory; }

    public void ResetInventory(GameState gameState)
    {
        inventory.Clear();
        SetFreeSlots(gameState.gameConfig.maxInventorySize);
        SetSaws(gameState.gameConfig.minSaws);
        SetBeers(gameState.gameConfig.minBeers);
        SetMagnifiers(gameState.gameConfig.minMagnifiers);
        SetInverters(gameState.gameConfig.minInverters);
        SetCellPhones(gameState.gameConfig.minCellPhones);
        SetHandCuffs(gameState.gameConfig.minHandCuffs);
        inventory = new List<int>(new int[gameState.gameConfig.maxInventorySize]);
    }

    public void UseSaw(GameState gameState)
    {
        int k = 0;
        for (int i = 0; i < inventory.Count; i++)
        {
            if (inventory[i] == (int)GameEnums.Item.SAW && k == 0)
            {
                inventory[i] = (int)GameEnums.Item.NO_ITEMS;
                SetSaws(GetSaws() - 1);
                GetNumberOfItems(gameState);
                k++;
            }
            else
            {
                continue;
            }
        }
        saw.UseItem(gameState);
        GetNumberOfItems(gameState);
    }

    public void UseBeer(GameState gameState)
    {
        int k = 0;
        for (int i = 0; i < inventory.Count; i++)
        {
            if (inventory[i] == (int)GameEnums.Item.BEER && k == 0)
            {
                inventory[i] = (int)GameEnums.Item.NO_ITEMS;
                SetBeers(GetBeers() - 1);
                GetNumberOfItems(gameState);
                k++;
            }
            else
            {
                continue;
            }
        }
        beer.UseItem(gameState);
        GetNumberOfItems(gameState);
    }

    public void UseMagnifier(GameState gameState)
    {
        int k = 0;
        for (int i = 0; i < inventory.Count; i++)
        {
            if (inventory[i] == (int)GameEnums.Item.MAGNIFIER && k == 0)
            {
                inventory[i] = (int)GameEnums.Item.NO_ITEMS;
                SetMagnifiers(GetMagnifiers() - 1);
                GetNumberOfItems(gameState);
                k++;
            }
            else
            {
                continue;
            }
        }
        magnifier.UseItem(gameState);
        GetNumberOfItems(gameState);
    }

    public void UseHandCuffs(GameState gameState)
    {
        int k = 0;
        for (int i = 0; i < inventory.Count; i++)
        {
            if (inventory[i] == (int)GameEnums.Item.HANDCUFFS && k == 0)
            {
                inventory[i] = (int)GameEnums.Item.NO_ITEMS;
                SetHandCuffs(GetHandCuffs() - 1);
                GetNumberOfItems(gameState);
                k++;
            }
            else
            {
                continue;
            }
        }
        handCuffs.UseItem(gameState);
        GetNumberOfItems(gameState);
    }

    public void UseInverter(GameState gameState)
    {
        int k = 0;
        for (int i = 0; i < inventory.Count; i++)
        {
            if (inventory[i] == (int)GameEnums.Item.INVERTER && k == 0)
            {
                inventory[i] = (int)GameEnums.Item.NO_ITEMS;
                SetInverters(GetInverters() - 1);
                GetNumberOfItems(gameState);
                k++;
            }
            else
            {
                continue;
            }
        }
        inverter.UseItem(gameState);
        GetNumberOfItems(gameState);
    }

    public void UseCellPhone(GameState gameState)
    {
        int k = 0;
        for (int i = 0; i < inventory.Count; i++)
        {
            if (inventory[i] == (int)GameEnums.Item.CELLPHONE && k == 0)
            {
                inventory[i] = (int)GameEnums.Item.NO_ITEMS;
                SetCellPhones(GetCellPhones() - 1);
                GetNumberOfItems(gameState);
                k++;
            }
            else
            {
                continue;
            }
        }
        cellPhone.UseItem(gameState);
        GetNumberOfItems(gameState);
    }
}
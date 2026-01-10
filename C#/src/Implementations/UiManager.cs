using System;
using System.Collections.Generic;

public class UiManager : IUiManager
{
    public UiManager() { }

    public void DisplayStats(GameState gameState)
    {
        Console.WriteLine("-------------------------------------------------------------------------------------------------------------");
        Console.Write("Poziom trudnosci: ");
        ShowAIDifficulty(gameState.ai.GetDifficulty());
        Console.WriteLine("\n\nStatystyki:\n");
        Console.WriteLine("czlowiek HP: " + gameState.human.GetHP());
        Console.WriteLine("czlowiek Pily: " + gameState.human.GetSaws());
        Console.WriteLine("czlowiek Piwa: " + gameState.human.GetBeers());
        Console.WriteLine("czlowiek Lupy: " + gameState.human.GetMagnifiers());
        Console.WriteLine("czlowiek Telefony: " + gameState.human.GetCellPhones());
        Console.WriteLine("czlowiek Kajdanki: " + gameState.human.GetHandCuffs());
        Console.WriteLine("czlowiek Inwertery: " + gameState.human.GetInverters());
        Console.WriteLine();
        Console.WriteLine("komputer HP: " + gameState.computer.GetHP());
        Console.WriteLine("komputer Pily: " + gameState.computer.GetSaws());
        Console.WriteLine("komputer Piwa: " + gameState.computer.GetBeers());
        Console.WriteLine("komputer Lupy: " + gameState.computer.GetMagnifiers());
        Console.WriteLine("komputer Telefony: " + gameState.computer.GetCellPhones());
        Console.WriteLine("komputer Kajdanki: " + gameState.computer.GetHandCuffs());
        Console.WriteLine("komputer Inwertery: " + gameState.computer.GetInverters());
        Console.WriteLine();
        Console.WriteLine("Pelne pociski: " + gameState.magazine.ShowFull());
        Console.WriteLine("Puste pociski: " + gameState.magazine.ShowEmpty());
        Console.WriteLine("Liczba pociskow: " + gameState.magazine.ShowBulletCount());
        Console.WriteLine("-------------------------------------------------------------------------------------------------------------");
    }

    public void ScrollScreen()
    {
        for (int i = 0; i < 30; i++)
            Console.WriteLine();
    }

    public void Menu()
    {
        Console.WriteLine("Wybierz co chcesz zrobic:");
        Console.WriteLine("0 - Sprobuj odzyskac 1 HP");
        Console.WriteLine("1 - Strzel w komputer");
        Console.WriteLine("2 - Uzyj przedmiotu");
        Console.WriteLine("3 - Zakoncz gre");
        Console.WriteLine("4 - Zapisz gre");
        Console.WriteLine("5 - Wczytaj gre");
        Console.WriteLine("6 - Wybierz poziom trudnosci");
        Console.WriteLine("-------------------------------------------------------------------------------------------------------------");
    }

    public void DifficultyMenu()
    {
        Console.WriteLine("-------------------------------------------------------------------------------------------------------------");
        Console.WriteLine("Wybierz poziom trudnosci:");
        Console.WriteLine("0 - latwy");
        Console.WriteLine("1 - normalny");
        Console.WriteLine("2 - trudny");
        Console.WriteLine("-------------------------------------------------------------------------------------------------------------");
    }

    public void InventoryMenu()
    {
        Console.WriteLine("-------------------------------------------------------------------------------------------------------------");
        Console.WriteLine("Wybierz przedmiot ktory chcesz uzyc:");
        Console.WriteLine("0 - Nie uzywaj zadnego przedmiotu");
        Console.WriteLine("1 - Kajdanki");
        Console.WriteLine("2 - Piwo");
        Console.WriteLine("3 - Lupa");
        Console.WriteLine("4 - Pila");
        Console.WriteLine("5 - Telefon");
        Console.WriteLine("6 - Inwerter");
        Console.WriteLine("-------------------------------------------------------------------------------------------------------------");
    }

    public void ShowAIDifficulty(int difficulty)
    {
        if (difficulty == (int)GameEnums.Difficulty.EASY)
        {
            Console.Write("latwy");
        }
        else if (difficulty == (int)GameEnums.Difficulty.NORMAL)
        {
            Console.Write("normalny");
        }
        else
        {
            Console.Write("trudny");
        }
    }

    public void ItemUseSuccessHuman(GameState gameState)
    {
        if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.NO_ITEMS)
        {
            Console.Write("Nie uzyles zadnego przedmiotu!");
        }
        else if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.CELLPHONE && gameState.human.GetCellPhones() > 0)
        {
            gameState.human.UseCellPhone(gameState);
            Console.Write("Pomyslnie uzyles telefonu!");
        }
        else if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.SAW && gameState.human.GetSaws() > 0)
        {
            gameState.human.UseSaw(gameState);
            Console.Write("Pomyslnie uzyles pily!");
        }
        else if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.BEER && gameState.human.GetBeers() > 0)
        {
            gameState.human.UseBeer(gameState);
            Console.Write("Pomyslnie wypiles piwo!");
        }
        else if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.MAGNIFIER && gameState.human.GetMagnifiers() > 0)
        {
            gameState.human.UseMagnifier(gameState);
            Console.Write("Pomyslnie uzyles lupy!");
        }
        else if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.HANDCUFFS && gameState.human.GetHandCuffs() > 0)
        {
            gameState.human.UseHandCuffs(gameState);
            Console.Write("Pomyslnie uzyles kajdanek!");
        }
        else if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.INVERTER && gameState.human.GetInverters() > 0)
        {
            gameState.human.UseInverter(gameState);
            Console.Write("Pomyslnie uzyles inwertera!");
        }
        else
        {
            Console.Write("Nie masz tego przedmiotu!");
        }
    }

    public void ItemUseSuccessComputer(GameState gameState)
    {
        if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.NO_ITEMS)
        {
            Console.WriteLine("Komputer nie uzyl zadnego przedmiotu!");
        }
        else if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.CELLPHONE && gameState.computer.GetCellPhones() > 0)
        {
            gameState.computer.UseCellPhone(gameState);
            Console.WriteLine("Komputer pomyslnie uzyl telefonu!");
        }
        else if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.SAW && gameState.computer.GetSaws() > 0)
        {
            gameState.computer.UseSaw(gameState);
            Console.WriteLine("Komputer pomyslnie uzyl pily!");
        }
        else if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.BEER && gameState.computer.GetBeers() > 0)
        {
            gameState.computer.UseBeer(gameState);
            Console.WriteLine("Komputer pomyslnie uzyl piwo!");
        }
        else if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.MAGNIFIER && gameState.computer.GetMagnifiers() > 0)
        {
            gameState.computer.UseMagnifier(gameState);
            Console.WriteLine("Komputer pomyslnie uzyl lupy!");
        }
        else if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.HANDCUFFS && gameState.computer.GetHandCuffs() > 0)
        {
            gameState.computer.UseHandCuffs(gameState);
            Console.WriteLine("Komputer pomyslnie uzyl kajdanek!");
        }
        else if (gameState.gameStateManager.GetItem() == (int)GameEnums.Item.INVERTER && gameState.computer.GetInverters() > 0)
        {
            gameState.computer.UseInverter(gameState);
            Console.WriteLine("Komputer pomyslnie uzyl inwertera!");
        }
        else
        {
            Console.WriteLine("Komputer nie ma tego przedmiotu!");
        }
    }

    public void InputSaveTXT(ref string fileName)
    {
        fileName = InputValidatorManager.GetValidatedInput("Podaj nazwe zapisu: ", InputValidatorManager.IsValidFileName);
        fileName += ".txt";
    }

    public void InputLoadTXT(ref string fileName)
    {
        fileName = InputValidatorManager.GetValidatedInput("Podaj nazwe zapisu do wczytania: ", InputValidatorManager.IsValidFileName);
        fileName += ".txt";
    }

    public void InputSaveJSON(ref string fileName)
    {
        fileName = InputValidatorManager.GetValidatedInput("Podaj nazwe zapisu: ", InputValidatorManager.IsValidFileName);
        fileName += ".json";
    }

    public void InputLoadJSON(ref string fileName)
    {
        fileName = InputValidatorManager.GetValidatedInput("Podaj nazwe zapisu do wczytania: ", InputValidatorManager.IsValidFileName);
        fileName += ".json";
    }

    public void InputDifficultyLevel(GameState gameState)
    {
        string input = InputValidatorManager.GetValidatedInput("Twoj wybor (0 - 2): ", InputValidatorManager.IsValidDifficultyChoice);
        gameState.ai.SetDifficulty(int.Parse(input));
    }

    public void InputItemChoice(GameState gameState)
    {
        string input = InputValidatorManager.GetValidatedInput("Twoj wybor (0 - 6): ", InputValidatorManager.IsValidItemChoice);
        gameState.gameStateManager.SetItem(int.Parse(input));
    }

    public bool WantsToContinue(GameState gameState)
    {
        string ans = InputValidatorManager.GetValidatedInput("Czy chcesz kontynuowac gre? (t/n): ", InputValidatorManager.IsValidYesNo);
        if (ans == "t" || ans == "T")
        {
            gameState.human.ResetHP();
            gameState.computer.ResetHP();
            gameState.magazine.Reload();
            gameState.human.ResetInventory(gameState);
            gameState.human.GetNumberOfItems(gameState);
            gameState.computer.ResetInventory(gameState);
            gameState.computer.GetNumberOfItems(gameState);
            Clear();
            DisplayStats(gameState);
            return true;
        }
        else
        {
            Clear();
            ThankYou();
            return false;
        }
    }

    public void ComputerChoosing() { Console.WriteLine("Wybiera komputer!"); }
    public void ComputerStarts() { Console.WriteLine("Zaczyna komputer!"); }
    public void HumanStarts() { Console.WriteLine("Zaczynasz ty!"); }
    public void ShowPointer() { Console.WriteLine("								*"); }
    public void NewLine() { Console.WriteLine(); }
    public void AutoSaveDone() { Console.Write("Zapis automatyczny zakonczony: "); }
    public void ShowAutoSaveName(string autoSaveFileName)
    {
        Console.WriteLine(autoSaveFileName);
        Console.WriteLine("-------------------------------------------------------------------------------------------------------------");
    }
    public void SavingSuccess() { Console.Write("Pomyslnie zapisano stan gry!"); }
    public void LoadingSuccess() { Console.Write("Pomyslnie wczytano stan gry!"); }
    public void DifficultyChangeSuccess() { Console.Write("Pomyslnie zmieniono poziom trudnosci!"); }
    public void InvalidInput() { Console.WriteLine("Nieprawidlowy wybor."); }
    public void ComputerWin() { Console.WriteLine("Komputer wygrywa gre!"); }
    public void HumanWin() { Console.WriteLine("Wygrywasz gre!"); }
    public void EndOfBullets() { Console.WriteLine("Koniec pociskow! Przeladowanie!"); }
    public void ThankYou() { Console.WriteLine("Dziekuje za gre! Do zobaczenia!"); }
    public void Clear()
    {
        Console.Clear();
    }
}
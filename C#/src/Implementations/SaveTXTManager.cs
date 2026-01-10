using System;
using System.Collections.Generic;
using System.IO;

public class SaveTXTManager : ISaveSyncManager
{
    public void SaveGameState(GameState gameState, string fileName)
    {
        try
        {
            string saveDir;

            if (fileName.Contains("autosave"))
            {
                saveDir = SaveConfig.GetAutoSaveDirectory();
            }
            else
            {
                saveDir = SaveConfig.GetSaveDirectory();
            }

            if (!SaveConfig.CreateDirectoryIfNotExists(saveDir))
            {
                Console.WriteLine("Nie mozna utworzyc katalogu zapisow!");
                return;
            }

            string fullPath = saveDir + "/" + fileName;

            using (StreamWriter gameSave = new StreamWriter(fullPath))
            {
                gameSave.WriteLine(gameState.human.GetHP());
                int itemsHuman = gameState.human.GetInventory().Count;
                gameSave.WriteLine(itemsHuman);
                foreach (int i in gameState.human.GetInventory())
                {
                    gameSave.WriteLine(i);
                }
                gameSave.WriteLine(gameState.human.GetSaws());
                gameSave.WriteLine(gameState.human.GetBeers());
                gameSave.WriteLine(gameState.human.GetMagnifiers());
                gameSave.WriteLine(gameState.human.GetInverters());
                gameSave.WriteLine(gameState.human.GetHandCuffs());
                gameSave.WriteLine(gameState.human.GetCellPhones());

                gameSave.WriteLine(gameState.computer.GetHP());
                int itemsComputer = gameState.computer.GetInventory().Count;
                gameSave.WriteLine(itemsComputer);
                foreach (int i in gameState.computer.GetInventory())
                {
                    gameSave.WriteLine(i);
                }
                gameSave.WriteLine(gameState.computer.GetSaws());
                gameSave.WriteLine(gameState.computer.GetBeers());
                gameSave.WriteLine(gameState.computer.GetMagnifiers());
                gameSave.WriteLine(gameState.computer.GetInverters());
                gameSave.WriteLine(gameState.computer.GetHandCuffs());
                gameSave.WriteLine(gameState.computer.GetCellPhones());

                gameSave.WriteLine(gameState.magazine.ShowFull());
                gameSave.WriteLine(gameState.magazine.ShowEmpty());
                gameSave.WriteLine(gameState.magazine.ShowBulletCount());

                gameSave.WriteLine(gameState.gameStateManager.GetStarter());
                gameSave.WriteLine(gameState.ai.GetDifficulty());
                gameSave.WriteLine(gameState.gameStateManager.GetChoice());
                gameSave.WriteLine(gameState.gameStateManager.GetShooter());
                gameSave.WriteLine(gameState.gameStateManager.GetTarget());
                gameSave.WriteLine(gameState.gameStateManager.GetItem());
                gameSave.WriteLine(gameState.gameStateManager.GetDamage());
                gameSave.WriteLine(gameState.gameStateManager.GetStateOfHandCuffs());

                foreach (int i in gameState.magazine.GetMagazine())
                    gameSave.WriteLine(i);
            }
        }
        catch (Exception e)
        {
            Console.WriteLine("Blad zapisywania: " + e.Message);
        }
    }
}
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;

public class LoadJSONManager : ILoadManager
{
    public void LoadGameState(GameState gameState, string fileName)
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

            string fullPath = saveDir + "/" + fileName;

            using (StreamReader gameSave = new StreamReader(fullPath))
            {
                string jsonContent = gameSave.ReadToEnd();
                JObject data = JObject.Parse(jsonContent);

                int hpHuman = (int)data["human_HP"];
                int hpComputer = (int)data["computer_HP"];
                int full = (int)data["magazine_full"];
                int empty = (int)data["magazine_empty"];
                int bulletCount = (int)data["magazine_bullet_count"];
                int Starter = (int)data["Starter"];
                int difficulty = (int)data["difficulty"];
                int choice = (int)data["choice"];
                int shooter = (int)data["shooter"];
                int target = (int)data["target"];
                int item = (int)data["item"];
                int damage = (int)data["damage"];
                bool wereHandCuffsUsed = (bool)data["WereHandCuffsUsed"];

                gameState.human.SetHP(hpHuman);
                gameState.computer.SetHP(hpComputer);
                gameState.magazine.SetFull(full);
                gameState.magazine.SetEmpty(empty);
                gameState.magazine.SetBulletCount(bulletCount);
                gameState.gameStateManager.SetStarter(Starter);
                gameState.ai.SetDifficulty(difficulty);
                gameState.gameStateManager.SetChoice(choice);
                gameState.gameStateManager.SetShooter(shooter);
                gameState.gameStateManager.SetTarget(target);
                gameState.gameStateManager.SetItem(item);
                gameState.gameStateManager.SetDamage(damage);
                gameState.gameStateManager.SetStateOfHandCuffs(wereHandCuffsUsed);

                List<int> humanInventory = new List<int>();
                foreach (int i in data["human_inventory"])
                {
                    humanInventory.Add(i);
                }
                gameState.human.SetInventory(humanInventory);

                gameState.human.SetSaws((int)data["human_Saws"]);
                gameState.human.SetBeers((int)data["human_Beers"]);
                gameState.human.SetMagnifiers((int)data["human_Magnifiers"]);
                gameState.human.SetInverters((int)data["human_Inverters"]);
                gameState.human.SetHandCuffs((int)data["human_HandCuffs"]);
                gameState.human.SetCellPhones((int)data["human_CellPhones"]);

                List<int> computerInventory = new List<int>();
                foreach (int i in data["computer_inventory"])
                {
                    computerInventory.Add(i);
                }
                gameState.computer.SetInventory(computerInventory);

                gameState.computer.SetSaws((int)data["computer_Saws"]);
                gameState.computer.SetBeers((int)data["computer_Beers"]);
                gameState.computer.SetMagnifiers((int)data["computer_Magnifiers"]);
                gameState.computer.SetInverters((int)data["computer_Inverters"]);
                gameState.computer.SetHandCuffs((int)data["computer_HandCuffs"]);
                gameState.computer.SetCellPhones((int)data["computer_CellPhones"]);

                List<int> newMagazine = new List<int>();
                for (int i = 0; i < bulletCount; i++)
                {
                    newMagazine.Add((int)data["magazine"][i]);
                }
                gameState.magazine.SetMagazine(newMagazine);
            }
        }
        catch (Newtonsoft.Json.JsonException e)
        {
            Console.WriteLine("Blad pliku JSON: " + e.Message);
        }
        catch (Exception e)
        {
            Console.WriteLine("Blad wczytywania: " + e.Message);
        }
    }
}
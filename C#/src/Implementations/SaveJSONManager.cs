using System;
using System.Collections.Generic;
using System.IO;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

public class SaveJSONManager : ISaveSyncManager
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

            JObject data = new JObject();
            data["human_HP"] = gameState.human.GetHP();

            JArray humanInventory = new JArray();
            foreach (int i in gameState.human.GetInventory())
                humanInventory.Add(i);
            data["human_inventory"] = humanInventory;

            data["human_Saws"] = gameState.human.GetSaws();
            data["human_Beers"] = gameState.human.GetBeers();
            data["human_Magnifiers"] = gameState.human.GetMagnifiers();
            data["human_Inverters"] = gameState.human.GetInverters();
            data["human_HandCuffs"] = gameState.human.GetHandCuffs();
            data["human_CellPhones"] = gameState.human.GetCellPhones();

            data["computer_HP"] = gameState.computer.GetHP();

            JArray computerInventory = new JArray();
            foreach (int i in gameState.computer.GetInventory())
                computerInventory.Add(i);
            data["computer_inventory"] = computerInventory;

            data["computer_Saws"] = gameState.computer.GetSaws();
            data["computer_Beers"] = gameState.computer.GetBeers();
            data["computer_Magnifiers"] = gameState.computer.GetMagnifiers();
            data["computer_Inverters"] = gameState.computer.GetInverters();
            data["computer_HandCuffs"] = gameState.computer.GetHandCuffs();
            data["computer_CellPhones"] = gameState.computer.GetCellPhones();

            data["magazine_full"] = gameState.magazine.ShowFull();
            data["magazine_empty"] = gameState.magazine.ShowEmpty();
            data["magazine_bullet_count"] = gameState.magazine.ShowBulletCount();

            data["Starter"] = gameState.gameStateManager.GetStarter();
            data["difficulty"] = gameState.ai.GetDifficulty();
            data["choice"] = gameState.gameStateManager.GetChoice();
            data["shooter"] = gameState.gameStateManager.GetShooter();
            data["target"] = gameState.gameStateManager.GetTarget();
            data["item"] = gameState.gameStateManager.GetItem();
            data["damage"] = gameState.gameStateManager.GetDamage();
            data["WereHandCuffsUsed"] = gameState.gameStateManager.GetStateOfHandCuffs();

            JArray magazineArray = new JArray();
            foreach (int i in gameState.magazine.GetMagazine())
                magazineArray.Add(i);
            data["magazine"] = magazineArray;

            using (StreamWriter gameSave = new StreamWriter(fullPath))
            {
                gameSave.Write(data.ToString(Newtonsoft.Json.Formatting.Indented));
            }
        }
        catch (JsonException e)
        {
            Console.WriteLine("Blad pliku JSON: " + e.Message);
        }
        catch (Exception e)
        {
            Console.WriteLine("Blad zapisywania: " + e.Message);
        }
    }
}
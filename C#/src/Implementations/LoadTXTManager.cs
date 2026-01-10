using System;
using System.Collections.Generic;
using System.IO;

public class LoadTXTManager : ILoadManager
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
                int bullet, hpHuman, itemsHuman, sawsHuman, beersHuman, magnifiersHuman, invertersHuman, handCuffsHuman, cellPhonesHuman,
                    hpComputer, itemsComputer, sawsComputer, beersComputer, magnifiersComputer, invertersComputer, handCuffsComputer, cellPhonesComputer,
                    full, empty, bulletCount, starter, difficulty, choice, shooter, target, item, itemHuman, itemComputer, damage;
                bool wereHandCuffsUsed;

                string line;

                line = gameSave.ReadLine();
                hpHuman = int.Parse(line);
                line = gameSave.ReadLine();
                itemsHuman = int.Parse(line);

                gameState.human.SetHP(hpHuman);
                List<int> newHumanInventory = new List<int>();
                for (int i = 0; i < itemsHuman; i++)
                {
                    line = gameSave.ReadLine();
                    itemHuman = int.Parse(line);
                    newHumanInventory.Add(itemHuman);
                }

                line = gameSave.ReadLine();
                sawsHuman = int.Parse(line);
                line = gameSave.ReadLine();
                beersHuman = int.Parse(line);
                line = gameSave.ReadLine();
                magnifiersHuman = int.Parse(line);
                line = gameSave.ReadLine();
                invertersHuman = int.Parse(line);
                line = gameSave.ReadLine();
                handCuffsHuman = int.Parse(line);
                line = gameSave.ReadLine();
                cellPhonesHuman = int.Parse(line);

                gameState.human.SetInventory(newHumanInventory);
                gameState.human.SetSaws(sawsHuman);
                gameState.human.SetBeers(beersHuman);
                gameState.human.SetMagnifiers(magnifiersHuman);
                gameState.human.SetInverters(invertersHuman);
                gameState.human.SetHandCuffs(handCuffsHuman);
                gameState.human.SetCellPhones(cellPhonesHuman);

                line = gameSave.ReadLine();
                hpComputer = int.Parse(line);
                line = gameSave.ReadLine();
                itemsComputer = int.Parse(line);

                gameState.computer.SetHP(hpComputer);
                List<int> newComputerInventory = new List<int>();
                for (int i = 0; i < itemsComputer; i++)
                {
                    line = gameSave.ReadLine();
                    itemComputer = int.Parse(line);
                    newComputerInventory.Add(itemComputer);
                }

                line = gameSave.ReadLine();
                sawsComputer = int.Parse(line);
                line = gameSave.ReadLine();
                beersComputer = int.Parse(line);
                line = gameSave.ReadLine();
                magnifiersComputer = int.Parse(line);
                line = gameSave.ReadLine();
                invertersComputer = int.Parse(line);
                line = gameSave.ReadLine();
                handCuffsComputer = int.Parse(line);
                line = gameSave.ReadLine();
                cellPhonesComputer = int.Parse(line);

                gameState.computer.SetInventory(newComputerInventory);
                gameState.computer.SetSaws(sawsComputer);
                gameState.computer.SetBeers(beersComputer);
                gameState.computer.SetMagnifiers(magnifiersComputer);
                gameState.computer.SetInverters(invertersComputer);
                gameState.computer.SetHandCuffs(handCuffsComputer);
                gameState.computer.SetCellPhones(cellPhonesComputer);

                line = gameSave.ReadLine();
                full = int.Parse(line);
                line = gameSave.ReadLine();
                empty = int.Parse(line);
                line = gameSave.ReadLine();
                bulletCount = int.Parse(line);
                line = gameSave.ReadLine();
                starter = int.Parse(line);
                line = gameSave.ReadLine();
                difficulty = int.Parse(line);
                line = gameSave.ReadLine();
                choice = int.Parse(line);
                line = gameSave.ReadLine();
                shooter = int.Parse(line);
                line = gameSave.ReadLine();
                target = int.Parse(line);
                line = gameSave.ReadLine();
                item = int.Parse(line);
                line = gameSave.ReadLine();
                damage = int.Parse(line);
                line = gameSave.ReadLine();
                wereHandCuffsUsed = bool.Parse(line);

                gameState.magazine.SetFull(full);
                gameState.magazine.SetEmpty(empty);
                gameState.magazine.SetBulletCount(bulletCount);

                gameState.gameStateManager.SetStarter(starter);
                gameState.ai.SetDifficulty(difficulty);
                gameState.gameStateManager.SetChoice(choice);
                gameState.gameStateManager.SetShooter(shooter);
                gameState.gameStateManager.SetTarget(target);
                gameState.gameStateManager.SetItem(item);
                gameState.gameStateManager.SetDamage(damage);
                gameState.gameStateManager.SetStateOfHandCuffs(wereHandCuffsUsed);

                List<int> newMagazine = new List<int>();
                for (int i = 0; i < bulletCount; i++)
                {
                    line = gameSave.ReadLine();
                    bullet = int.Parse(line);
                    newMagazine.Add(bullet);
                }

                gameState.magazine.SetMagazine(newMagazine);
            }
        }
        catch (Exception e)
        {
            Console.WriteLine("Blad wczytywania: " + e.Message);
        }
    }
}
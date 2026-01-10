using System;
using System.Collections.Generic;
using System.Linq;

public class MagazineManager : IMagazineManager
{
    private int full = 0;
    private int empty = 0;
    private int bulletCount = 0;
    private List<int> magazine = new List<int>();
    private GameConfig gameConfig;
    private Random rand = new Random();

    public MagazineManager(GameConfig gameConfig)
    {
        this.gameConfig = gameConfig;
    }

    public void Load()
    {
        bulletCount = rand.Next(gameConfig.minBullets, gameConfig.maxBullets + 1);
        magazine = new List<int>(bulletCount);

        for (int i = 0; i < bulletCount; i++)
        {
            magazine.Add(rand.Next(gameConfig.numberOfBulletTypes));
        }
    }

    public void ShowBullets()
    {
        foreach (int bullet in magazine)
        {
            Console.WriteLine(bullet == (int)GameEnums.Bullet.FULL ? "Pelna - 1" : "Pusta - 0");
        }
    }

    public bool CheckBulletType()
    {
        return magazine[0] == (int)GameEnums.Bullet.FULL;
    }

    public void CheckBullets()
    {
        full = magazine.Count(bullet => bullet == (int)GameEnums.Bullet.FULL);
        empty = magazine.Count - full;
    }

    public int ShowFull() { return full; }
    public int ShowEmpty() { return empty; }

    public void DecreaseFullCount() { if (full > 0) full--; }
    public void DecreaseEmptyCount() { if (empty > 0) empty--; }

    public int ShowBulletCount() { return magazine.Count; }

    public void SetBulletCount(int newBulletCount)
    {
        bulletCount = newBulletCount;
        if (magazine.Count > bulletCount)
            magazine.RemoveRange(bulletCount, magazine.Count - bulletCount);
        else
            magazine.AddRange(new int[bulletCount - magazine.Count]);
    }

    public void SetFull(int newFull) { full = newFull; }
    public void SetEmpty(int newEmpty) { empty = newEmpty; }

    public void DecreaseBulletCount()
    {
        if (bulletCount == 0) return;
        magazine.RemoveAt(0);
        bulletCount = magazine.Count;
    }

    public bool IsOutOfBullets() { return IsEmpty(); }

    public void Reload()
    {
        magazine.Clear();
        bulletCount = 0;
        empty = 0;
        full = 0;
        Load();
        CheckBullets();
    }

    public bool IsEmptySlot()
    {
        if (magazine.Count == 0) throw new Exception("Magazynek jest pusty!");
        return magazine[0] == (int)GameEnums.Bullet.EMPTY;
    }

    public bool IsEmpty() { return bulletCount == 0; }

    public List<int> GetMagazine() { return magazine; }

    public void SetMagazine(List<int> newMagazine)
    {
        magazine = newMagazine;
        bulletCount = magazine.Count;
    }

    public double CalculateHitProbability()
    {
        if (magazine.Count == 0) return 0.0;
        return (double)full / bulletCount;
    }

    public bool HasEmptyBullets()
    {
        return magazine.Any(bullet => bullet == (int)GameEnums.Bullet.EMPTY);
    }

    public void InvertBulletType()
    {
        if (CheckBulletType())
            magazine[0] = (int)GameEnums.Bullet.EMPTY;
        else
            magazine[0] = (int)GameEnums.Bullet.FULL;
    }

    public int GetMagazineSize() { return magazine.Count; }

    public bool CheckBulletTypeCellPhone(int bullet)
    {
        return magazine[bullet] == (int)GameEnums.Bullet.FULL;
    }
}
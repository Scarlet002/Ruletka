using System.Collections.Generic;

public interface IMagazineManager
{
    void Load();
    void ShowBullets();
    bool CheckBulletType();
    void CheckBullets();
    int ShowFull();
    int ShowEmpty();
    void SetFull(int newFull);
    void SetEmpty(int newEmpty);
    void DecreaseFullCount();
    void DecreaseEmptyCount();
    int ShowBulletCount();
    void SetBulletCount(int newBulletCount);
    void DecreaseBulletCount();
    bool IsOutOfBullets();
    void Reload();
    bool IsEmptySlot();
    bool IsEmpty();
    List<int> GetMagazine();
    void SetMagazine(List<int> newMagazine);
    double CalculateHitProbability();
    bool HasEmptyBullets();
    void InvertBulletType();
    int GetMagazineSize();
    bool CheckBulletTypeCellPhone(int bullet);
}
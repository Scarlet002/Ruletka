#pragma once
#include "ForwardDeclarations.h"
#include "GameEnums.h"
#include "IMagazineManager.h"
#include <vector>
#include <stdexcept>
#include <algorithm>

using std::vector;

class MagazineManager : public IMagazineManager
{
private:
    int full = 0;
    int empty = 0;
    int bulletCount = 0;
    vector<int> magazine;

public:

    MagazineManager() {};

    void Load() override;
    void ShowBullets() const override;
    bool CheckBulletType() const override;
    void CheckBullets() override;
    int ShowFull() const override;
    int ShowEmpty() const override;
    void DecreaseFullCount() override;
    void DecreaseEmptyCount() override;
    int ShowBulletCount() const override;
    void SetBulletCount(int newBulletCount) override;
    void SetFull(int newFull) override;
    void SetEmpty(int newEmpty) override;
    void DecreaseBulletCount() override;
    bool IsOutOfBullets() const override;
    void Reload() override;
    bool IsEmptySlot() const override;
    bool IsEmpty() const override;
    const vector<int>& GetMagazine() const override;
    void SetMagazine(const vector<int>& newMagazine) override;
    double CalculateHitProbability() const override;
    bool HasEmptyBullets() const override;

    ~MagazineManager() {};
};

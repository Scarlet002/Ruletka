#pragma once
#include "ForwardDeclarations.h"
#include <vector>

using std::vector;

class IMagazineManager
{
public:

    virtual void Load() = 0;
    virtual void ShowBullets() const = 0;
    virtual bool CheckBulletType() const = 0;
    virtual void CheckBullets() = 0;
    virtual int ShowFull() const = 0;
    virtual int ShowEmpty() const = 0;
    virtual void SetFull(int newFull) = 0;
    virtual void SetEmpty(int newEmpty) = 0;
    virtual void DecreaseFullCount() = 0;
    virtual void DecreaseEmptyCount() = 0;
    virtual int ShowBulletCount() const = 0;
    virtual void SetBulletCount(int newBulletCount) = 0;
    virtual void DecreaseBulletCount() = 0;
    virtual bool IsOutOfBullets() const = 0;
    virtual void Reload() = 0;
    virtual bool IsEmptySlot() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual const vector<int>& GetMagazine() const = 0;
    virtual void SetMagazine(const vector<int>& newMagazine) = 0;
    virtual double CalculateHitProbability() const = 0;
    virtual bool HasEmptyBullets() const = 0;

    virtual ~IMagazineManager() = default;
};
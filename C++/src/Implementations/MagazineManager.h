#pragma once
#include "ForwardDeclarations.h"
#include "GameEnums.h"
#include "IMagazineManager.h"
#include "GameConfig.h"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cstdint>

class MagazineManager : public IMagazineManager
{
private:
    std::vector<uint8_t> magazine;
    uint8_t full = GameConfig::minBulletsCount;
    uint8_t empty = GameConfig::minBulletsCount;
    uint8_t bulletCount = GameConfig::minBulletsCount;
public:
    explicit MagazineManager();

    void Load() override;
    void ShowBullets() const override;
    bool CheckBulletType() const override;
    void CheckBullets() override;
    int ShowFull() const override;
    int ShowEmpty() const override;
    void DecreaseFullCount() override;
    void DecreaseEmptyCount() override;
    int ShowBulletCount() const override;
    void SetFull(int newFull) override;
    void SetEmpty(int newEmpty) override;
    void DecreaseBulletCount() override;
    bool IsOutOfBullets() const override;
    void Reload() override;
    bool IsEmptySlot() const override;
    bool IsEmpty() const override;
	void SetBulletCount(int newBulletCount) override;
    const std::vector<uint8_t>& GetMagazine() const override;
    void SetMagazine(const std::vector<uint8_t>& newMagazine) override;
    double CalculateHitProbability() const override;
    bool HasEmptyBullets() const override;
    void InvertBulletType() override;
    int GetMagazineSize() const override;
    bool CheckBulletTypeCellPhone(int bullet) const override;
};

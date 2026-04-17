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

    inline void DecreaseBulletCount();
    inline void DecreaseFullCount();
    inline void DecreaseEmptyCount();
	inline void ValidateMagazineSize() const;
public:
    explicit MagazineManager();

    void UpdateMagazineState(uint8_t bullet) override;
    void CheckBullets() override;
    uint8_t GetFull() const override;
    uint8_t GetEmpty() const override;
    void Reload() override;
    bool IsEmpty() const override;
    const std::vector<uint8_t>& GetMagazine() const override;
    void SetMagazine(const std::vector<uint8_t>& newMagazine) override;
    float CalculateHitProbability() const override;
    void InvertBulletType() override;
    uint8_t GetMagazineSize() const override;
    bool CheckBulletType(uint8_t bullet) const override;
};

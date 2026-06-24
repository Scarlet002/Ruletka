#pragma once
#include "ForwardDeclarations.h"
#include "GameEnums.h"
#include "Magazine.h"
#include "GameConfig.h"
#include <deque>
#include <stdexcept>
#include <algorithm>
#include <cstdint>

class ShotgunMagazine : public Magazine
{
private:
    std::deque<uint8_t> magazine;
    uint8_t full = GameConfig::minBullets;
    uint8_t empty = GameConfig::minBullets;
    float hitProbability = 0.f;

    void DecreaseBulletCount();
    void DecreaseFullCount();
    void DecreaseEmptyCount();
	void ValidateMagazineSize() const;
public:
    explicit ShotgunMagazine();

    void UpdateMagazineState(uint8_t bullet) override;
    void CheckBullets() override;
    uint8_t GetFull() const noexcept override;
    uint8_t GetEmpty() const noexcept override;
    void Reload() override;
    bool IsEmpty() const noexcept override;
    const std::deque<uint8_t>& GetMagazine() const noexcept override;
    void SetMagazine(const std::deque<uint8_t>& newMagazine) override;
    float CalculateHitProbability() const noexcept override;
    void InvertBulletType() override;
    uint8_t GetMagazineSize() const noexcept override;
    bool CheckBulletType(uint8_t bullet) const noexcept override;
    void SetHitProbability(float newProbability) override;
    float GetHitProbability() const noexcept override;
};

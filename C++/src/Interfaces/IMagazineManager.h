#pragma once
#include <vector>
#include <cstdint>

class IMagazineManager
{
public:
    virtual void UpdateMagazineState(uint8_t bullet) = 0;
    virtual void CheckBullets() = 0;
    virtual uint8_t GetFull() const = 0;
    virtual uint8_t GetEmpty() const = 0;
    virtual void Reload() = 0;
    virtual bool IsEmpty() const = 0;
    virtual const std::vector<uint8_t>& GetMagazine() const = 0;
    virtual void SetMagazine(const std::vector<uint8_t>& newMagazine) = 0;
    virtual float CalculateHitProbability() const = 0;
    virtual void InvertBulletType() = 0;
    virtual uint8_t GetMagazineSize() const = 0;
    virtual bool CheckBulletType(uint8_t bullet) const = 0;

    virtual ~IMagazineManager() = default;
};
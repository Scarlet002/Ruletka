#pragma once
#include <deque>
#include <cstdint>

class Magazine
{
protected:
	Magazine() = default;
public:
    Magazine(const Magazine&) = delete;
    Magazine& operator=(const Magazine&) = delete;

    Magazine(Magazine&&) = delete;
    Magazine& operator=(Magazine&&) = delete;

    virtual void UpdateMagazineState(uint8_t bullet) = 0;
    virtual void CheckBullets() = 0;
    [[nodiscard]] virtual uint8_t GetFull() const noexcept = 0;
    [[nodiscard]] virtual uint8_t GetEmpty() const noexcept = 0;
    virtual void Reload() = 0;
    [[nodiscard]] virtual bool IsEmpty() const noexcept = 0;
    [[nodiscard]] virtual const std::deque<uint8_t>& GetMagazine() const noexcept = 0;
    virtual void SetMagazine(const std::deque<uint8_t>& newMagazine) = 0;
    [[nodiscard]] virtual float CalculateHitProbability() const noexcept = 0;
    virtual void InvertBulletType() = 0;
    [[nodiscard]] virtual uint8_t GetMagazineSize() const noexcept = 0;
    [[nodiscard]] virtual bool CheckBulletType(uint8_t bullet) const noexcept = 0;
    virtual void SetHitProbability(float newProbability) = 0;
    [[nodiscard]] virtual float GetHitProbability() const noexcept = 0;

    virtual ~Magazine() = default;
};
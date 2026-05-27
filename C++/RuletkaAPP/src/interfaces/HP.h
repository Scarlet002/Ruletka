#pragma once
#include <cstdint>

class HP
{
protected:
	HP() = default;
public:
    HP(const HP&) = delete;
    HP& operator=(const HP&) = delete;

    HP(HP&&) = delete;
    HP& operator=(HP&&) = delete;

	virtual void SetHP(uint8_t newHP) = 0;

    virtual void LoseHP(uint8_t damage) = 0;

    virtual void RegainHP() = 0;

    virtual void ResetHP() = 0;

    [[nodiscard]] virtual int8_t GetHP() const noexcept = 0;

    virtual ~HP() = default;
};
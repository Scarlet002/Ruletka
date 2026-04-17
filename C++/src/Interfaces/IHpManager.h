#pragma once
#include <cstdint>

class IHpManager
{
public:
	virtual void SetHP(uint8_t newHP) = 0;
    virtual void LoseHP(uint8_t damage) = 0;
    virtual void RegainHP() = 0;
    virtual void ResetHP() = 0;
    virtual int8_t GetHP() const = 0;

    virtual ~IHpManager() = default;
};
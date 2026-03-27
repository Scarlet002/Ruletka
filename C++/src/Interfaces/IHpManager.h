#pragma once

class IHpManager
{
public:
	virtual void SetHP(int newHP) = 0;
    virtual void LoseHP(int damage) = 0;
    virtual void RegainHP() = 0;
    virtual void ResetHP() = 0;
    virtual int GetHP() const = 0;

    virtual ~IHpManager() = default;
};
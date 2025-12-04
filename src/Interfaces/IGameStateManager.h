#pragma once
#include "ForwardDeclarations.h"

class IGameStateManager
{
public:

    virtual int SetItem(int newItem) = 0;
    virtual int SetStarter(int newStarter) = 0;
    virtual int SetChoice(int newChoice) = 0;
    virtual int SetTarget(int newTarget) = 0;
    virtual int SetShooter(int newShooter) = 0;
    virtual int SetDamage(int newDamage) = 0;
    virtual void SetStateOfHandCuffs(bool newState) = 0;
    virtual int GetStarter() const = 0;
    virtual int GetChoice() const = 0;
    virtual int GetTarget() const = 0;
    virtual int GetShooter() const = 0;
    virtual int GetDamage() const = 0;
    virtual int GetItem() const = 0;
    virtual bool GetStateOfHandCuffs() const = 0;
    virtual int RandomizeStarter() = 0;
    virtual void ResetDamage() = 0;

    virtual ~IGameStateManager() = default;
};

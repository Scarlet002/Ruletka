#pragma once
#include "ForwardDeclarations.h"
#include <string>

using std::string;

class IGameStateManager
{
public:

    virtual void SetItem(int newItem) = 0;
    virtual void SetStarter(int newStarter) = 0;
    virtual void SetChoice(int newChoice) = 0;
    virtual void SetTarget(int newTarget) = 0;
    virtual void SetShooter(int newShooter) = 0;
    virtual void SetDamage(int newDamage) = 0;
    virtual void SetStateOfHandCuffs(bool newState) = 0;
    virtual void SetLogLine(string newLogLine) = 0;
    virtual int GetStarter() const = 0;
    virtual int GetChoice() const = 0;
    virtual int GetTarget() const = 0;
    virtual int GetShooter() const = 0;
    virtual int GetDamage() const = 0;
    virtual int GetItem() const = 0;
    virtual bool GetStateOfHandCuffs() const = 0;
    virtual string GetLogLine() const = 0;
    virtual int RandomizeStarter() = 0;
    virtual void ResetDamage() = 0;

    virtual ~IGameStateManager() = default;
};
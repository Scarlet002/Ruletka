#pragma once
#include "ForwardDeclarations.h"

class IGameStateManager
{
public:

    virtual int SetStarter(int newStarter) = 0;
    virtual int SetChoice(int newChoice) = 0;
    virtual int SetTarget(int newTarget) = 0;
    virtual int SetShooter(int newShooter) = 0;
    virtual int GetStarter() const = 0;
    virtual int GetChoice() const = 0;
    virtual int GetTarget() const = 0;
    virtual int GetShooter() const = 0;
    virtual int RundomizeStarter() = 0;

    virtual ~IGameStateManager() = default;
};

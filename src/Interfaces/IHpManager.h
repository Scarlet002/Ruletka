#pragma once
#include "ForwardDeclarations.h"

class IHpManager
{
public:

    virtual void LoseHP() = 0;
    virtual void RegainHP() = 0;
    virtual void ResetHP() = 0;
    virtual int GetHP() const = 0;
    virtual void SetHP(int newHP) = 0;

    virtual ~IHpManager() = default;
};
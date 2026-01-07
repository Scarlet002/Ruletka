#pragma once
#include "ForwardDeclarations.h"

class IHpManager
{
public:

    IHpManager() = default;

    virtual void LoseHP(GameState& gameState) = 0;
    virtual void RegainHP() = 0;
    virtual void ResetHP() = 0;
    virtual int GetHP() const = 0;
    virtual void SetHP(int newHP) = 0;

    virtual ~IHpManager() = default;
};
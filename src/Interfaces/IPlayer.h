#pragma once
#include "ForwardDeclarations.h"

struct GameState;

class IPlayer
{
public:

    virtual void LoseHP() = 0;
    virtual void RegainHP() = 0;
    virtual void ResetHP() = 0;
    virtual int GetHP() const = 0;
    virtual void SetHP(int newHP) = 0;
    virtual bool isAlive() const = 0;
    virtual bool IsHuman() const = 0;
    virtual bool IsComputer() const = 0;
    virtual int MakeDecision(GameState& gameState) const = 0;
    virtual void Shoot(GameState& gameState) = 0;

    virtual ~IPlayer() = default;
};
#pragma once
#include "GameState.h"
#include "ForwardDeclarations.h"

class IAiManager
{
public:

    IAiManager() = default;

    virtual int SetDifficulty(int newDifficulty) = 0;
    virtual int GetDifficulty() const = 0;
    virtual void EasyAI(GameState& gameState) const = 0;
    virtual void NormalAI(GameState& gameState) const = 0;
    virtual void HardAI(GameState& gameState) const = 0;

    virtual ~IAiManager() = default;
};

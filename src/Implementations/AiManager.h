#pragma once
#include "IAiManager.h"
#include "ForwardDeclarations.h"
#include "GameEnums.h"

class AiManager : public IAiManager
{
private:
    int difficulty = GameEnums::NORMAL;
public:
    AiManager() {};

    int SetDifficulty(int newDifficulty) override;
    int GetDifficulty() const override;
    void EasyAI(GameState& gameState) const override;
    void NormalAI(GameState& gameState) const override;
    void HardAI(GameState& gameState) const override;

    ~AiManager() {};
};
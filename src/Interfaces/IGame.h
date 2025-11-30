#pragma once
#include "GameState.h"
#include "Player.h"
#include "UiManager.h"
#include "ForwardDeclarations.h"

class IGame
{
public:

    virtual void NewRound(GameState& gameState, const UiManager& ui) = 0;
    virtual bool WhoWon(const Player& human, const Player& computer, const UiManager& ui) = 0;
    virtual void StartGame() = 0;

    virtual ~IGame() = default;
};

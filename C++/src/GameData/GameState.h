#pragma once
#include "IPlayer.h"
#include "IMagazineManager.h"
#include "ITurnManager.h"
#include <memory>

struct GameState 
{
    GameState();

    std::unique_ptr<IPlayer> human;
    std::unique_ptr<IPlayer> computer;
    std::unique_ptr<IMagazineManager> magazine;
    std::unique_ptr<ITurnManager> turn;

    void CopyStateToSnapshot(const GameState& state);
};
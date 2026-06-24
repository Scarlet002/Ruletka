#pragma once
#include "ForwardDeclarations.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "DecisionState.h"
#include "GameLoopState.h"
#include "Action.h"
#include <string>
#include <memory>
#include <thread>
#include <chrono>

class Restart : public Action
{
private:
    std::shared_ptr<IGameState> gs;
    std::shared_ptr<UI> ui;
public:
    Restart(std::shared_ptr<IGameState> gs
        , std::shared_ptr<UI> ui)
        : gs(gs)
        , ui(ui) {}

	void Execute() override
	{
        if (gs->GetDecisionState().GetChoice() == GameEnums::RESTART_NO)
        {
            gs->GetGameLoopState().SetStateOfGameLoop(false);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        if (gs->GetDecisionState().GetChoice() == GameEnums::RESTART_YES)
        {
            return;
        }
	}
};
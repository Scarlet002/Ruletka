#pragma once
#include "ForwardDeclarations.h"
#include "IGameState.h"
#include "GameLoopState.h"
#include "Action.h"
#include <memory>
#include <thread>
#include <chrono>

class Exit : public Action
{
private:
	std::shared_ptr<IGameState> gs;
public:
	Exit(std::shared_ptr<IGameState> gs) : gs(gs) {}

	void Execute() override
	{
		gs->GetGameLoopState().SetStateOfGameLoop(false);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
};
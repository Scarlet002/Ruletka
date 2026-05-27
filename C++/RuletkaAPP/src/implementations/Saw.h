#pragma once
#include "ForwardDeclarations.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "GameConfig.h"
#include "IPlayer.h"
#include "Logger.h"
#include "DecisionState.h"
#include "GameLoopState.h"
#include "ItemState.h"
#include "Action.h"
#include <string>
#include <memory>

class Saw : public Action
{
private:
	std::shared_ptr<IGameState> gs;
	std::shared_ptr<Logger> logger;
public:
	Saw(std::shared_ptr<IGameState> gs
		, std::shared_ptr<Logger> logger)
		: gs(gs)
		, logger(logger) {}

	void Execute() override
	{
		IPlayer& currentPlayer = gs->GetGameLoopState().GetStarter() == GameEnums::HUMAN
							   ? gs->GetHuman() : gs->GetComputer();

		std::string logLine = "";
		if (currentPlayer.GetInventory().GetItemCount(GameEnums::SAW) == 0)
		{
			logLine = currentPlayer.GetName() + " nie ma tego przedmiotu!";
		}
		else
		{
			currentPlayer.GetInventory().UseItem(gs->GetDecisionState().GetChoice());
			gs->GetItemState().SetDamage(GameConfig::sawDamage);
			logLine = currentPlayer.GetName() + " uzyl pily! Obrazenia zwiekszone";
		}
		logger->UpdateLog(logLine);
	}
};
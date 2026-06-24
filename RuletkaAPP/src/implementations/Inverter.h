#pragma once
#include "ForwardDeclarations.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "IPlayer.h"
#include "Logger.h"
#include "GameLoopState.h"
#include "DecisionState.h"
#include "Magazine.h"
#include "Action.h"
#include <string>
#include <memory>

class Inverter : public Action
{
private:
	std::shared_ptr<IGameState> gs;
	std::shared_ptr<Logger> logger;
public:
    Inverter(std::shared_ptr<IGameState> gs
        , std::shared_ptr<Logger> logger)
        : gs(gs)
        , logger(logger) {}

	void Execute() override
	{
        IPlayer& currentPlayer = gs->GetGameLoopState().GetStarter() == GameEnums::HUMAN
                               ? gs->GetHuman() : gs->GetComputer();
		
        std::string logLine = "";
        if (currentPlayer.GetInventory().GetItemCount(GameEnums::INVERTER) <= 0)
        {
            logLine = currentPlayer.GetName() + " nie ma tego przedmiotu!";
        }
        else
        {
            currentPlayer.GetInventory().UseItem(gs->GetDecisionState().GetChoice());
            gs->GetMagazine().InvertBulletType();
            logLine = currentPlayer.GetName() + " uzyl inwertera!";
        }
        logger->UpdateLog(logLine);
	}
};
#pragma once
#include "ForwardDeclarations.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "IPlayer.h"
#include "Logger.h"
#include "GameLoopState.h"
#include "DecisionState.h"
#include "Magazine.h"
#include "ItemState.h"
#include "Action.h"
#include <string>
#include <memory>

class Magnifier : public Action
{
private:
    std::shared_ptr<IGameState> gs;
	std::shared_ptr<Logger> logger;
public:
    Magnifier(std::shared_ptr<IGameState> gs
        , std::shared_ptr<Logger> logger)
        : gs(gs)
		, logger(logger) {}

	void Execute() override 
	{
        IPlayer& currentPlayer = gs->GetGameLoopState().GetStarter() == GameEnums::HUMAN
                               ? gs->GetHuman() : gs->GetComputer();

        std::string logLine = "";
        if (currentPlayer.GetInventory().GetItemCount(GameEnums::MAGNIFIER) == 0)
        {
            logLine = currentPlayer.GetName() + " nie ma tego przedmiotu!";
        }
        else
        {
            currentPlayer.GetInventory().UseItem(gs->GetDecisionState().GetChoice());
            logLine = currentPlayer.GetName() + " uzyl lupy! ";
            gs->GetMagazine().SetHitProbability(gs->GetMagazine().CheckBulletType(GameEnums::FIRST_BULLET));
            gs->GetItemState().SetStateOfMagnifier(true);
            if (currentPlayer.GetType())
            {
                logLine += "Pierwszy pocisk jest ";
                if (gs->GetMagazine().CheckBulletType(GameEnums::FIRST_BULLET)) 
                { 
                    logLine += "pelny!";
                }
                else { logLine += "pusty!"; }
            }
        }
        logger->UpdateLog(logLine);
	}
};
#pragma once
#include "ForwardDeclarations.h"
#include "GameLoopState.h"
#include "DecisionState.h"
#include "Action.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "IPlayer.h"
#include "Logger.h"
#include <string>
#include <memory>

class Handcuffs : public Action
{
private:
    std::shared_ptr<IGameState> gs;
    std::shared_ptr<Logger> logger;
public:
	Handcuffs(std::shared_ptr<IGameState> gs
        , std::shared_ptr<Logger> logger)
        : gs(gs)
		, logger(logger) {}

	void Execute() override
	{
        IPlayer& currentPlayer = gs->GetGameLoopState().GetStarter() == GameEnums::HUMAN
                               ? gs->GetHuman() : gs->GetComputer();

        std::string logLine = "";
        if (currentPlayer.GetInventory().GetItemCount(GameEnums::HANDCUFFS) == 0)
        {
            logLine = currentPlayer.GetName() + " nie ma tego przedmiotu!";
        }
        else
        {
            currentPlayer.GetInventory().UseItem(gs->GetDecisionState().GetChoice());
            gs->GetItemState().SetStateOfHandCuffs(GameEnums::ITEM_USED);
            logLine = currentPlayer.GetName() + " uzyl kajdanek!";
        }
        logger->UpdateLog(logLine);
	}
};
#pragma once
#include "ForwardDeclarations.h"
#include "Action.h"
#include "IGameState.h"
#include "ItemState.h"
#include "DecisionState.h"
#include "GameLoopState.h"
#include "GameEnums.h"
#include "GameConfig.h"
#include "IPlayer.h"
#include "Logger.h"
#include "RNG.h"
#include "Magazine.h"
#include <string>
#include <memory>

class Cellphone : public Action
{
private:
	std::shared_ptr<IGameState> gs;
	std::shared_ptr<Logger> logger;
public:
    Cellphone(std::shared_ptr<IGameState> gs
        , std::shared_ptr<Logger> logger)
		: gs(gs)
        , logger(logger) {}

	void Execute() override
	{
        IPlayer& currentPlayer = gs->GetGameLoopState().GetStarter() == GameEnums::HUMAN
                               ? gs->GetHuman() : gs->GetComputer();

        std::string logLine = "";
        if (currentPlayer.GetInventory().GetItemCount(GameEnums::CELLPHONE) == 0)
        {
            logLine = currentPlayer.GetName() + " nie ma tego przedmiotu!";
        }
        else
        {
            currentPlayer.GetInventory().UseItem(gs->GetDecisionState().GetChoice());
            logLine = currentPlayer.GetName() + " uzyl telefonu! ";
            gs->GetMagazine().SetHitProbability(gs->GetMagazine().CheckBulletType(GameEnums::FIRST_BULLET));
            gs->GetItemState().SetStateOfCellPhone(true);
            if (currentPlayer.GetType())
            {
                uint8_t size = gs->GetMagazine().GetMagazineSize();

                if (size > 0) { size--; } //<- tu try chatch trzeba zrobic
                else { return; }

                uint8_t randomBullet = RNG::GetRN<uint8_t>(GameConfig::minBullets, size);

                if (gs->GetMagazine().CheckBulletType(randomBullet))
                {
                    logLine += std::to_string(randomBullet + 1) + " pocisk jest pelny!";
                }
                else { logLine += std::to_string(randomBullet + 1) + " pocisk jest pusty!"; }
            }
        }
        logger->UpdateLog(logLine);
	}
};
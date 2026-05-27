#pragma once
#include "ForwardDeclarations.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "IPlayer.h"
#include "Logger.h"
#include "GameLoopState.h"
#include "ItemState.h"
#include "Magazine.h"
#include "Action.h"
#include <string>
#include <memory>

class Heal : public Action
{
private:
    std::shared_ptr<IGameState> gs;
	std::shared_ptr<Logger> logger;
public:
    Heal(std::shared_ptr<IGameState> gs
        , std::shared_ptr<Logger> logger)
        : gs(gs)
        , logger(logger) {}

	void Execute() override
	{
        IPlayer& currentPlayer = gs->GetGameLoopState().GetStarter() == GameEnums::HUMAN
			                 ? gs->GetHuman() : gs->GetComputer();

        if (gs->GetMagazine().CheckBulletType(GameEnums::FIRST_BULLET))
        {
            uint8_t damage = gs->GetItemState().GetDamage();
            currentPlayer.GetHP().LoseHP(damage);
            std::string logLine = currentPlayer.GetName() + " stracil " + std::to_string(damage) + " HP!";
            logger->UpdateLog(logLine);
        }
        else
        {
            currentPlayer.GetHP().RegainHP();
            std::string logLine = currentPlayer.GetName() + " odzyskal 1 HP!";
            logger->UpdateLog(logLine);
        }
        gs->GetMagazine().UpdateMagazineState(GameEnums::FIRST_BULLET);
        gs->GetItemState().SetDamage(GameConfig::defaultDamage);
        gs->GetItemState().SetStateOfCellPhone(false);
        gs->GetItemState().SetStateOfMagnifier(false);

        if (!gs->GetItemState().GetStateOfHandCuffs())
        {
            if (currentPlayer.GetType())
            {
                gs->GetGameLoopState().SetStarter(GameEnums::COMPUTER);
            }
            else { gs->GetGameLoopState().SetStarter(GameEnums::HUMAN); }
        }
        else { gs->GetItemState().SetStateOfHandCuffs(GameEnums::ITEM_NOT_USED); }
	}
};
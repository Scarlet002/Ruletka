#pragma once
#include "ForwardDeclarations.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "GameConfig.h"
#include "IPlayer.h"
#include "Logger.h"
#include "ItemState.h"
#include "GameLoopState.h"
#include "Magazine.h"
#include "Action.h"
#include <string>
#include <memory>

class Shoot : public Action
{
private:
    std::shared_ptr<IGameState> gs;
    std::shared_ptr<Logger> logger;
public:
    Shoot(std::shared_ptr<IGameState> gs
        , std::shared_ptr<Logger> logger)
        : gs(gs)
        , logger(logger) {}

	void Execute() override
	{
        IPlayer& currentPlayer = gs->GetGameLoopState().GetStarter() == GameEnums::HUMAN
                               ? gs->GetHuman() : gs->GetComputer();

        IPlayer& currentEnemy = gs->GetGameLoopState().GetStarter() == GameEnums::HUMAN
                              ? gs->GetComputer() : gs->GetHuman();

        std::string logLine = "";
        if (gs->GetMagazine().CheckBulletType(GameEnums::FIRST_BULLET))
        {
            uint8_t damage = gs->GetItemState().GetDamage();
            currentEnemy.GetHP().LoseHP(damage);
            logLine = currentPlayer.GetName() + " trafil " + currentEnemy.GetName() 
                    + " i zadal mu " + std::to_string(damage) + " obrazen!";
        }
        else { logLine = currentPlayer.GetName() + " nie trafil " + currentEnemy.GetName() + "!"; }
        logger->UpdateLog(logLine);
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
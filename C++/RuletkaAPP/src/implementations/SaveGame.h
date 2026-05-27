#pragma once
#include "ForwardDeclarations.h"
#include "IGameState.h"
#include "SerializationManager.h"
#include "GameEnums.h"
#include "GameConfig.h"
#include "IPlayer.h"
#include "Logger.h"
#include "UI.h"
#include "DecisionState.h"
#include "Magazine.h"
#include "Action.h"
#include <string>
#include <memory>

class SaveGame : public Action
{
private:
    std::shared_ptr<IGameState> gs;
    std::shared_ptr<Logger> logger;
    std::shared_ptr<SerializationManager> sm;
	std::shared_ptr<UI> ui;
public:
    SaveGame(std::shared_ptr<IGameState> gs
        , std::shared_ptr<Logger> logger
        , std::shared_ptr<SerializationManager> sm
        , std::shared_ptr<UI> ui)
        : gs(gs)
        , logger(logger)
        , sm(sm)
        , ui(ui) {}

	void Execute() override
	{
        if (gs->GetDecisionState().GetCurrentMenu() != GameEnums::SAVE_MENU)
        {
            gs->GetDecisionState().SetCurrentMenu(GameEnums::SAVE_MENU);
            gs->GetDecisionState().SetChoice(GameEnums::NO_CHOICE);
        }
        else
        {
            std::string logLine = "";
            std::string fileName = ui->GetFilename();
            sm->Serialize(gs, fileName);

            if (sm->GetSerializationLog() != "")
            {
                logLine = sm->GetSerializationLog();
            }
            else { logLine = "Gra zostala zapisana jako " + fileName + "!"; }
            logger->UpdateLog(logLine);

            if (gs->GetDecisionState().GetChoice() != GameEnums::NO_CHOICE)
            {
                gs->GetDecisionState().SetCurrentMenu(GameEnums::MAIN_MENU);
            }
        }
	}
};
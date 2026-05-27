#pragma once
#include "SerializationManager.h"
#include "ForwardDeclarations.h"
#include "DecisionState.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "Action.h"
#include "Logger.h"
#include "UI.h"
#include <string>
#include <memory>

class LoadGame : public Action
{
private:
    std::shared_ptr<IGameState> gs;
    std::shared_ptr<Logger> logger;
    std::shared_ptr<SerializationManager> sm;
    std::shared_ptr<UI> ui;
public:
    LoadGame(std::shared_ptr<IGameState> gs
        , std::shared_ptr<Logger> logger
        , std::shared_ptr<SerializationManager> sm
        , std::shared_ptr<UI> ui)
        : gs(gs)
        , logger(logger)
        , sm(sm)
        , ui(ui) {}

    void Execute() override
    {
        if (gs->GetDecisionState().GetCurrentMenu() != GameEnums::LOAD_MENU)
        {
            gs->GetDecisionState().SetCurrentMenu(GameEnums::LOAD_MENU);
            gs->GetDecisionState().SetChoice(GameEnums::NO_CHOICE);
        }
        else
        {
            std::string logLine = "";
            std::string fileName = ui->GetFilename();
            sm->Deserialize(gs, fileName);

            if (sm->GetSerializationLog() != "")
            {
                logLine = sm->GetSerializationLog();
            }
            else { logLine = "Gra zostala wczytana z pliku " + fileName + "!"; }
            logger->UpdateLog(logLine);

            if (gs->GetDecisionState().GetChoice() != GameEnums::NO_CHOICE)
            {
                gs->GetDecisionState().SetCurrentMenu(GameEnums::MAIN_MENU);
            }
        }
    }
};
#pragma once
#include "SerializationManager.h"
#include "ForwardDeclarations.h"
#include "SerializationState.h"
#include "DecisionState.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "Logger.h"
#include "Action.h"
#include "UI.h"
#include <string>
#include <memory>

class ChangeSerialization : public Action
{
private:
    std::shared_ptr<IGameState> gs;
    std::shared_ptr<Logger> logger;
    std::shared_ptr<SerializationManager> sm;
    std::shared_ptr<UI> ui;
public:
    ChangeSerialization(std::shared_ptr<IGameState> gs
        , std::shared_ptr<Logger> logger
        , std::shared_ptr<SerializationManager> sm
        , std::shared_ptr<UI> ui)
        : gs(gs)
        , logger(logger)
        , sm(sm)
        , ui(ui) {}

	void Execute() override
	{
        if (gs->GetDecisionState().GetCurrentMenu() != GameEnums::SERIALIZATION_MENU)
        {
            gs->GetDecisionState().SetCurrentMenu(GameEnums::SERIALIZATION_MENU);
            gs->GetDecisionState().SetChoice(GameEnums::NO_CHOICE);
        }
        else
        {
            int8_t serializationType = gs->GetDecisionState().GetChoice();
            gs->GetSerializationState().SetSerializationType(serializationType);
            sm->SetSerializer(serializationType);

            std::string logLine = "Format serializacji: ";
            if (serializationType == GameEnums::JSON) { logLine += "JSON"; }
            else if (serializationType == GameEnums::TXT) { logLine += "TXT"; }
            logger->UpdateLog(logLine);

            if (serializationType != GameEnums::NO_CHOICE)
            {
                gs->GetDecisionState().SetCurrentMenu(GameEnums::MAIN_MENU);
            }
        }
	}
};
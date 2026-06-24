#pragma once
#include "ForwardDeclarations.h"
#include "AIState.h"
#include "DecisionState.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "AIManager.h"
#include "Logger.h"
#include "UI.h"
#include "Action.h"
#include <string>
#include <memory>

class ChangeDifficulty : public Action
{
private:
    std::shared_ptr<IGameState> gs;
    std::shared_ptr<Logger> logger;
    std::shared_ptr<AIManager> aim;
	std::shared_ptr<UI> ui;
public:
    ChangeDifficulty(std::shared_ptr<IGameState> gs
        , std::shared_ptr<Logger> logger
        , std::shared_ptr<AIManager> aim
        , std::shared_ptr<UI> ui)
        : gs(gs)
        , logger(logger)
        , aim(aim)
        , ui(ui) {}

    void Execute() override
    {
        if (gs->GetDecisionState().GetCurrentMenu() != GameEnums::DIFFICULTY_MENU)
        {
            gs->GetDecisionState().SetCurrentMenu(GameEnums::DIFFICULTY_MENU);
            gs->GetDecisionState().SetChoice(GameEnums::NO_CHOICE);
        }
        else
        {
            int8_t choice = gs->GetDecisionState().GetChoice();
            if (gs->GetAIState().GetRecentDifficulty() != gs->GetAIState().GetDifficulty())
            {
                gs->GetAIState().SetRecentDifficulty(gs->GetAIState().GetDifficulty());
            }

            gs->GetAIState().SetDifficulty(choice);
            aim->SetStrategy(choice);
            std::string logLine = "Poziom trudnosci: " + ui->GetAIDifficulty(choice) + "!";
            logger->UpdateLog(logLine);

            if (choice != GameEnums::NO_CHOICE)
            {
                gs->GetDecisionState().SetCurrentMenu(GameEnums::MAIN_MENU);
            }
        }
    }
};
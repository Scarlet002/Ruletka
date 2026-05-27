#include "DecisionProcessor.h"
#include "GameConfig.h"
#include "IGameState.h"
#include "GameEnums.h"
#include "IPlayer.h"
#include "AIManager.h"
#include "Logger.h"
#include "SerializationManager.h"
#include "Magazine.h"
#include "UI.h"
#include "InventoryProcessor.h"
#include "DecisionState.h"
#include "GameLoopState.h"
#include "ItemState.h"
#include <chrono>
#include <string>
#include <memory>
#include <thread>

DecisionProcessor::DecisionProcessor(std::shared_ptr<IGameState> gs
    , std::shared_ptr<AIManager> aim
    , std::shared_ptr<Logger> logger
    , std::shared_ptr<UI> ui)
    : gs(gs)
    , aim(aim)
    , logger(logger)
    , ui(ui) {}

void DecisionProcessor::AddAction(int8_t choice, std::shared_ptr<Action> action)
{
    decisions[choice] = std::move(action);
}

void DecisionProcessor::Decision()
{
    if (gs->GetGameLoopState().GetStarter() == GameEnums::HUMAN)
    {
        gs->GetDecisionState().SetChoice(ui->Decision());
    }
    else { gs->GetDecisionState().SetChoice(aim->Decision()); }
}

void DecisionProcessor::SetDecision(int8_t choice)
{
    auto it = decisions.find(choice);
    if (it != decisions.end()) decision = it->second; 
    else throw std::runtime_error("There is no such decision!");
}

void DecisionProcessor::CalcProbability()
{
    if (!gs->GetItemState().GetStateOfMagnifier()
        && !gs->GetItemState().GetStateOfCellPhone())
    {
        gs->GetMagazine().SetHitProbability(gs->GetMagazine().CalculateHitProbability());
    }
}

void DecisionProcessor::Process()
{
    if (gs->GetGameLoopState().GetIsOnePlayerAlive())
    {
        decision = decisions.at(GameEnums::RESTART);
        Decision();
        int8_t choice = gs->GetDecisionState().GetChoice();
        decision->Execute();
    }
    else
    {
        CalcProbability();
        Decision();
        int8_t choice = gs->GetDecisionState().GetChoice();
        if (choice == GameEnums::NO_CHOICE)
        {
            return;
        }
        if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::MAIN_MENU)
        {
            SetDecision(choice);
        }

        if (gs->GetGameLoopState().GetStarter() == GameEnums::HUMAN)
        {
            decision->Execute();
            if (decision == decisions.at(GameEnums::SHOOT)
                || decision == decisions.at(GameEnums::HEAL))
            {
                decision = decisions.at(GameEnums::AUTOSAVE);
                decision->Execute();
            }
        }
        else { decision->Execute(); }
    }
}
#include "InventoryProcessor.h"
#include "GameConfig.h"
#include "IGameState.h"
#include "IPlayer.h"
#include "AIManager.h" 
#include "Logger.h"
#include "UI.h"
#include "Magazine.h"
#include "DecisionState.h"
#include "GameLoopState.h"
#include "Action.h"
#include "GameEnums.h"
#include <memory>
#include <unordered_map>

InventoryProcessor::InventoryProcessor(std::shared_ptr<IGameState> gs
    , std::shared_ptr<Logger> logger
    , std::shared_ptr<UI> ui)
    : gs(gs)
    , logger(logger)
    , ui(ui) {}

void InventoryProcessor::Process()
{
    if (gs->GetDecisionState().GetCurrentMenu() != GameEnums::INVENTORY_MENU)
    {
        gs->GetDecisionState().SetCurrentMenu(GameEnums::INVENTORY_MENU);
        gs->GetDecisionState().SetChoice(GameEnums::NO_CHOICE);
    }
    else
    {

        IPlayer& currentPlayer = gs->GetGameLoopState().GetStarter() == GameEnums::HUMAN
                               ? gs->GetHuman() : gs->GetComputer();

        int8_t itemChoice = gs->GetDecisionState().GetChoice();

        auto it = itemActions.find(itemChoice);
        if (it != itemActions.end())
        {
            it->second->Execute();
        }
        else
        {
            if (itemChoice == GameEnums::NO_ITEMS)
            {
                logger->UpdateLog(currentPlayer.GetName() + " nie uzyl zadnego przedmiotu!");
            }
            if (itemChoice != GameEnums::NO_CHOICE && itemChoice != GameEnums::NO_ITEMS)
            {
                logger->UpdateLog("Nieprawidlowy wybor!");
            }
        }

        if (itemChoice != GameEnums::NO_CHOICE)
        {
            gs->GetDecisionState().SetCurrentMenu(GameEnums::MAIN_MENU);
        }
    }
}

void InventoryProcessor::AddAction(int8_t choice, std::shared_ptr<Action> action)
{
    itemActions[choice] = std::move(action);
}
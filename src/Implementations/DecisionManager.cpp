#include "DecisionManger.h"
#include "InputValidatorManager.h"
#include "GameEnums.h"
#include "GameState.h"
#include <string>

int DecisionManager::MakeDecision(GameState& gameState) const
{
    int choice = GameEnums::SHOOT;
    if (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN)
    {
        string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 7): ", InputValidatorManager::IsValidMenuChoice);
        choice = stoi(input);
    }
    else
    {
        if (gameState.ai.GetDifficulty() == GameEnums::EASY)
        {
            gameState.ai.EasyAI(gameState);
        }
        else if (gameState.ai.GetDifficulty() == GameEnums::NORMAL)
        {
            gameState.ai.NormalAI(gameState);
        }
        else
        {
            gameState.ai.HardAI(gameState);
        }
        gameState.gameStateManager.GetChoice();
    }
    return choice;
}
#include "DecisionManager.h"
#include "InputValidatorManager.h"
#include "GameEnums.h"
#include "GameState.h"
#include <string>

int DecisionManager::MakeDecision(GameState& gameState) const
{
    int choice = GameEnums::NO_CHOICE;
    if (gameState.gameStateManager.GetStarter() == GameEnums::STARTER_HUMAN)
    {
        string input = InputValidatorManager::GetValidatedInput("Twoj wybor (0 - 6): ", InputValidatorManager::IsValidMenuChoice);
        choice = stoi(input);
        gameState.gameStateManager.SetChoice(choice);
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
        choice = gameState.gameStateManager.GetChoice();
    }
    return choice;
}
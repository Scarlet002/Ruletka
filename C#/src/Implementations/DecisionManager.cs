public class DecisionManager : IDecisionManager
{
    public DecisionManager() { }

    public int MakeDecision(GameState gameState)
    {
        int choice = (int)GameEnums.Choice.NO_CHOICE;

        if (gameState.gameStateManager.GetStarter() == (int)GameEnums.Starter.STARTER_HUMAN)
        {
            string input = InputValidatorManager.GetValidatedInput("Twoj wybor (0 - 6): ", InputValidatorManager.IsValidMenuChoice);
            choice = int.Parse(input);
            gameState.gameStateManager.SetChoice(choice);
        }
        else
        {
            if (gameState.ai.GetDifficulty() == (int)GameEnums.Difficulty.EASY)
            {
                gameState.ai.EasyAI(gameState);
            }
            else if (gameState.ai.GetDifficulty() == (int)GameEnums.Difficulty.NORMAL)
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
}
public class HandCuffs : Item
{
    public HandCuffs() { }

    public void UseItem(GameState gameState)
    {
        gameState.gameStateManager.SetStateOfHandCuffs(true);
        if (gameState.gameStateManager.GetStarter() == (int)GameEnums.Starter.STARTER_HUMAN)
        {
            gameState.log.Add("Uzyles kajdanek!");
        }
        else
        {
            gameState.log.Add("Komputer uzyl kajdanek!");
        }
    }
}
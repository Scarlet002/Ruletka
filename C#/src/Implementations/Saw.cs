public class Saw : Item
{
    public Saw() { }

    public void UseItem(GameState gameState)
    {
        gameState.gameStateManager.SetDamage(gameState.gameConfig.sawDamage);
        if (gameState.gameStateManager.GetStarter() == (int)GameEnums.Starter.STARTER_HUMAN)
        {
            gameState.log.Add("Uzyles pily (obrazenia razy 2)!");
        }
        else
        {
            gameState.log.Add("Komputer uzyl pily (obrazenia razy 2)!");
        }
    }
}
public class Magnifier : Item
{
    public Magnifier() { }

    public void UseItem(GameState gameState)
    {
        if (gameState.magazine.CheckBulletType())
        {
            if (gameState.gameStateManager.GetStarter() == (int)GameEnums.Starter.STARTER_HUMAN)
            {
                gameState.log.Add("Uzyles lupy (pelna)!");
            }
            else
            {
                gameState.log.Add("Komputer uzyl lupy!");
            }
        }
        else
        {
            if (gameState.gameStateManager.GetStarter() == (int)GameEnums.Starter.STARTER_HUMAN)
            {
                gameState.log.Add("Uzyles lupy (pusta)!");
            }
            else
            {
                gameState.log.Add("Komputer uzyl lupy!");
            }
        }
    }
}
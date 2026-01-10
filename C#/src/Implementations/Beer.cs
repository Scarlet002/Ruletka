public class Beer : Item
{
    public Beer() { }

    public void UseItem(GameState gameState)
    {
        if (gameState.magazine.CheckBulletType())
        {
            gameState.magazine.DecreaseFullCount();
            if (gameState.gameStateManager.GetStarter() == (int)GameEnums.Starter.STARTER_HUMAN)
            {
                gameState.log.Add("Uzyles piwa (usunieto pelna)!");
            }
            else
            {
                gameState.log.Add("Komputer uzyl piwa (usunieto pelna)!");
            }
        }
        else
        {
            gameState.magazine.DecreaseEmptyCount();
            if (gameState.gameStateManager.GetStarter() == (int)GameEnums.Starter.STARTER_HUMAN)
            {
                gameState.log.Add("Uzyles piwa (usunieto pusta)!");
            }
            else
            {
                gameState.log.Add("Komputer uzyl piwa (usunieto pusta)!");
            }
        }
        gameState.magazine.DecreaseBulletCount();
    }
}
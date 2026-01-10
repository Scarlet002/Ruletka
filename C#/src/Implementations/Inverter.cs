public class Inverter : Item
{
    public Inverter() { }

    public void UseItem(GameState gameState)
    {
        gameState.wasMagazineShown = true;
        gameState.magazine.InvertBulletType();
        gameState.magazine.CheckBullets();
        if (gameState.gameStateManager.GetStarter() == (int)GameEnums.Starter.STARTER_HUMAN)
        {
            gameState.log.Add("Zmieniles typ naboju!");
        }
        else
        {
            gameState.log.Add("Komputer zmienil typ naboju!");
        }
    }
}
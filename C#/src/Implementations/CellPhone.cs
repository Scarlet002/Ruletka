using System;

public class CellPhone : Item
{
    private int bullet = 0;
    private Random random = new Random();

    public CellPhone() { }

    public void UseItem(GameState gameState)
    {
        bullet = random.Next(gameState.magazine.GetMagazineSize());
        if (gameState.magazine.CheckBulletTypeCellPhone(bullet))
        {
            if (gameState.gameStateManager.GetStarter() == (int)GameEnums.Starter.STARTER_HUMAN)
            {
                gameState.log.Add("Uzyles telefonu (" + (bullet + 1).ToString() + " pelna)!");
            }
            else
            {
                gameState.log.Add("Komputer uzyl telefonu!");
            }
        }
        else
        {
            if (gameState.gameStateManager.GetStarter() == (int)GameEnums.Starter.STARTER_HUMAN)
            {
                gameState.log.Add("Uzyto telefonu (" + (bullet + 1).ToString() + " pusta)!");
            }
            else
            {
                gameState.log.Add("Komputer uzyl telefonu!");
            }
        }
    }
}
using System;

public class ShootingManager : IShootingManager
{
    public ShootingManager() { }

    public void Shoot(GameState gameState)
    {
        int target = gameState.gameStateManager.GetTarget();
        int shooter = gameState.gameStateManager.GetShooter();

        try
        {
            if (gameState.magazine.IsEmpty())
                throw new Exception("Brak pociskow w magazynku!");

            if (gameState.gameStateManager.GetChoice() == (int)GameEnums.Choice.SHOOT)
            {
                if (gameState.magazine.IsEmptySlot())
                {
                    if (target == (int)GameEnums.Shooter.SHOOTER_HUMAN)
                    {
                        gameState.log.Add("Komputer nie trafia!");
                    }
                    else
                    {
                        gameState.log.Add("Nie trafiasz!");
                    }
                    gameState.magazine.DecreaseEmptyCount();
                }
                else
                {
                    if (target == (int)GameEnums.Shooter.SHOOTER_HUMAN)
                    {
                        gameState.human.LoseHP(gameState);
                        gameState.log.Add("Zostales trafiony!");
                    }
                    else
                    {
                        gameState.computer.LoseHP(gameState);
                        gameState.log.Add("Trafiles komputer!");
                    }
                    gameState.magazine.DecreaseFullCount();
                }
            }
            else
            {
                if (gameState.magazine.IsEmptySlot())
                {
                    int currentHP = (shooter == (int)GameEnums.Shooter.SHOOTER_HUMAN) ?
                        gameState.human.GetHP() : gameState.computer.GetHP();

                    if (currentHP < gameState.gameConfig.maxPlayerHP)
                    {
                        if (shooter == (int)GameEnums.Shooter.SHOOTER_HUMAN)
                        {
                            gameState.human.RegainHP();
                            gameState.log.Add("Odzyskales 1 HP!");
                        }
                        else
                        {
                            gameState.computer.RegainHP();
                            gameState.log.Add("Komputer odzyskal 1 HP!");
                        }
                    }
                    else
                    {
                        if (shooter == (int)GameEnums.Shooter.SHOOTER_HUMAN)
                        {
                            gameState.log.Add("Nie odzyskales HP bo masz MAXHP!");
                        }
                        else
                        {
                            gameState.log.Add("Komputer nie odzyskal HP bo ma MAXHP!");
                        }
                    }
                    gameState.magazine.DecreaseEmptyCount();
                }
                else
                {
                    if (shooter == (int)GameEnums.Shooter.SHOOTER_HUMAN)
                    {
                        gameState.human.LoseHP(gameState);
                        gameState.log.Add("Nie udalo sie odzyskac HP (straciles 1 HP)");
                    }
                    else
                    {
                        gameState.computer.LoseHP(gameState);
                        gameState.log.Add("Nie udalo sie odzyskac HP (komputer stracil 1 HP)!");
                    }
                    gameState.magazine.DecreaseFullCount();
                }
            }
            gameState.magazine.DecreaseBulletCount();
        }
        catch (Exception e)
        {
            Console.WriteLine("Blad strzalu: " + e.Message);
            gameState.magazine.Reload();
        }
    }
}
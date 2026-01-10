using System;

public class AiManager : IAiManager
{
    private int difficulty = (int)GameEnums.Difficulty.NORMAL;

    public AiManager() { }

    public int SetDifficulty(int newDifficulty)
    {
        difficulty = newDifficulty;
        return difficulty;
    }

    public int GetDifficulty()
    {
        return difficulty;
    }

    public void EasyAI(GameState gameState)
    {
        Random rand = new Random();
        gameState.gameStateManager.SetChoice(rand.Next(gameState.gameConfig.numberOfBulletTypes));
    }

    public void NormalAI(GameState gameState)
    {
        double hitChance = gameState.magazine.CalculateHitProbability();

        if (gameState.computer.GetCellPhones() > 0)
        {
            gameState.computer.UseCellPhone(gameState);
        }

        if (gameState.computer.GetHandCuffs() > 0)
        {
            gameState.computer.UseHandCuffs(gameState);
        }

        if (hitChance == 1.0)
        {
            if (gameState.computer.GetSaws() > 0 && gameState.human.GetHP() >= 2)
            {
                gameState.computer.UseSaw(gameState);
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
            }
            else
            {
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
            }
        }
        else if (hitChance != 0.0 && hitChance != 1.0)
        {
            if (gameState.computer.GetMagnifiers() > 0)
            {
                gameState.computer.UseMagnifier(gameState);
                if (gameState.magazine.CheckBulletType())
                {
                    if (gameState.computer.GetSaws() > 0 && gameState.human.GetHP() >= 2)
                    {
                        gameState.computer.UseSaw(gameState);
                        gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
                    }
                    else
                    {
                        gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
                    }
                }
                else
                {
                    if (gameState.computer.GetInverters() > 0)
                    {
                        gameState.computer.UseInverter(gameState);
                        gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
                    }
                    else if (gameState.computer.GetBeers() > 0)
                    {
                        if (gameState.computer.GetHP() == gameState.gameConfig.maxPlayerHP)
                        {
                            gameState.computer.UseBeer(gameState);
                            hitChance = gameState.magazine.CalculateHitProbability();
                            if (hitChance == 1.0)
                            {
                                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
                            }
                            else if (hitChance != 0.0 && hitChance != 1.0)
                            {
                                if (gameState.computer.GetMagnifiers() > 0 &&
                                    (gameState.computer.GetSaws() > 0 && gameState.human.GetHP() >= 2))
                                {
                                    gameState.computer.UseMagnifier(gameState);
                                    if (gameState.magazine.CheckBulletType())
                                    {
                                        gameState.computer.UseSaw(gameState);
                                        gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
                                    }
                                    else
                                    {
                                        gameState.gameStateManager.SetChoice((int)GameEnums.Choice.HEAL);
                                    }
                                }
                                else
                                {
                                    gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
                                }
                            }
                            else
                            {
                                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.HEAL);
                            }
                        }
                        else
                        {
                            gameState.gameStateManager.SetChoice((int)GameEnums.Choice.HEAL);
                        }
                    }
                    else
                    {
                        gameState.gameStateManager.SetChoice((int)GameEnums.Choice.HEAL);
                    }
                }
            }
            else
            {
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
            }
        }
        else
        {
            if (gameState.human.GetHP() == 1 && gameState.computer.GetInverters() > 0)
            {
                gameState.computer.UseInverter(gameState);
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
            }
            else if ((gameState.human.GetHP() == 2 && gameState.computer.GetInverters() > 0) &&
                     gameState.computer.GetSaws() > 0)
            {
                gameState.computer.UseInverter(gameState);
                gameState.computer.UseSaw(gameState);
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
            }
            else
            {
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.HEAL);
            }
        }
    }

    public void HardAI(GameState gameState)
    {
        if (gameState.computer.GetMagnifiers() > 0)
        {
            gameState.computer.UseMagnifier(gameState);
        }

        if (gameState.computer.GetCellPhones() > 0)
        {
            gameState.computer.UseCellPhone(gameState);
        }

        if (gameState.computer.GetHandCuffs() > 0)
        {
            gameState.computer.UseHandCuffs(gameState);
        }

        if (gameState.magazine.CheckBulletType())
        {
            if (gameState.human.GetHP() == 1)
            {
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
            }
            else if (gameState.human.GetHP() == 2 && gameState.computer.GetSaws() > 0)
            {
                gameState.computer.UseSaw(gameState);
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
            }
            else if (gameState.computer.GetHP() == 1 && gameState.computer.GetInverters() > 0)
            {
                gameState.computer.UseInverter(gameState);
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.HEAL);
            }
            else if (gameState.computer.GetSaws() > 0 && gameState.human.GetHP() >= 2)
            {
                gameState.computer.UseSaw(gameState);
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
            }
            else
            {
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
            }
        }
        else
        {
            if (gameState.human.GetHP() == 1 && gameState.computer.GetInverters() > 0)
            {
                gameState.computer.UseInverter(gameState);
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
            }
            else if ((gameState.human.GetHP() == 2 && gameState.computer.GetInverters() > 0) &&
                     gameState.computer.GetSaws() > 0)
            {
                gameState.computer.UseInverter(gameState);
                gameState.computer.UseSaw(gameState);
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
            }
            else if (gameState.computer.GetHP() == 1)
            {
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.HEAL);
            }
            else if (gameState.computer.GetInverters() > 0 &&
                     gameState.computer.GetHP() == gameState.gameConfig.maxPlayerHP)
            {
                gameState.computer.UseInverter(gameState);
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
            }
            else if (gameState.computer.GetBeers() > 0 &&
                     gameState.computer.GetHP() == gameState.gameConfig.maxPlayerHP)
            {
                gameState.computer.UseBeer(gameState);
                if (gameState.magazine.CheckBulletType())
                {
                    gameState.gameStateManager.SetChoice((int)GameEnums.Choice.SHOOT);
                }
                else
                {
                    gameState.gameStateManager.SetChoice((int)GameEnums.Choice.HEAL);
                }
            }
            else
            {
                gameState.gameStateManager.SetChoice((int)GameEnums.Choice.HEAL);
            }
        }
    }
}
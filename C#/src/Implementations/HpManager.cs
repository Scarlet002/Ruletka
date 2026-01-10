public class HpManager : IHpManager
{
    private GameConfig gameConfig;
    private readonly int MAXHP;
    private int currentHP;

    public HpManager(GameConfig gameConfig)
    {
        this.gameConfig = gameConfig;
        MAXHP = gameConfig.maxPlayerHP;
        currentHP = gameConfig.maxPlayerHP;
    }

    public void LoseHP(GameState gameState)
    {
        int damage = gameState.gameStateManager.GetDamage();
        if (currentHP > 0)
        {
            SetHP(GetHP() - damage);
        }
    }

    public void RegainHP()
    {
        if (currentHP > 0 && currentHP < MAXHP)
            currentHP++;
    }

    public void ResetHP()
    {
        currentHP = MAXHP;
    }

    public int GetHP()
    {
        return currentHP;
    }

    public void SetHP(int newHP)
    {
        currentHP = newHP;
    }
}
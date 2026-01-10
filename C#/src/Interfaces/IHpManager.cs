public interface IHpManager
{
    void LoseHP(GameState gameState);
    void RegainHP();
    void ResetHP();
    int GetHP();
    void SetHP(int newHP);
}
public interface IAiManager
{
    int SetDifficulty(int newDifficulty);
    int GetDifficulty();
    void EasyAI(GameState gameState);
    void NormalAI(GameState gameState);
    void HardAI(GameState gameState);
}
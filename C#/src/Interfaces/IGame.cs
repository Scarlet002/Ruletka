public interface IGame
{
    void NewRound(GameState gameState, IUiManager ui);
    bool WhoWon(GameState gameState, IUiManager ui);
    void StartGame();
}
using static AutoSaveManager;

public interface ISaveAsyncManager
{
    void SetSaveCounter(int newSaveCounter);
    int GetSaveCounter();
    string SaveGameStateAsync(GameState gameState, string autoSaveFileName);
    bool IsSaving();
}
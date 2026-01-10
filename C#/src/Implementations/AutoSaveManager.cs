using System;
using System.Threading.Tasks;

public class AutoSaveManager : ISaveAsyncManager
{
    private Task saveTask;
    private bool isSaving;
    private int saveCounter;
    private SaveJSONManager saver;
    private GameState gameState;

    public AutoSaveManager(SaveJSONManager saverRef, GameState gameState)
    {
        saver = saverRef;
        this.gameState = gameState;
        isSaving = false;
        saveCounter = 0;
    }

    public void SetSaveCounter(int newSaveCounter)
    {
        saveCounter = newSaveCounter;
    }

    public string SaveGameStateAsync(GameState gameState, string autoSaveFileName)
    {
        isSaving = true;
        SetSaveCounter(GetSaveCounter() + 1);

        string finalFileName = string.IsNullOrEmpty(autoSaveFileName)
            ? "autosave" + GetSaveCounter().ToString() + ".json"
            : autoSaveFileName;

        string fileNameForTask = finalFileName;
        var localGameState = gameState;
        var localSaver = saver;

        saveTask = Task.Run(async () =>
        {
            await Task.Delay(500);

            localSaver.SaveGameState(localGameState, fileNameForTask);

            isSaving = false;
            Console.WriteLine($"Autosave wykonany: {fileNameForTask}");
        });

        return finalFileName;
    }

    public int GetSaveCounter()
    {
        return saveCounter;
    }

    public bool IsSaving()
    {
        return isSaving;
    }
}
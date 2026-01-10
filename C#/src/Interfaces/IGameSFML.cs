using System.Collections.Generic;

public interface IGameSFML
{
    void InitializeGame();
    void ProcessPlayerAction(int action);
    void ProcessComputerTurn();
    void UseItem(int item);
    void CheckGameConditions();
    void SwitchTurn();
    void Run();
    void HandlePlayerChoice(int choice);
    void HandleItemChoice(int item);
    void HandleRestartChoice(int choice);
    void HandleSaveLoadWithFilename(int action, string filename);
    void HandleDifficultyChoice(int choice);
}
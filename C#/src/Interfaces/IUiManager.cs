public interface IUiManager
{
    void DisplayStats(GameState gameState);
    void ScrollScreen();
    void Menu();
    void DifficultyMenu();
    void ShowAIDifficulty(int difficulty);
    void InventoryMenu();

    void InputSaveTXT(ref string fileName);
    void InputLoadTXT(ref string fileName);
    void InputSaveJSON(ref string fileName);
    void InputLoadJSON(ref string fileName);
    void InputDifficultyLevel(GameState gameState);
    void InputItemChoice(GameState gameState);

    bool WantsToContinue(GameState gameState);
    void ComputerChoosing();
    void ComputerStarts();
    void HumanStarts();
    void ShowPointer();
    void NewLine();
    void AutoSaveDone();
    void ShowAutoSaveName(string autoSaveFileName);
    void SavingSuccess();
    void LoadingSuccess();
    void DifficultyChangeSuccess();
    void ItemUseSuccessHuman(GameState gameState);
    void ItemUseSuccessComputer(GameState gameState);
    void InvalidInput();
    void ComputerWin();
    void HumanWin();
    void EndOfBullets();
    void ThankYou();
    void Clear();
}
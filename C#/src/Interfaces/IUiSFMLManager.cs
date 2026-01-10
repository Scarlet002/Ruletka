using System.Collections.Generic;
using SFML.Graphics;
using SFML.Window;
using SFML.System;

public interface IUiSFMLManager
{
    void DrawStatsPanel(GameState gameState, float x, float y, bool isHuman);
    void DrawGameLog(GameState gameState, float x, float y);
    void DrawDecisionPanel(GameState gameState, float x, float y);
    void DrawGameOverScreen(GameState gameState, float x, float y);
    void DrawWaitForComputerPanel(float x, float y);
    void DrawMagazinePanel(GameState gameState, float x, float y);
    void DrawDifficultyInfoPanel(GameState gameState, float x, float y);
    void DrawFilenameInput(float x, float y);

    void CreateMainButtons();
    void CreateItemButtons();
    void CreateDifficultyButtons();
    void CreateRestartButtons(float x, float y);

    void HandleGameOverInput(GameState gameState, Vector2i mousePos);
    void HandleNormalGameInput(GameState gameState, Vector2i mousePos);
    void HandleFilenameInput(GameState gameState, SFML.Window.Event sfmlEvent);

    bool Initialize();
    void ProcessEvents(GameState gameState);
    void Render(GameState gameState);
    void AddToLog(GameState gameState, string message);
    void ClearLog(GameState gameState);
    void ShowMessage(GameState gameState, string message);
    void DisplayStats(GameState gameState);

    bool IsShowingItemMenu();
    bool IsShowingSaveLoadMenu();
    bool IsShowingDifficultyMenu();
    bool IsRestartButtonCreated();

    void ShowItemMenu(bool show);
    void ShowSaveLoadMenu(bool show);
    void ShowDifficultyMenu(bool show);
    void ShowRestartMenu(bool show);

    void StartFilenameInput(int action);
    void SetGameReference(GameSFMLVersion game);
    bool IsWindowOpen();
    void CloseWindow();
    void ResetUI(GameState gameState);
}
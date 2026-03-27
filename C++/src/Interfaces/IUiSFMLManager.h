#pragma once
#include "IGameEngine.h"
#include <string>

class IUiSFMLManager 
{
public:
    virtual void DrawStatsPanel(float x, float y, bool isHuman) = 0;
    virtual void DrawGameLog(float x, float y) = 0;
    virtual void DrawDecisionPanel(float x, float y) = 0;
    virtual void DrawGameOverScreen(float x, float y) = 0;
    virtual void DrawWaitForComputerPanel(float x, float y) = 0;

    virtual void CreateMainButtons() = 0;
    virtual void CreateItemButtons() = 0;
    virtual void CreateDifficultyButtons() = 0;
    virtual void CreateRestartButtons(float x, float y) = 0;

    virtual void HandleGameOverInput(const sf::Vector2i& mousePos) = 0;
    virtual void HandleNormalGameInput(const sf::Vector2i& mousePos) = 0;

    virtual void DrawFilenameInput(float x, float y) = 0;
    virtual void HandleFilenameInput(const sf::Event& event) = 0;

    virtual void SetGameReference(IGameEngine* game) = 0;

    virtual bool Initialize() = 0;
    virtual void ProcessEvents() = 0;
    virtual void Render() = 0;

    virtual void AddToLog(const std::string& message) = 0;
    virtual void ClearLog() = 0;
    virtual void StartFilenameInput(int action) = 0;

    virtual bool IsWindowOpen() const = 0;
    virtual void CloseWindow() = 0;

    virtual unsigned int GetWindowWidth() const = 0;
    virtual unsigned int GetWindowHeight() const = 0;

    virtual void DrawMagazinePanel(float x, float y) = 0;
    virtual void DrawDifficultyInfoPanel(float x, float y) = 0;

    virtual bool IsShowingItemMenu() const = 0;
    virtual bool IsShowingSaveLoadMenu() const = 0;
    virtual bool IsShowingDifficultyMenu() const = 0;
    virtual bool IsRestartButtonCreated() const = 0;

    virtual void ShowItemMenu(bool show) = 0;
    virtual void ShowSaveLoadMenu(bool show) = 0;
    virtual void ShowDifficultyMenu(bool show) = 0;
    virtual void ShowRestartMenu(bool show) = 0;
	virtual void ShowMessage(const std::string& message) = 0;

	virtual void DisplayStats() const = 0;

    virtual void ResetUI() = 0;

    virtual ~IUiSFMLManager() = default;
};
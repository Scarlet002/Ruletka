#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "ForwardDeclarations.h"
#include <string>
#include <vector>

class IUiSFMLManager 
{
public:
    virtual void DrawStatsPanel(const GameState& gameState, float x, float y, bool isHuman) = 0;
    virtual void DrawGameLog(GameState& gameState, float x, float y) = 0;
    virtual void DrawDecisionPanel(const GameState& gameState, float x, float y) = 0;
    virtual void DrawGameOverScreen(const GameState& gameState, float x, float y) = 0;
    virtual void DrawWaitForComputerPanel(float x, float y) = 0;

    virtual void CreateMainButtons() = 0;
    virtual void CreateItemButtons() = 0;
    virtual void CreateDifficultyButtons() = 0;
    virtual void CreateRestartButtons(float x, float y) = 0;

    virtual void HandleGameOverInput(GameState& gameState, const sf::Vector2i& mousePos) = 0;
    virtual void HandleNormalGameInput(GameState& gameState, const sf::Vector2i& mousePos) = 0;

    virtual void DrawFilenameInput(float x, float y) = 0;
    virtual void HandleFilenameInput(GameState& gameState, const sf::Event& event) = 0;

    virtual void SetGameReference(GameSFMLVersion* game) = 0;

    virtual bool Initialize() = 0;
    virtual void ProcessEvents(GameState& gameState) = 0;
    virtual void Render(GameState& gameState) = 0;

    virtual void AddToLog(GameState& gameState, const std::string& message) = 0;
    virtual void ClearLog(GameState& gameState) = 0;
    virtual void StartFilenameInput(int action) = 0;

    virtual bool IsWindowOpen() const = 0;
    virtual void CloseWindow() = 0;

    virtual unsigned int GetWindowWidth() const = 0;
    virtual unsigned int GetWindowHeight() const = 0;

    virtual void DrawMagazinePanel(const GameState& gameState, float x, float y) = 0;
    virtual void DrawDifficultyInfoPanel(const GameState& gameState, float x, float y) = 0;

    virtual bool IsShowingItemMenu() const = 0;
    virtual bool IsShowingSaveLoadMenu() const = 0;
    virtual bool IsShowingDifficultyMenu() const = 0;
    virtual bool IsRestartButtonCreated() const = 0;

    virtual void ShowItemMenu(bool show) = 0;
    virtual void ShowSaveLoadMenu(bool show) = 0;
    virtual void ShowDifficultyMenu(bool show) = 0;
    virtual void ShowRestartMenu(bool show) = 0;
	virtual void ShowMessage(GameState& gameState, const std::string& message) = 0;

	virtual void DisplayStats(const GameState& gameState) = 0;

    virtual void ResetUI(GameState& gameState) = 0;

    virtual ~IUiSFMLManager() = default;
};
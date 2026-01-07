#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "IUiSFMLManager.h"
#include "ForwardDeclarations.h"
#include <string>
#include <vector>

class UiSFMLManager : public IUiSFMLManager 
{
private:

    struct Button {
        sf::RectangleShape rect;
        sf::Text text;
        int actionId = 0;
        bool isHovered = false;
    };

    sf::RenderWindow window;
    sf::Font font;

    static const unsigned int WINDOW_WIDTH = 1200;
    static const unsigned int WINDOW_HEIGHT = 600;

    IGameSFML* gameRef = nullptr;

    bool showInventory = false;
    bool showSaveLoad = false;
    bool showDifficulty = false;
    bool showRestart = false;

    bool isWaitingForFilename = false;
    int currentFileAction = 0;
    std::string currentFilename;
    sf::Text filenameText;
    sf::RectangleShape filenameBox;
    sf::Text filenameLabel;

    static const int MAX_LOG_LINES = 8;

    Button restartButton;
    Button exitButton;
    bool restartButtonCreated = false;

    std::vector<Button> mainButtons;
    std::vector<Button> itemButtons;
    std::vector<Button> saveLoadButtons;
    std::vector<Button> difficultyButtons;

public:
    UiSFMLManager(GameState& gameState);

    void DrawStatsPanel(const GameState& gameState, float x, float y, bool isHuman) override;
    void DrawGameLog(GameState& gameState, float x, float y) override;
    void DrawDecisionPanel(const GameState& gameState, float x, float y) override;
    void DrawGameOverScreen(const GameState& gameState, float x, float y) override;
    void DrawWaitForComputerPanel(float x, float y) override;

    void CreateMainButtons() override;
    void CreateItemButtons() override;
    void CreateDifficultyButtons() override;
    void CreateRestartButtons(float x, float y) override;

    void HandleGameOverInput(GameState& gameState, const sf::Vector2i& mousePos) override;
    void HandleNormalGameInput(GameState& gameState, const sf::Vector2i& mousePos) override;

    void DrawFilenameInput(float x, float y) override;
    void HandleFilenameInput(GameState& gameState, const sf::Event& event) override;

    void SetGameReference(GameSFMLVersion* game) override;

    bool Initialize() override;
    void ProcessEvents(GameState& gameState) override;
    void Render(GameState& gameState) override;

    void AddToLog(GameState& gameState, const std::string& message) override;
    void ClearLog(GameState& gameState) override;
    void StartFilenameInput(int action) override;

    bool IsWindowOpen() const override;
    void CloseWindow() override;

    unsigned int GetWindowWidth() const override { return WINDOW_WIDTH; }
    unsigned int GetWindowHeight() const override { return WINDOW_HEIGHT; }

    void DrawMagazinePanel(GameState& gameState, float x, float y) override;
    void DrawDifficultyInfoPanel(const GameState& gameState, float x, float y) override;

    bool IsShowingItemMenu() const override { return showInventory; }
    bool IsShowingSaveLoadMenu() const override { return showSaveLoad; }
    bool IsShowingDifficultyMenu() const override { return showDifficulty; }
    bool IsRestartButtonCreated() const override { return restartButtonCreated; }

    void ShowItemMenu(bool show) override { showInventory = show; }
    void ShowSaveLoadMenu(bool show) override { showSaveLoad = show; }
    void ShowDifficultyMenu(bool show) override { showDifficulty = show; }
    void ShowRestartMenu(bool show) override { showRestart = show; }
	void ShowMessage(GameState& gameState, const std::string& message) override;
	void DisplayStats(const GameState& gameState) override;

    void ResetUI(GameState& gameState) override;

    ~UiSFMLManager();
};
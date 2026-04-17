#pragma once
#include <SFML/Graphics.hpp>
#include "IUiManager.h"
#include "ForwardDeclarations.h"
#include "GameEnums.h"
#include "GameConfig.h"
#include <string>
#include <vector>
#include <cstdint>

class UiSFMLManager : public IUiManager 
{
private:
    typedef unsigned int uint;
    struct Button 
    {
        sf::RectangleShape rect;
        sf::Text text;
        int8_t actionId = GameEnums::NO_CHOICE;
        bool isHovered = false;
    };

    sf::RenderWindow window;
    sf::Font font;

    static constexpr uint WINDOW_WIDTH = 1200;
    static constexpr uint WINDOW_HEIGHT = 600;

    bool showInventory = false;
    bool showSaveLoad = false;
    bool showDifficulty = false;
    bool showRestart = false;
    bool isWaitingForFilename = false;
	bool wasMagazinePanelShown = false;
    bool waitingForRestartChoice = false;

    sf::Text filenameText;
    sf::RectangleShape filenameBox;
    sf::Text filenameLabel;

    Button restartButton;
    Button exitButton;
    bool restartButtonCreated = false;

    std::vector<Button> mainButtons;
    std::vector<Button> itemButtons;
    std::vector<Button> saveLoadButtons;
    std::vector<Button> difficultyButtons;

    std::string fileName = "save";
    std::string logLine = "";
    std::vector<std::string> log;
    std::vector<std::string> recentLog;
    const GameState& state;

    // Metody związane z rysowanie kafelków i paneli okna
    inline void DrawStatsPanel(float x, float y, bool isHuman);
    inline void DrawGameLog(float x, float y);
    inline void DrawDecisionPanel(float x, float y);
    inline void DrawGameOverScreen(float x, float y);
    inline void DrawWaitForComputerPanel(float x, float y);
    inline void DrawMagazinePanel(float x, float y);
    inline void DrawDifficultyInfoPanel(float x, float y);
    inline void DrawFilenameInput(float x, float y);

    // Metody związane z tworzeniem przycisków i interakcji okna
    inline void CreateMainButtons();
    inline void CreateItemButtons();
    inline void CreateDifficultyButtons();
    inline void CreateRestartButtons(float x, float y);
    inline void CreateFilenameInput(int8_t action);

    // Other window methods
    inline bool IsWindowOpen() const;
    inline void CloseWindow();

    // Metody związane z obsługą wejścia z klawiatury i myszy
    inline int8_t HandleGameOverInput(const sf::Vector2i& mousePos);
    inline int8_t HandleNormalGameInput(const sf::Vector2i& mousePos);
    inline int8_t InputDifficultyLevel(const sf::Vector2i& mousePos);
    inline int8_t InputItemChoice(const sf::Vector2i& mousePos);
    inline int8_t HandleFilenameInput(const sf::Event& event);
    inline void SetRecentLog(const std::vector<std::string>& newRecentLog);
    inline const std::vector<std::string>& GetRecentLog() const;

	// Gettery
    inline bool IsShowingInventoryMenu() const { return showInventory; }
    inline bool IsShowingSaveLoadMenu() const { return showSaveLoad; }
    inline bool IsShowingDifficultyMenu() const { return showDifficulty; }
    inline bool IsRestartButtonCreated() const { return restartButtonCreated; }
    inline bool IsWaitingForFilename() const { return isWaitingForFilename; }
    inline bool IsShowingRestartMenu() const { return showRestart; }
	inline bool isWaitingForRestartChoice() const { return waitingForRestartChoice; }

    // Settery
    inline void SetItemMenu(bool newState) { showInventory = newState; }
    inline void SetSaveLoadMenu(bool newState) { showSaveLoad = newState; }
    inline void SetDifficultyMenu(bool newState) { showDifficulty = newState; }
    inline void SetRestartMenu(bool newState) { showRestart = newState; }
    inline void SetRestartButtonState(bool newState) { restartButtonCreated = newState; }
    inline void SetCurrentFilenameState(bool newState) { isWaitingForFilename = newState; }
	inline void SetWaitingForRestartChoice(bool newState) { waitingForRestartChoice = newState; }
public:
    explicit UiSFMLManager(const GameState& state);

    // UI methods
    int8_t Decision() override;
    bool Initialize() override;
    void Render() override;
    void ResetUI() override;
    std::string GetAIDifficulty(int8_t difficulty) const override;
    std::string GetFilename() const override;
    bool GetUIType() const override;

    // Log methods
    void SetLog(const std::vector<std::string>& newLog) override;
    void ClearLog() override;
    const std::vector<std::string>& GetLog() const override;
    std::string GetRecentLogLine() const override;
    void SetRecentLogLine(std::string newLogLine) override;

    ~UiSFMLManager();
};
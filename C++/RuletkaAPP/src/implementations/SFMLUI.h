#pragma once
#include <SFML/Graphics.hpp>
#include "LogObserver.h"
#include "UI.h"
#include "ForwardDeclarations.h"
#include "GameEnums.h"
#include "GameConfig.h"
#include <string>
#include <vector>
#include <deque>
#include <cstdint>

class SFMLUI : public UI, public LogObserver
{
private:
    using uint = unsigned int;
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
    bool showSerialization = false;
    bool isWaitingForFilename = false;

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
    std::vector<Button> serializationButtons;

    std::string fileName = "save";
    std::string logLine = "";
    std::deque<std::string> log;
    const std::shared_ptr<IGameState> gs;

    // Drawing methods
    void DrawStatsPanel(float x, float y, bool isHuman);
    void DrawGameLog(float x, float y);
    void DrawDecisionPanel();
    void DrawGameOverScreen(float x, float y);
    /*void DrawWaitForComputerPanel(float x, float y);*/ /*< -to się przyda do multiplayera*/
    void DrawMagazinePanel(float x, float y);
    void DrawDifficultyInfoPanel(float x, float y);
    void DrawFilenameInput(float x, float y);

    // Creation methods
    void CreateMainButtons();
    void CreateItemButtons();
    void CreateDifficultyButtons();
    void CreateSerializationButtons();
    void CreateRestartButtons(float x, float y);
    void CreateFilenameInput(int8_t action);

    // Other window methods
    bool IsWindowOpen() const noexcept;
    void CloseWindow();

    // IO methods
    int8_t HandleGameOverInput(const sf::Vector2i& mousePos) noexcept;
    int8_t HandleNormalGameInput(const sf::Vector2i& mousePos) noexcept;
    int8_t InputDifficultyLevel(const sf::Vector2i& mousePos) noexcept;
    int8_t InputItemChoice(const sf::Vector2i& mousePos) noexcept;
    int8_t InputSerializationType(const sf::Vector2i& mousePos) noexcept;
    int8_t HandleFilenameInput(const sf::Event& event) noexcept;

    // Gettery
    bool isShowingSerializationMenu() const noexcept { return showSerialization; }
    bool IsShowingInventoryMenu() const noexcept { return showInventory; }
    bool IsShowingSaveLoadMenu() const noexcept { return showSaveLoad; }
    bool IsShowingDifficultyMenu() const noexcept { return showDifficulty; }
    bool IsRestartButtonCreated() const noexcept { return restartButtonCreated; }
    bool IsWaitingForFilename() const noexcept { return isWaitingForFilename; }
    bool IsShowingRestartMenu() const noexcept { return showRestart; }

    // Settery
    void SetSerializationMenu(bool newState) { showSerialization = newState; }
    void SetItemMenu(bool newState) { showInventory = newState; }
    void SetSaveLoadMenu(bool newState) { showSaveLoad = newState; }
    void SetDifficultyMenu(bool newState) { showDifficulty = newState; }
    void SetRestartMenu(bool newState) { showRestart = newState; }
    void SetRestartButtonState(bool newState) { restartButtonCreated = newState; }
    void SetCurrentFilenameState(bool newState) { isWaitingForFilename = newState; }
public:
    explicit SFMLUI(const std::shared_ptr<IGameState> gs);

    // UI methods
    int8_t Decision() noexcept override;
    void Initialize() override;
    void Render() override;
    void ResetUI() override;
    std::string GetAIDifficulty(int8_t difficulty) const noexcept override;
    std::string GetFilename() const noexcept override;
    bool GetUIType() const noexcept override;

    // Log methods
    void ClearLog() override;
    const std::deque<std::string>& GetLog() const noexcept override;
    std::string GetRecentLogLine() const noexcept override;
    void GetRecentLogUpdate(std::string newLogUpdate) override;

    ~SFMLUI();
};
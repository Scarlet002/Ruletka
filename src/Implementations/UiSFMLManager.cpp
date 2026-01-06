#include "UiSFMLManager.h"
#include "GameSFMLVersion.h"
#include "GameEnums.h"
#include <iostream>

using std::string;
using std::vector;
using std::to_string;
using std::pair;
using std::cout;

using sf::Color;
using sf::RectangleShape;
using sf::VideoMode;
using sf::FloatRect;
using sf::Font;
using sf::RenderWindow;
using sf::Vector2f;
using sf::Vector2i;
using sf::Keyboard;
using sf::Text;
using sf::Event;
using sf::Mouse;

UiSFMLManager::UiSFMLManager(GameState& gameState)
    : window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ruletka"),
    gameRef(nullptr),
    showInventory(false),
    showSaveLoad(false),
    showDifficulty(false),
    showRestart(false),
    isWaitingForFilename(false),
    currentFileAction(0),
    currentFilename(""),
    restartButtonCreated(false)
{
    gameState.log.reserve(MAX_LOG_LINES);
    if (!font.loadFromFile("arial.ttf"))
    {
        font.loadFromFile("assets/fonts/arial.ttf");
    }
}

bool UiSFMLManager::Initialize()
{
    window.setFramerateLimit(60);
    font.getInfo().family.empty();

    CreateMainButtons();
    CreateItemButtons();
    CreateDifficultyButtons();

    return !font.getInfo().family.empty();
}

void UiSFMLManager::DrawStatsPanel(const GameState& gameState, float x, float y, bool isHuman) {
    const Player& player = isHuman ? gameState.human : gameState.computer;

    string title = isHuman ? "GRACZ" : "KOMPUTER";
    Color color = isHuman ? Color::Green : Color::Red;

    RectangleShape panel(Vector2f(380, 350));
    panel.setPosition(x, y);
    panel.setFillColor(Color(40, 40, 40, 220));
    panel.setOutlineColor(Color::White);
    panel.setOutlineThickness(2);
    window.draw(panel);

    Text titleText(title, font, 28);
    titleText.setFillColor(color);
    titleText.setPosition(x + 20, y + 20);
    window.draw(titleText);

    Text hpText("HP: " + to_string(player.GetHP()) + "/" +
        to_string(gameState.gameConfig.maxPlayerHP), font, 22);
    hpText.setFillColor(Color::White);
    hpText.setPosition(x + 20, y + 70);
    window.draw(hpText);

    float hpPercent = static_cast<float>(player.GetHP()) / gameState.gameConfig.maxPlayerHP;
    RectangleShape hpBarBg(Vector2f(340, 20));
    hpBarBg.setPosition(x + 20, y + 110);
    hpBarBg.setFillColor(Color(50, 50, 50));
    window.draw(hpBarBg);

    RectangleShape hpBar(Vector2f(340 * hpPercent, 20));
    hpBar.setPosition(x + 20, y + 110);
    hpBar.setFillColor(color);
    window.draw(hpBar);

    float itemY = y + 150;
    vector<pair<string, int>> items = {
        {"Pily:", player.GetSaws()},
        {"Piwa:", player.GetBeers()},
        {"Lupy:", player.GetMagnifiers()},
        {"Telefony:", player.GetCellPhones()},
        {"Kajdanki:", player.GetHandCuffs()},
        {"Inwertery:", player.GetInverters()}
    };

    vector<string> icons = { "[P]", "[B]", "[L]", "[T]", "[K]", "[I]" };

    for (size_t i = 0; i < items.size(); i++) {
        Text itemText(icons[i] + " " + items[i].first + " " +
            to_string(items[i].second), font, 18);
        itemText.setFillColor(Color::White);
        itemText.setPosition(x + 20, itemY);
        window.draw(itemText);
        itemY += 32;
    }
}

void UiSFMLManager::DrawMagazinePanel(const GameState& gameState, float x, float y) {
    RectangleShape panel(Vector2f((WINDOW_WIDTH - 40) / 2, 100));
    panel.setPosition(x, y);
    panel.setFillColor(Color(50, 30, 30, 220));
    panel.setOutlineColor(Color::White);
    panel.setOutlineThickness(2.0f);
    window.draw(panel);

    Text title("MAGAZYNEK", font, 20);
    title.setFillColor(Color::Yellow);
    title.setPosition(x + 15, y + 15);
    window.draw(title);

    int full = gameState.magazine.ShowFull();
    int empty = gameState.magazine.ShowEmpty();
    int total = gameState.magazine.ShowBulletCount();

    string statsText = "Pelne: " + to_string(full) +
        "   Puste: " + to_string(empty) +
        "   Razem: " + to_string(total);

    Text stats(statsText, font, 18);
    stats.setFillColor(Color::White);
    stats.setPosition(x + 15, y + 55);
    window.draw(stats);
}

void UiSFMLManager::DrawDifficultyInfoPanel(const GameState& gameState, float x, float y) {
    RectangleShape panel(Vector2f((WINDOW_WIDTH - 40) / 2, 100));
    panel.setPosition(x, y);
    panel.setFillColor(Color(30, 30, 50, 220));
    panel.setOutlineColor(Color::White);
    panel.setOutlineThickness(2.0f);
    window.draw(panel);

    Text title("POZIOM TRUDNOSCI", font, 20);
    title.setFillColor(Color::Magenta);
    title.setPosition(x + 15, y + 15);
    window.draw(title);

    string difficultyText;
    switch (gameState.ai.GetDifficulty()) {
    case GameEnums::EASY: difficultyText = "LATWY"; break;
    case GameEnums::NORMAL: difficultyText = "NORMALNY"; break;
    case GameEnums::HARD: difficultyText = "TRUDNY"; break;
    default: difficultyText = "NIEUSTAWIONO";
    }

    Text difficultyDisplay(difficultyText, font, 22);
    difficultyDisplay.setFillColor(Color::Cyan);
    difficultyDisplay.setPosition(x + 15, y + 55);
    window.draw(difficultyDisplay);
}

void UiSFMLManager::DrawGameLog(GameState& gameState, float x, float y) {
    RectangleShape panel(Vector2f(380, 350));
    panel.setPosition(x, y);
    panel.setFillColor(Color(30, 30, 30, 220));
    panel.setOutlineColor(Color::White);
    panel.setOutlineThickness(2);
    window.draw(panel);

    Text title("LOG GRY", font, 22);
    title.setPosition(x + 20, y + 15);
    title.setFillColor(Color::Green);
    window.draw(title);

    float textY = y + 55;
    for (const auto& line : gameState.log) {
        Text logText(line, font, 18);
        logText.setFillColor(Color::White);
        logText.setPosition(x + 20, textY);
        window.draw(logText);
        textY += 30;
    }
}

void UiSFMLManager::DrawWaitForComputerPanel(float x, float y) {
    RectangleShape panel(Vector2f(WINDOW_WIDTH - 40, 80));
    panel.setPosition(x, y);
    panel.setFillColor(Color(50, 50, 70, 220));
    panel.setOutlineColor(Color::Red);
    panel.setOutlineThickness(2.0f);
    window.draw(panel);

    Text waitText("TRWA TURA KOMPUTERA...", font, 28);
    FloatRect bounds = waitText.getLocalBounds();
    waitText.setOrigin(bounds.width / 2, bounds.height / 2);
    waitText.setPosition(WINDOW_WIDTH / 2, y + 40);
    waitText.setFillColor(Color::Yellow);
    window.draw(waitText);
}

void UiSFMLManager::DrawGameOverScreen(const GameState& gameState, float x, float y) {
    RectangleShape panel(Vector2f(600, 400));
    panel.setPosition(x, y);
    panel.setFillColor(Color(30, 30, 50, 230));
    panel.setOutlineColor(Color::Yellow);
    panel.setOutlineThickness(3.0f);
    window.draw(panel);

    Text gameOverText("KONIEC GRY", font, 48);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    FloatRect bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(bounds.width / 2, bounds.height / 2);
    gameOverText.setPosition(x + 300, y + 70);
    window.draw(gameOverText);

    string winnerText;
    Color winnerColor;
    if (gameState.currentGameState == GameEnums::STATE_HUMAN_WIN) {
        winnerText = "GRACZ WYGRYWA!";
        winnerColor = Color::Green;
    }
    else {
        winnerText = "KOMPUTER WYGRYWA!";
        winnerColor = Color::Red;
    }

    Text winnerDisplay(winnerText, font, 36);
    winnerDisplay.setFillColor(winnerColor);
    winnerDisplay.setStyle(sf::Text::Bold);
    bounds = winnerDisplay.getLocalBounds();
    winnerDisplay.setOrigin(bounds.width / 2, bounds.height / 2);
    winnerDisplay.setPosition(x + 300, y + 150);
    window.draw(winnerDisplay);

    string stats = "Gracz: " + to_string(gameState.human.GetHP()) + " HP | " +
        "Komputer: " + to_string(gameState.computer.GetHP()) + " HP";
    Text statsText(stats, font, 22);
    statsText.setFillColor(Color::White);
    statsText.setPosition(x + 180, y + 210);
    window.draw(statsText);

    if (!restartButtonCreated) {
        CreateRestartButtons(x, y);
    }

    window.draw(restartButton.rect);
    window.draw(restartButton.text);
    window.draw(exitButton.rect);
    window.draw(exitButton.text);
}

void UiSFMLManager::DrawFilenameInput(float x, float y) {
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);

    if (currentFileAction == GameEnums::SAVE) {
        filenameLabel.setString("ZAPIS GRY - Podaj nazwe pliku:");
        filenameLabel.setFillColor(sf::Color::Green);
    }
    else if (currentFileAction == GameEnums::LOAD) {
        filenameLabel.setString("WCZYTYWANIE GRY - Podaj nazwe pliku:");
        filenameLabel.setFillColor(sf::Color::Yellow);
    }

    window.draw(filenameBox);
    window.draw(filenameText);
    window.draw(filenameLabel);

    Text instruction("Wpisz nazwe i nacisnij Enter (Esc - anuluj)", font, 18);
    instruction.setFillColor(sf::Color::White);
    instruction.setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 + 60);
    window.draw(instruction);
}

void UiSFMLManager::DrawDecisionPanel(const GameState& gameState, float x, float y) {
    RectangleShape panel(Vector2f(WINDOW_WIDTH - 20, 50));
    panel.setPosition(x, y);
    panel.setFillColor(Color(50, 50, 50, 220));
    panel.setOutlineColor(Color::White);
    panel.setOutlineThickness(2);
    window.draw(panel);

    auto& buttons = showInventory ? itemButtons :
        showDifficulty ? difficultyButtons :
        mainButtons;

    float totalButtonsWidth = 0;
    for (const auto& btn : buttons) {
        totalButtonsWidth += btn.rect.getSize().x;
    }
    totalButtonsWidth += (buttons.size() - 1) * 8;

    float startX = x + (panel.getSize().x - totalButtonsWidth) / 2;
    float currentX = startX;

    for (size_t i = 0; i < buttons.size(); i++) {
        buttons[i].rect.setPosition(currentX, y + 5);

        window.draw(buttons[i].rect);

        FloatRect bounds = buttons[i].text.getLocalBounds();
        buttons[i].text.setOrigin(bounds.width / 2, bounds.height / 2);
        buttons[i].text.setPosition(currentX + buttons[i].rect.getSize().x / 2,
            y + 5 + buttons[i].rect.getSize().y / 2);

        window.draw(buttons[i].text);

        currentX += buttons[i].rect.getSize().x + 8;
    }
}

void UiSFMLManager::CreateMainButtons() {
    mainButtons.clear();

    float width = 130;
    float height = 40;

    vector<pair<string, int>> buttons = {
        {"Regen", GameEnums::HEAL},
        {"Strzel", GameEnums::SHOOT},
        {"Przedmiot", GameEnums::USEITEM},
        {"Zapisz", GameEnums::SAVE},
        {"Wczytaj", GameEnums::LOAD},
        {"Trudnosc", GameEnums::DIFFICULTY},
        {"Wyjdz", GameEnums::EXIT}
    };

    for (int i = 0; i < buttons.size(); i++) {
        Button btn;
        btn.actionId = buttons[i].second;
        btn.isHovered = false;

        btn.rect.setSize(Vector2f(width, height));
        btn.rect.setPosition(0, 0);
        btn.rect.setFillColor(Color(70, 70, 70));
        btn.rect.setOutlineColor(Color::White);
        btn.rect.setOutlineThickness(1);

        btn.text.setFont(font);
        btn.text.setString(buttons[i].first);
        btn.text.setCharacterSize(16);
        btn.text.setFillColor(Color::White);

        btn.text.setPosition(0, 0);

        mainButtons.push_back(btn);
    }
}

void UiSFMLManager::CreateItemButtons() {
    itemButtons.clear();

    float width = 130;
    float height = 40;

    vector<pair<string, int>> items = {
        {"Kajdanki", GameEnums::HANDCUFFS},
        {"Piwo", GameEnums::BEER},
        {"Lupa", GameEnums::MAGNIFIER},
        {"Pila", GameEnums::SAW},
        {"Telefon", GameEnums::CELLPHONE},
        {"Inwerter", GameEnums::INVERTER}
    };

    for (int i = 0; i < items.size(); i++) {
        Button btn;
        btn.actionId = items[i].second;
        btn.isHovered = false;

        btn.rect.setSize(Vector2f(width, height));
        btn.rect.setPosition(0, 0);
        btn.rect.setFillColor(Color(70, 70, 70));
        btn.rect.setOutlineColor(Color::White);
        btn.rect.setOutlineThickness(1);

        btn.text.setFont(font);
        btn.text.setString(items[i].first);
        btn.text.setCharacterSize(16);
        btn.text.setFillColor(Color::White);
        btn.text.setPosition(0, 0);

        itemButtons.push_back(btn);
    }
}

void UiSFMLManager::CreateDifficultyButtons() {
    difficultyButtons.clear();

    float totalWidth = 3 * 130 + 2 * 8;
    float startX = (WINDOW_WIDTH - totalWidth) / 2;
    float y = 730;
    float width = 130;
    float height = 40;
    float spacing = 8;

    vector<pair<string, int>> buttons = {
        {"Latwy", GameEnums::EASY},
        {"Normalny", GameEnums::NORMAL},
        {"Trudny", GameEnums::HARD},
    };

    for (int i = 0; i < buttons.size(); i++) {
        Button btn;
        btn.actionId = buttons[i].second;
        btn.isHovered = false;

        float btnX = startX + (i * (width + spacing));
        btn.rect.setSize(Vector2f(width, height));
        btn.rect.setPosition(btnX, y);
        btn.rect.setFillColor(Color(70, 70, 90));
        btn.rect.setOutlineColor(Color::Magenta);
        btn.rect.setOutlineThickness(1);

        btn.text.setFont(font);
        btn.text.setString(buttons[i].first);
        btn.text.setCharacterSize(16);
        btn.text.setFillColor(Color::White);

        FloatRect bounds = btn.text.getLocalBounds();
        btn.text.setOrigin(bounds.width / 2, bounds.height / 2);
        btn.text.setPosition(btnX + width / 2, y + height / 2);

        difficultyButtons.push_back(btn);
    }
}

void UiSFMLManager::CreateRestartButtons(float x, float y) {
    restartButton.rect.setSize(Vector2f(200, 60));
    restartButton.rect.setPosition(x + 50, y + 250);
    restartButton.rect.setFillColor(Color(70, 120, 70));
    restartButton.rect.setOutlineColor(Color::White);
    restartButton.rect.setOutlineThickness(2);

    restartButton.text.setFont(font);
    restartButton.text.setString("ZAGRAJ PONOWNIE");
    restartButton.text.setCharacterSize(20);
    restartButton.text.setFillColor(Color::White);
    restartButton.actionId = GameEnums::RESTART_YES;
    restartButton.isHovered = false;

    FloatRect bounds = restartButton.text.getLocalBounds();
    restartButton.text.setOrigin(bounds.width / 2, bounds.height / 2);
    restartButton.text.setPosition(x + 150, y + 280);

    exitButton.rect.setSize(Vector2f(200, 60));
    exitButton.rect.setPosition(x + 350, y + 250);
    exitButton.rect.setFillColor(Color(120, 70, 70));
    exitButton.rect.setOutlineColor(Color::White);
    exitButton.rect.setOutlineThickness(2);

    exitButton.text.setFont(font);
    exitButton.text.setString("WYJSCIE");
    exitButton.text.setCharacterSize(20);
    exitButton.text.setFillColor(Color::White);
    exitButton.actionId = GameEnums::RESTART_NO;
    exitButton.isHovered = false;

    bounds = exitButton.text.getLocalBounds();
    exitButton.text.setOrigin(bounds.width / 2, bounds.height / 2);
    exitButton.text.setPosition(x + 450, y + 280);

    restartButtonCreated = true;
}

void UiSFMLManager::StartFilenameInput(int action) {
    isWaitingForFilename = true;
    currentFileAction = action;
    showSaveLoad = false;

    if (action == GameEnums::SAVE) {
        currentFilename = "save";
        filenameLabel.setString("Podaj nazwe pliku do ZAPISU:");
    }
    else if (action == GameEnums::LOAD) {
        currentFilename = "save";
        filenameLabel.setString("Podaj nazwe pliku do WCZYTANIA:");
    }

    filenameBox.setSize(sf::Vector2f(400, 40));
    filenameBox.setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2);
    filenameBox.setFillColor(sf::Color(50, 50, 70));
    filenameBox.setOutlineColor(sf::Color::Cyan);
    filenameBox.setOutlineThickness(2);

    filenameText.setFont(font);
    filenameText.setString(currentFilename);
    filenameText.setCharacterSize(24);
    filenameText.setFillColor(sf::Color::White);
    filenameText.setPosition(WINDOW_WIDTH / 2 - 190, WINDOW_HEIGHT / 2 + 5);

    filenameLabel.setFont(font);
    filenameLabel.setCharacterSize(20);
    filenameLabel.setFillColor(sf::Color::White);
    filenameLabel.setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 40);
}

void UiSFMLManager::HandleFilenameInput(GameState& gameState, const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            isWaitingForFilename = false;
            showSaveLoad = false;

            if (gameRef && !currentFilename.empty()) {
                if (currentFileAction == GameEnums::SAVE) {
                    gameRef->HandleSaveLoadWithFilename(GameEnums::SAVE, currentFilename);
                }
                else if (currentFileAction == GameEnums::LOAD) {
                    gameRef->HandleSaveLoadWithFilename(GameEnums::LOAD, currentFilename);
                }
            }
        }
        else if (event.key.code == sf::Keyboard::Escape) {
            isWaitingForFilename = false;
            showSaveLoad = false;
            AddToLog(gameState, "Anulowano wybor pliku");
        }
        else if (event.key.code == sf::Keyboard::BackSpace) {
            if (!currentFilename.empty()) {
                currentFilename.pop_back();
                filenameText.setString(currentFilename);
            }
        }
    }
    else if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8) {
            if (!currentFilename.empty()) {
                currentFilename.pop_back();
            }
        }
        else if (event.text.unicode == 13) {
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 128) {
            if (currentFilename.length() < 50) {
                currentFilename += static_cast<char>(event.text.unicode);
            }
        }

        filenameText.setString(currentFilename);
    }
}

void UiSFMLManager::HandleGameOverInput(GameState& gameState, const sf::Vector2i& mousePos) {
    if (restartButtonCreated)
    {
        if (restartButton.rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            if (gameRef) {
                gameRef->HandleRestartChoice(GameEnums::RESTART_YES);
                gameState.waitingForRestartChoice = false;
                gameState.currentGameState = GameEnums::STATE_RUNNING;
            }
            AddToLog(gameState, "Wybrano: Zagraj ponownie");
            return;
        }
        else if (exitButton.rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            if (gameRef) {
                gameRef->HandleRestartChoice(GameEnums::RESTART_NO);
            }
            AddToLog(gameState, "Wybrano: Wyjscie");
            return;
        }
    }
}

void UiSFMLManager::HandleNormalGameInput(GameState& gameState, const sf::Vector2i& mousePos) {
    if (showInventory) {
        for (const auto& btn : itemButtons) {
            if (btn.rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                cout << "DEBUG: Kliknieto przedmiot: " << btn.actionId << std::endl;
                if (gameRef) {
                    gameRef->HandleItemChoice(btn.actionId);
                }
                showInventory = false;
                return;
            }
        }
    }

    if (showSaveLoad) {
        for (const auto& btn : saveLoadButtons) {
            if (btn.rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                cout << "DEBUG: Kliknieto save/load: " << btn.actionId << std::endl;
                StartFilenameInput(btn.actionId);
                return;
            }
        }
    }

    if (showDifficulty) {
        for (const auto& btn : difficultyButtons) {
            if (btn.rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                cout << "DEBUG: Kliknieto trudnosc: " << btn.actionId << std::endl;
                if (gameRef) {
                    gameRef->HandleDifficultyChoice(btn.actionId);
                }
                showDifficulty = false;
                return;
            }
        }
    }

    for (const auto& btn : mainButtons) {
        if (btn.rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            cout << "DEBUG: Kliknieto przycisk: " << btn.actionId << std::endl;

            if (gameRef) {
                gameRef->HandlePlayerChoice(btn.actionId);
            }

            if (btn.actionId == GameEnums::USEITEM) {
                showInventory = true;
            }
            else if (btn.actionId == GameEnums::SAVE || btn.actionId == GameEnums::LOAD) {
                showSaveLoad = true;
            }
            else if (btn.actionId == GameEnums::DIFFICULTY) {
                showDifficulty = true;
            }
            else if (btn.actionId == GameEnums::RESTART_YES || btn.actionId == GameEnums::RESTART_NO)
            {
                showRestart = false;
            }

            return;
        }
    }
}

void UiSFMLManager::ProcessEvents(GameState& gameState) {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
            if (gameRef) {
                gameRef->HandlePlayerChoice(GameEnums::EXIT);
            }
            return;
        }

        if (isWaitingForFilename) {
            HandleFilenameInput(gameState, event);
            return;
        }

        if (event.type == Event::MouseButtonPressed &&
            event.mouseButton.button == Mouse::Left) {

            Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

            if ((gameState.currentGameState == GameEnums::STATE_HUMAN_WIN ||
                gameState.currentGameState == GameEnums::STATE_COMPUTER_WIN) &&
                gameState.waitingForRestartChoice) {
                HandleGameOverInput(gameState, mousePos);
                return;
            }

            if (gameState.currentGameState == GameEnums::STATE_RUNNING) {
                HandleNormalGameInput(gameState, mousePos);
                return;
            }
        }

        if (event.type == Event::KeyPressed &&
            event.key.code == Keyboard::Escape) {
            if (isWaitingForFilename) {
                isWaitingForFilename = false;
                AddToLog(gameState, "Anulowano wybor pliku");
            }
            else if (showInventory) {
                showInventory = false;
                AddToLog(gameState, "Anulowano wybor przedmiotu");
            }
            else if (showSaveLoad) {
                showSaveLoad = false;
            }
            else if (showDifficulty) {
                showDifficulty = false;
            }
            else if (showRestart) {
                showRestart = false;
            }
        }
    }
}

void UiSFMLManager::Render(GameState& gameState) {
    window.clear(Color(20, 20, 30));

    DrawMagazinePanel(gameState, 10, 20);
    DrawDifficultyInfoPanel(gameState, WINDOW_WIDTH / 2 + 10, 20);

    float panelWidth = 380;
    float spacing = 20;
    float totalWidth = 3 * panelWidth + 2 * spacing;
    float startX = (WINDOW_WIDTH - totalWidth) / 2;

    DrawStatsPanel(gameState, startX, 140, true);

    DrawGameLog(gameState, startX + panelWidth + spacing, 140);

    DrawStatsPanel(gameState, startX + 2 * (panelWidth + spacing), 140, false);

    if (gameState.currentGameState == GameEnums::STATE_HUMAN_WIN ||
        gameState.currentGameState == GameEnums::STATE_COMPUTER_WIN) {
        DrawGameOverScreen(gameState, (WINDOW_WIDTH - (WINDOW_WIDTH / 2)) / 2, WINDOW_HEIGHT / 6);
    }
    else {
        if (isWaitingForFilename) {
            DrawFilenameInput(0, 0);
        }
        else if (showInventory) {
            DrawDecisionPanel(gameState, 10, 510);
        }
        else if (showRestart) {
            DrawGameOverScreen(gameState, (WINDOW_WIDTH - (WINDOW_WIDTH / 2)) / 2, WINDOW_HEIGHT / 6);
        }
        else {
            DrawDecisionPanel(gameState, 10, 510);
        }
    }

    window.display();
}

void UiSFMLManager::AddToLog(GameState& gameState, const std::string& message) {
    gameState.log.push_back(message);
    if (gameState.log.size() > MAX_LOG_LINES) {
        gameState.log.erase(gameState.log.begin());
    }
}

void UiSFMLManager::DisplayStats(const GameState& gameState) {
    cout << "Gracz: " << gameState.human.GetHP()
        << " HP, Komputer: " << gameState.computer.GetHP() << " HP\n";
}

void UiSFMLManager::ShowMessage(GameState& gameState, const std::string& message) {
    AddToLog(gameState, message);
}

bool UiSFMLManager::IsWindowOpen() const {
    return window.isOpen();
}

void UiSFMLManager::CloseWindow() {
    if (window.isOpen()) {
        window.close();
    }
}

void UiSFMLManager::SetGameReference(GameSFMLVersion* game) {
    gameRef = game;
}

void UiSFMLManager::ClearLog(GameState& gameState) {
    gameState.log.clear();
}

void UiSFMLManager::ResetUI(GameState& gameState) {
    showInventory = false;
    showSaveLoad = false;
    showDifficulty = false;
    showRestart = false;
    isWaitingForFilename = false;
    restartButtonCreated = false;
    ClearLog(gameState);
}

UiSFMLManager::~UiSFMLManager() {
    CloseWindow();
}
#include "UiSFMLManager.h"
#include "UiManager.h"
#include "GameEngine.h"
#include "GameEnums.h"
#include "GameState.h"
#include "IPlayer.h"
#include "GameConfig.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <memory>

UiSFMLManager::UiSFMLManager(const GameState& state)
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ruletka")
    , state(state)
{
    recentLog.reserve(GameConfig::maxLogsInLine);
    log.reserve(GameConfig::maxLogsInLine);
    if (!font.loadFromFile("arial.ttf"))
    {
        font.loadFromFile("assets/fonts/arial.ttf");
    }
}

bool UiSFMLManager::Initialize()
{
    /*window.setFramerateLimit(60);*/

    CreateMainButtons();
    CreateItemButtons();
    CreateDifficultyButtons();

    return !font.getInfo().family.empty();
}

void UiSFMLManager::DrawStatsPanel(float x, float y, bool isHuman)
{
    const std::unique_ptr<IPlayer>& player = isHuman ? state.human : state.computer;

    std::string title = isHuman ? "GRACZ" : "KOMPUTER";
    sf::Color color = isHuman ? sf::Color::Green : sf::Color::Red;

    sf::RectangleShape panel(sf::Vector2f(380, 350));
    panel.setPosition(x, y);
    panel.setFillColor(sf::Color(40, 40, 40, 220));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(2);
    window.draw(panel);

    sf::Text titleText(title, font, 28);
    titleText.setFillColor(color);
    titleText.setPosition(x + 20, y + 20);
    window.draw(titleText);

    sf::Text hpText("HP: " + std::to_string(player->GetHP()) + "/" +
        std::to_string(GameConfig::maxPlayerHP), font, 22);
    hpText.setFillColor(sf::Color::White);
    hpText.setPosition(x + 20, y + 70);
    window.draw(hpText);

    float hpPercent = static_cast<float>(player->GetHP()) / GameConfig::maxPlayerHP;
    sf::RectangleShape hpBarBg(sf::Vector2f(340, 20));
    hpBarBg.setPosition(x + 20, y + 110);
    hpBarBg.setFillColor(sf::Color(50, 50, 50));
    window.draw(hpBarBg);

    sf::RectangleShape hpBar(sf::Vector2f(340 * hpPercent, 20));
    hpBar.setPosition(x + 20, y + 110);
    hpBar.setFillColor(color);
    window.draw(hpBar);

    float itemY = y + 150;
    std::vector<std::pair<std::string, int8_t>> items =
    {
        {"Pily:", player->GetSaws()},
        {"Piwa:", player->GetBeers()},
        {"Lupy:", player->GetMagnifiers()},
        {"Telefony:", player->GetCellPhones()},
        {"Kajdanki:", player->GetHandCuffs()},
        {"Inwertery:", player->GetInverters()}
    };

    std::vector<std::string> icons = { "[P]", "[B]", "[L]", "[T]", "[K]", "[I]" };

    for (uint8_t i = 0; i < items.size(); ++i)
    {
        sf::Text itemText(icons[i] + " " + items[i].first + " " +
            std::to_string(items[i].second), font, 18);
        itemText.setFillColor(sf::Color::White);
        itemText.setPosition(x + 20, itemY);
        window.draw(itemText);
        itemY += 32;
    }
}

void UiSFMLManager::DrawMagazinePanel(float x, float y)
{
    sf::RectangleShape panel(sf::Vector2f((WINDOW_WIDTH - 40) / 2, 100));
    panel.setPosition(x, y);
    panel.setFillColor(sf::Color(50, 30, 30, 220));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(2.0f);
    window.draw(panel);

    sf::Text title("MAGAZYNEK", font, 20);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(x + 15, y + 15);
    window.draw(title);

    uint8_t full = state.magazine->GetFull();
    uint8_t empty = state.magazine->GetEmpty();
    uint8_t total = state.magazine->GetMagazineSize();

    std::string statsText;

    statsText = "Pelne: "
        + std::to_string(full)
        + " Puste: "
        + std::to_string(empty)
        + " Razem: "
        + std::to_string(total);

    sf::Text stats(statsText, font, 18);
    stats.setFillColor(sf::Color::White);
    stats.setPosition(x + 15, y + 55);
    window.draw(stats);
}

void UiSFMLManager::DrawDifficultyInfoPanel(const float x, float y)
{
    sf::RectangleShape panel(sf::Vector2f((WINDOW_WIDTH - 40) / 2, 100));
    panel.setPosition(x, y);
    panel.setFillColor(sf::Color(30, 30, 50, 220));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(2.0f);
    window.draw(panel);

    sf::Text title("POZIOM TRUDNOSCI", font, 20);
    title.setFillColor(sf::Color::Magenta);
    title.setPosition(x + 15, y + 15);
    window.draw(title);

    std::string difficultyText = "";
    switch (state.turn->GetDifficulty())
    {
        case GameEnums::EASY: difficultyText = "LATWY"; break;
        case GameEnums::NORMAL: difficultyText = "NORMALNY"; break;
        case GameEnums::HARD: difficultyText = "TRUDNY"; break;
        default: difficultyText;
    }

    sf::Text difficultyDisplay(difficultyText, font, 22);
    difficultyDisplay.setFillColor(sf::Color::Cyan);
    difficultyDisplay.setPosition(x + 15, y + 55);
    window.draw(difficultyDisplay);
}

void UiSFMLManager::DrawGameLog(float x, float y)
{
    sf::RectangleShape panel(sf::Vector2f(380, 350));
    panel.setPosition(x, y);
    panel.setFillColor(sf::Color(30, 30, 30, 220));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(2);
    window.draw(panel);

    sf::Text title("LOG GRY", font, 22);
    title.setPosition(x + 20, y + 15);
    title.setFillColor(sf::Color::Green);
    window.draw(title);

    if (!GetLog().empty()) 
    { 
        SetRecentLog(GetLog());
        if (state.turn->GetStarter() == GameEnums::HUMAN
            && state.turn->GetChoice() == GameEnums::NO_CHOICE)
        {
            ClearLog();
        }
    }

    float textY = y + 55;
    for (const auto& line : GetRecentLog())
    {
        sf::Text logText(line, font, 18);
        logText.setFillColor(sf::Color::White);
        logText.setPosition(x + 20, textY);
        window.draw(logText);
        textY += 30;
    }
}

void UiSFMLManager::DrawWaitForComputerPanel(float x, float y)
{
    sf::RectangleShape panel(sf::Vector2f(WINDOW_WIDTH - 40, 80));
    panel.setPosition(x, y);
    panel.setFillColor(sf::Color(50, 50, 70, 220));
    panel.setOutlineColor(sf::Color::Red);
    panel.setOutlineThickness(2.0f);
    window.draw(panel);

    sf::Text waitText("TRWA TURA KOMPUTERA...", font, 28);
    sf::FloatRect bounds = waitText.getLocalBounds();
    waitText.setOrigin(bounds.width / 2, bounds.height / 2);
    waitText.setPosition(WINDOW_WIDTH / 2.f, y + 40);
    waitText.setFillColor(sf::Color::Yellow);
    window.draw(waitText);
}

void UiSFMLManager::DrawGameOverScreen(const float x, float y)
{
    sf::RectangleShape panel(sf::Vector2f(600, 400));
    panel.setPosition(x, y);
    panel.setFillColor(sf::Color(30, 30, 50, 230));
    panel.setOutlineColor(sf::Color::Yellow);
    panel.setOutlineThickness(3.0f);
    window.draw(panel);

    sf::Text gameOverText("KONIEC GRY", font, 48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    sf::FloatRect bounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(bounds.width / 2, bounds.height / 2);
    gameOverText.setPosition(x + 300, y + 70);
    window.draw(gameOverText);

    std::string winnerText;
    sf::Color winnerColor;
    if (state.human->IsAlive())
    {
        winnerText = "GRACZ WYGRYWA!";
        winnerColor = sf::Color::Green;
    }
    else
    {
        winnerText = "KOMPUTER WYGRYWA!";
        winnerColor = sf::Color::Red;
    }

    sf::Text winnerDisplay(winnerText, font, 36);
    winnerDisplay.setFillColor(winnerColor);
    winnerDisplay.setStyle(sf::Text::Bold);
    bounds = winnerDisplay.getLocalBounds();
    winnerDisplay.setOrigin(bounds.width / 2, bounds.height / 2);
    winnerDisplay.setPosition(x + 300, y + 150);
    window.draw(winnerDisplay);

    std::string stats = "Gracz: "
        + std::to_string(state.human->GetHP()) + " HP | " +
        "Komputer: " + std::to_string(state.computer->GetHP()) + " HP";
    sf::Text statsText(stats, font, 22);
    statsText.setFillColor(sf::Color::White);
    statsText.setPosition(x + 180, y + 210);
    window.draw(statsText);

    if (!IsRestartButtonCreated()) { CreateRestartButtons(x, y); }

    window.draw(restartButton.rect);
    window.draw(restartButton.text);
    window.draw(exitButton.rect);
    window.draw(exitButton.text);
}

void UiSFMLManager::DrawFilenameInput(float x, float y)
{
    CreateFilenameInput(state.turn->GetChoice());
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);

    if (state.turn->GetChoice() == GameEnums::SAVE)
    {
        filenameLabel.setString("ZAPIS GRY - Podaj nazwe pliku:");
        filenameLabel.setFillColor(sf::Color::Green);
    }
    else if (state.turn->GetChoice() == GameEnums::LOAD)
    {
        filenameLabel.setString("WCZYTYWANIE GRY - Podaj nazwe pliku:");
        filenameLabel.setFillColor(sf::Color::Yellow);
    }

    window.draw(filenameBox);
    window.draw(filenameText);
    window.draw(filenameLabel);

    sf::Text instruction("Wpisz nazwe i nacisnij Enter (Esc - anuluj)", font, 18);
    instruction.setFillColor(sf::Color::White);
    instruction.setPosition(WINDOW_WIDTH / 2.f - 200, WINDOW_HEIGHT / 2.f + 60);
    window.draw(instruction);
}

void UiSFMLManager::DrawDecisionPanel(const float x, float y)
{
    sf::RectangleShape panel(sf::Vector2f(WINDOW_WIDTH - 20, 50));
    panel.setPosition(x, y);
    panel.setFillColor(sf::Color(50, 50, 50, 220));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(2);
    window.draw(panel);

    auto& buttons =
        IsShowingInventoryMenu() ?
        itemButtons : IsShowingDifficultyMenu() ? difficultyButtons : mainButtons;

    float totalButtonsWidth = 0;
    for (const auto& btn : buttons)
    {
        totalButtonsWidth += btn.rect.getSize().x;
    }
    totalButtonsWidth += (buttons.size() - 1) * 8;

    float startX = x + (panel.getSize().x - totalButtonsWidth) / 2;
    float currentX = startX;

    for (uint8_t i = 0; i < buttons.size(); ++i)
    {
        buttons[i].rect.setPosition(currentX, y + 5);

        window.draw(buttons[i].rect);

        sf::FloatRect bounds = buttons[i].text.getLocalBounds();
        buttons[i].text.setOrigin(bounds.width / 2, bounds.height / 2);
        buttons[i].text.setPosition(currentX + buttons[i].rect.getSize().x / 2,
            y + 5 + buttons[i].rect.getSize().y / 2);

        window.draw(buttons[i].text);
        currentX += buttons[i].rect.getSize().x + 8;
    }
}

void UiSFMLManager::CreateMainButtons()
{
    mainButtons.clear();

    float width = 130;
    float height = 40;

    std::vector<std::pair<std::string, int8_t>> buttons =
    {
        {"Regen", GameEnums::HEAL},
        {"Strzel", GameEnums::SHOOT},
        {"Przedmiot", GameEnums::USEITEM},
        {"Zapisz", GameEnums::SAVE},
        {"Wczytaj", GameEnums::LOAD},
        {"Trudnosc", GameEnums::DIFFICULTY},
        {"Wyjdz", GameEnums::EXIT}
    };

    for (uint8_t i = 0; i < buttons.size(); ++i)
    {
        Button btn;
        btn.actionId = buttons[i].second;
        btn.isHovered = false;
        btn.rect.setSize(sf::Vector2f(width, height));
        btn.rect.setPosition(0, 0);
        btn.rect.setFillColor(sf::Color(70, 70, 70));
        btn.rect.setOutlineColor(sf::Color::White);
        btn.rect.setOutlineThickness(1);
        btn.text.setFont(font);
        btn.text.setString(buttons[i].first);
        btn.text.setCharacterSize(16);
        btn.text.setFillColor(sf::Color::White);
        btn.text.setPosition(0, 0);
        mainButtons.push_back(btn);
    }
}

void UiSFMLManager::CreateItemButtons()
{
    itemButtons.clear();

    float width = 130;
    float height = 40;

    std::vector<std::pair<std::string, int8_t>> items =
    {
        {"Kajdanki", GameEnums::HANDCUFFS},
        {"Piwo", GameEnums::BEER},
        {"Lupa", GameEnums::MAGNIFIER},
        {"Pila", GameEnums::SAW},
        {"Telefon", GameEnums::CELLPHONE},
        {"Inwerter", GameEnums::INVERTER}
    };

    for (int8_t i = 0; i < items.size(); ++i)
    {
        Button btn;
        btn.actionId = items[i].second;
        btn.isHovered = false;
        btn.rect.setSize(sf::Vector2f(width, height));
        btn.rect.setPosition(0, 0);
        btn.rect.setFillColor(sf::Color(70, 70, 70));
        btn.rect.setOutlineColor(sf::Color::White);
        btn.rect.setOutlineThickness(1);
        btn.text.setFont(font);
        btn.text.setString(items[i].first);
        btn.text.setCharacterSize(16);
        btn.text.setFillColor(sf::Color::White);
        btn.text.setPosition(0, 0);
        itemButtons.push_back(btn);
    }
}

void UiSFMLManager::CreateDifficultyButtons()
{
    difficultyButtons.clear();

    float totalWidth = 3 * 130 + 2 * 8;
    float startX = (WINDOW_WIDTH - totalWidth) / 2.f;
    float y = 730;
    float width = 130;
    float height = 40;
    float spacing = 8;

    std::vector<std::pair<std::string, int8_t>> buttons =
    {
        {"Latwy", GameEnums::EASY},
        {"Normalny", GameEnums::NORMAL},
        {"Trudny", GameEnums::HARD},
    };

    for (int8_t i = 0; i < buttons.size(); ++i)
    {
        Button btn;
        btn.actionId = buttons[i].second;
        btn.isHovered = false;

        float btnX = startX + (i * (width + spacing));
        btn.rect.setSize(sf::Vector2f(width, height));
        btn.rect.setPosition(btnX, y);
        btn.rect.setFillColor(sf::Color(70, 70, 90));
        btn.rect.setOutlineColor(sf::Color::Magenta);
        btn.rect.setOutlineThickness(1);

        btn.text.setFont(font);
        btn.text.setString(buttons[i].first);
        btn.text.setCharacterSize(16);
        btn.text.setFillColor(sf::Color::White);

        sf::FloatRect bounds = btn.text.getLocalBounds();
        btn.text.setOrigin(bounds.width / 2, bounds.height / 2);
        btn.text.setPosition(btnX + width / 2, y + height / 2);

        difficultyButtons.push_back(btn);
    }
}

void UiSFMLManager::CreateRestartButtons(float x, float y)
{
    restartButton.rect.setSize(sf::Vector2f(200, 60));
    restartButton.rect.setPosition(x + 50, y + 250);
    restartButton.rect.setFillColor(sf::Color(70, 120, 70));
    restartButton.rect.setOutlineColor(sf::Color::White);
    restartButton.rect.setOutlineThickness(2);

    restartButton.text.setFont(font);
    restartButton.text.setString("ZAGRAJ PONOWNIE");
    restartButton.text.setCharacterSize(20);
    restartButton.text.setFillColor(sf::Color::White);
    restartButton.actionId = GameEnums::RESTART_YES;
    restartButton.isHovered = false;

    sf::FloatRect bounds = restartButton.text.getLocalBounds();
    restartButton.text.setOrigin(bounds.width / 2, bounds.height / 2);
    restartButton.text.setPosition(x + 150, y + 280);

    exitButton.rect.setSize(sf::Vector2f(200, 60));
    exitButton.rect.setPosition(x + 350, y + 250);
    exitButton.rect.setFillColor(sf::Color(120, 70, 70));
    exitButton.rect.setOutlineColor(sf::Color::White);
    exitButton.rect.setOutlineThickness(2);

    exitButton.text.setFont(font);
    exitButton.text.setString("WYJSCIE");
    exitButton.text.setCharacterSize(20);
    exitButton.text.setFillColor(sf::Color::White);
    exitButton.actionId = GameEnums::RESTART_NO;
    exitButton.isHovered = false;

    bounds = exitButton.text.getLocalBounds();
    exitButton.text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    exitButton.text.setPosition(x + 450, y + 280);

    SetRestartButtonState(true);
}

void UiSFMLManager::CreateFilenameInput(int8_t action)
{
    filenameBox.setSize(sf::Vector2f(400, 40));
    filenameBox.setPosition(WINDOW_WIDTH / 2.f - 200, WINDOW_HEIGHT / 2.f);
    filenameBox.setFillColor(sf::Color(50, 50, 70));
    filenameBox.setOutlineColor(sf::Color::Cyan);
    filenameBox.setOutlineThickness(2);

    filenameText.setFont(font);
    filenameText.setString(fileName);
    filenameText.setCharacterSize(24);
    filenameText.setFillColor(sf::Color::White);
    filenameText.setPosition(WINDOW_WIDTH / 2.f - 190, WINDOW_HEIGHT / 2.f + 5);

    filenameLabel.setFont(font);
    filenameLabel.setCharacterSize(20);
    filenameLabel.setFillColor(sf::Color::White);
    filenameLabel.setPosition(WINDOW_WIDTH / 2.f - 200, WINDOW_HEIGHT / 2.f - 40);
}

int8_t UiSFMLManager::HandleFilenameInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Enter
            || event.key.code == sf::Keyboard::Escape)
        {
            SetCurrentFilenameState(false);
            SetSaveLoadMenu(false);
            return GameEnums::SAVE;
        }
        else if (event.key.code == sf::Keyboard::BackSpace)
        {
            if (!fileName.empty())
            {
                fileName.pop_back();
                filenameText.setString(fileName);
            }
        }
    }
    else if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode >= 32
            && event.text.unicode < 128)
        {
            fileName += static_cast<char>(event.text.unicode);
        }
        filenameText.setString(fileName);
    }
	return GameEnums::NO_CHOICE;
}

int8_t UiSFMLManager::HandleGameOverInput(const sf::Vector2i& mousePos)
{
    if (state.turn->GetCurrentMenu() == GameEnums::RESTART_MENU)
    {
        if (restartButton.rect.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            waitingForRestartChoice = false;
            return GameEnums::RESTART_YES;
        }
        else if (exitButton.rect.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            return GameEnums::RESTART_NO;
        }
        else
        {
            return GameEnums::NO_CHOICE;
        }
    }
    return GameEnums::NO_CHOICE;
}

int8_t UiSFMLManager::HandleNormalGameInput(const sf::Vector2i& mousePos)
{
    if (state.turn->GetCurrentMenu() == GameEnums::INVENTORY_MENU) 
    { 
        return InputItemChoice(mousePos);
    }
    else if (state.turn->GetCurrentMenu() == GameEnums::DIFFICULTY_MENU) 
    { 
        return InputDifficultyLevel(mousePos);
    }
    else
    {
        for (const auto& btn : mainButtons)
        {
            if (btn.rect.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                std::cout << "DEBUG: Kliknieto przycisk: " << btn.actionId << '\n';
                if (btn.actionId == GameEnums::USEITEM) { SetItemMenu(true); }
                else if (btn.actionId == GameEnums::DIFFICULTY) { SetDifficultyMenu(true); }
                else if (btn.actionId == GameEnums::SAVE
                    || btn.actionId == GameEnums::LOAD) 
                { 
                    SetCurrentFilenameState(true);
                    SetSaveLoadMenu(true);
                }
                return btn.actionId;
            }
        }
        return GameEnums::NO_CHOICE;
    }
}

int8_t UiSFMLManager::InputDifficultyLevel(const sf::Vector2i& mousePos)
{
    if (state.turn->GetCurrentMenu() == GameEnums::DIFFICULTY_MENU)
    {
        for (const auto& btn : difficultyButtons)
        {
            if (btn.rect.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                std::cout << "DEBUG: Kliknieto trudnosc: " << std::to_string(btn.actionId) << '\n';
                SetDifficultyMenu(false);
                return btn.actionId;
            }
        }
        return GameEnums::NO_CHOICE;
    }
    return GameEnums::NO_CHOICE;
}

int8_t UiSFMLManager::InputItemChoice(const sf::Vector2i& mousePos)
{
    if (state.turn->GetCurrentMenu() == GameEnums::INVENTORY_MENU)
    {
        for (const auto& btn : itemButtons)
        {
            if (btn.rect.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                std::cout << "DEBUG: Kliknieto przedmiot: " << std::to_string(btn.actionId) << '\n';
                SetItemMenu(false);
                return btn.actionId;
            }
        }
		return GameEnums::NO_CHOICE;
    }
    return GameEnums::NO_CHOICE;
}

int8_t UiSFMLManager::Decision()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            if (state.turn->GetIsOnePlayerAlive())
            {
                return HandleGameOverInput(mousePos);
            }
            else { return HandleNormalGameInput(mousePos); }
        }
        else if (state.turn->GetCurrentMenu() == GameEnums::SAVE_MENU
            || state.turn->GetCurrentMenu() == GameEnums::LOAD_MENU)
        {
            return HandleFilenameInput(event);
        }
        else if (event.type == sf::Event::KeyPressed
            && event.key.code == sf::Keyboard::Escape
            && (state.turn->GetCurrentMenu() == GameEnums::SAVE_MENU
            || state.turn->GetCurrentMenu() == GameEnums::LOAD_MENU))
        {
            if (IsWaitingForFilename()) { SetCurrentFilenameState(false); }
            else if (IsShowingInventoryMenu()) { SetItemMenu(false); }
            else if (IsShowingSaveLoadMenu()) { SetSaveLoadMenu(false); }
            else if (IsShowingDifficultyMenu()) { SetDifficultyMenu(false); }
            else if (IsRestartButtonCreated()) { SetRestartMenu(false); }
            return GameEnums::NO_CHOICE;
        }
    }
    return GameEnums::NO_CHOICE;
}

void UiSFMLManager::Render()
{
    window.clear(sf::Color(20, 20, 30));
    if (state.turn->GetCurrentMenu() == GameEnums::SAVE_MENU
        || state.turn->GetCurrentMenu() == GameEnums::LOAD_MENU) 
    { 
        DrawFilenameInput(0, 0);
    }
    else if (state.turn->GetIsOnePlayerAlive())
    {
        DrawGameOverScreen((WINDOW_WIDTH - (WINDOW_WIDTH / 2.f)) / 2.f
            , (WINDOW_HEIGHT) / 6.f);
    }
    else 
    { 
        DrawDecisionPanel(10, 510);
        DrawMagazinePanel(10, 20);
        DrawDifficultyInfoPanel(WINDOW_WIDTH / 2.f + 10, 20);
        float panelWidth = 380;
        float spacing = 20;
        float totalWidth = 3 * panelWidth + 2 * spacing;
        float startX = (WINDOW_WIDTH - totalWidth) / 2.f;
        DrawStatsPanel(startX, 140, true);
        DrawGameLog(startX + panelWidth + spacing, 140);
        DrawStatsPanel(startX + 2 * (panelWidth + spacing), 140, false);
    }
    window.display();
}

void UiSFMLManager::ResetUI()
{
    SetItemMenu(false);
    SetSaveLoadMenu(false);
    SetDifficultyMenu(false);
    SetRestartMenu(false);
    SetCurrentFilenameState(false);
    SetRestartButtonState(false);
    ClearLog();
}

bool UiSFMLManager::GetUIType() const { return false; }

std::string UiSFMLManager::GetFilename() const { return fileName; }

void UiSFMLManager::SetRecentLog(const std::vector<std::string>& newRecentLog) { recentLog = newRecentLog; }

const std::vector<std::string>& UiSFMLManager::GetRecentLog() const { return recentLog; }

bool UiSFMLManager::IsWindowOpen() const { return window.isOpen(); }

void UiSFMLManager::CloseWindow() { if (window.isOpen()) { window.close(); } }

void UiSFMLManager::ClearLog() { log.clear(); }

const std::vector<std::string>& UiSFMLManager::GetLog() const { return log; }

void UiSFMLManager::SetLog(const std::vector<std::string>& newLog) { log = newLog; }

std::string UiSFMLManager::GetRecentLogLine() const { return log.back(); }

void UiSFMLManager::SetRecentLogLine(std::string newLogLine) { log.push_back(newLogLine); }

std::string UiSFMLManager::GetAIDifficulty(int8_t difficulty) const
{
    if (difficulty == GameEnums::EASY) { return "latwy"; }
    else if (difficulty == GameEnums::NORMAL) { return "normalny"; }
    else { return "trudny"; }
}

UiSFMLManager::~UiSFMLManager() { CloseWindow(); }
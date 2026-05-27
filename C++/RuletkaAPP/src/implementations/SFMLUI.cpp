#include "SFMLUI.h"
#include "ConsoleUI.h"
#include "GameEngine.h"
#include "GameEnums.h"
#include "IGameState.h"
#include "LogObserver.h"
#include "IPlayer.h"
#include "Magazine.h"
#include "AIState.h"
#include "GameLoopState.h"
#include "SerializationState.h"
#include "HP.h"
#include "IInventory.h"
#include "DecisionState.h"
#include "GameConfig.h"
#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <cstdint>
#include <memory>

SFMLUI::SFMLUI(const std::shared_ptr<IGameState> gs)
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Ruletka", sf::Style::Default)
    , gs(gs)
    , log() {}

void SFMLUI::Initialize()
{
    font.loadFromFile("assets/fonts/arial.ttf");
    window.setVerticalSyncEnabled(true);

    CreateMainButtons();
    CreateItemButtons();
    CreateDifficultyButtons();
    CreateSerializationButtons();
}

void SFMLUI::DrawStatsPanel(float x, float y, bool isHuman)
{
    const auto& player = isHuman ? gs->GetHuman() : gs->GetComputer();
    const auto& playerHP = player.GetType() ? gs->GetHumanHP() : gs->GetComputerHP();
    const auto& playerInventory = player.GetType() ? gs->GetHumanInventory() : gs->GetComputerInventory();

    std::string title = isHuman ? gs->GetHuman().GetName() : gs->GetComputer().GetName();
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

    sf::Text hpText("HP: " + std::to_string(playerHP.GetHP()) + "/" +
        std::to_string(GameConfig::maxPlayerHP), font, 22);
    hpText.setFillColor(sf::Color::White);
    hpText.setPosition(x + 20, y + 70);
    window.draw(hpText);

    float hpPercent = static_cast<float>(playerHP.GetHP()) / GameConfig::maxPlayerHP;
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
        {"Pily:", playerInventory.GetItemCount(GameEnums::SAW)},
        {"Piwa:", playerInventory.GetItemCount(GameEnums::BEER)},
        {"Lupy:", playerInventory.GetItemCount(GameEnums::MAGNIFIER)},
        {"Telefony:", playerInventory.GetItemCount(GameEnums::CELLPHONE)},
        {"Kajdanki:", playerInventory.GetItemCount(GameEnums::HANDCUFFS)},
        {"Inwertery:", playerInventory.GetItemCount(GameEnums::INVERTER)}
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

void SFMLUI::DrawMagazinePanel(float x, float y)
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

    uint8_t full = gs->GetMagazine().GetFull();
    uint8_t empty = gs->GetMagazine().GetEmpty();
    uint8_t total = gs->GetMagazine().GetMagazineSize();

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

void SFMLUI::DrawDifficultyInfoPanel(const float x, float y)
{
    sf::RectangleShape panel(sf::Vector2f((WINDOW_WIDTH - 40) / 2, 100));
    panel.setPosition(x, y);
    panel.setFillColor(sf::Color(30, 30, 50, 220));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(2.0f);
    window.draw(panel);

    std::string difficultyText = "";
    switch (gs->GetAIState().GetDifficulty())
    {
        case GameEnums::EASY: difficultyText = "LATWY"; break;
        case GameEnums::NORMAL: difficultyText = "NORMALNY"; break;
        case GameEnums::HARD: difficultyText = "TRUDNY"; break;
        default: difficultyText;
    }

    std::string serializationType = "";
    switch (gs->GetSerializationState().GetSerializationType())
    {
    case GameEnums::JSON: serializationType = "JSON"; break;
    case GameEnums::TXT: serializationType = "TXT"; break;
    default: serializationType;
    }

    std::vector<std::pair<std::string, std::string>> Texts =
    {
        {"POZIOM TRUDNOSCI:", difficultyText},
        {"FORMAT SERIALIZACJI:", serializationType},
    };
    
    for (uint8_t i = 0; i < Texts.size(); ++i)
    {
        sf::Text infoText(Texts[i].first + " " + Texts[i].second, font, 18);
        infoText.setFillColor(sf::Color::White);
        infoText.setPosition(x + 15, y + 15 + i * 30);
        window.draw(infoText);
	}

}

void SFMLUI::DrawGameLog(float x, float y)
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

    if (log.size() >= GameConfig::maxLogsRendered)
    {
        log.pop_front();
    }

    float textY = y + 55;
    for (const auto& line : log)
    {
        sf::Text logText(line, font, 18);
        logText.setFillColor(sf::Color::White);
        logText.setPosition(x + 20, textY);
        window.draw(logText);
        textY += 30;
    }
}

//void SFMLUI::DrawWaitForComputerPanel(float x, float y) <- to się przyda do multiplayera
//{
//    sf::RectangleShape panel(sf::Vector2f(WINDOW_WIDTH - 40, 80));
//    panel.setPosition(x, y);
//    panel.setFillColor(sf::Color(50, 50, 70, 220));
//    panel.setOutlineColor(sf::Color::Red);
//    panel.setOutlineThickness(2.0f);
//    window.draw(panel);
//
//    sf::Text waitText("TRWA TURA KOMPUTERA...", font, 28);
//    sf::FloatRect bounds = waitText.getLocalBounds();
//    waitText.setOrigin(bounds.width / 2, bounds.height / 2);
//    waitText.setPosition(WINDOW_WIDTH / 2.f, y + 40);
//    waitText.setFillColor(sf::Color::Yellow);
//    window.draw(waitText);
//}

void SFMLUI::DrawGameOverScreen(const float x, float y)
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
    if (gs->GetHuman().IsAlive())
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
        + std::to_string(gs->GetHumanHP().GetHP()) + " HP | " +
        "Komputer: " + std::to_string(gs->GetComputerHP().GetHP()) + " HP";
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

void SFMLUI::DrawFilenameInput(float x, float y)
{
    CreateFilenameInput(gs->GetDecisionState().GetChoice());
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);

    if (gs->GetDecisionState().GetChoice() == GameEnums::SAVE)
    {
        filenameLabel.setString("ZAPIS GRY - Podaj nazwe pliku:");
        filenameLabel.setFillColor(sf::Color::Green);
    }
    else if (gs->GetDecisionState().GetChoice() == GameEnums::LOAD)
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

void SFMLUI::DrawDecisionPanel()
{
    float panelWidth = window.getSize().x - 20;
    float panelHeight = 50;
    float panelX = 10;
    float panelY = window.getSize().y - panelHeight - 10;

    sf::RectangleShape panel(sf::Vector2f(panelWidth, panelHeight));
    panel.setPosition(panelX, panelY);
    panel.setFillColor(sf::Color(50, 50, 50, 220));
    panel.setOutlineColor(sf::Color::White);
    panel.setOutlineThickness(2);
    window.draw(panel);

    auto& buttons = IsShowingInventoryMenu() 
                  ? itemButtons : IsShowingDifficultyMenu() 
                  ? difficultyButtons : isShowingSerializationMenu()
                  ? serializationButtons : mainButtons;

    float totalButtonsWidth = 0.f;
    for (const auto& button : buttons)
    {
        totalButtonsWidth += button.rect.getSize().x;
    }
    totalButtonsWidth += buttons.size() * 8;

    float startX = panelX + (panel.getSize().x - totalButtonsWidth) / 2;
    float currentX = startX;

    for (uint8_t i = 0; i < buttons.size(); ++i)
    {
        buttons[i].rect.setPosition(currentX, panelY + 5);

        window.draw(buttons[i].rect);

        sf::FloatRect bounds = buttons[i].text.getLocalBounds();
        buttons[i].text.setOrigin(bounds.width / 2, bounds.height / 2);
        buttons[i].text.setPosition(currentX + buttons[i].rect.getSize().x / 2,
            panelY + 5 + buttons[i].rect.getSize().y / 2);

        window.draw(buttons[i].text);
        currentX += buttons[i].rect.getSize().x + 8;
    }
}

void SFMLUI::CreateMainButtons()
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
        {"Serializacja", GameEnums::SERIALIZATION},
        {"Wyjdz", GameEnums::EXIT}
    };

    for (uint8_t i = 0; i < buttons.size(); ++i)
    {
        Button button;
        button.actionId = buttons[i].second;
        button.isHovered = false;
        button.rect.setSize(sf::Vector2f(width, height));
        button.rect.setPosition(0, 0);
        button.rect.setFillColor(sf::Color(70, 70, 70));
        button.rect.setOutlineColor(sf::Color::White);
        button.rect.setOutlineThickness(1);
        button.text.setFont(font);
        button.text.setString(buttons[i].first);
        button.text.setCharacterSize(16);
        button.text.setFillColor(sf::Color::White);
        button.text.setPosition(0, 0);
        mainButtons.push_back(button);
    }
}

void SFMLUI::CreateItemButtons()
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
        Button button;
        button.actionId = items[i].second;
        button.isHovered = false;
        button.rect.setSize(sf::Vector2f(width, height));
        button.rect.setPosition(0, 0);
        button.rect.setFillColor(sf::Color(70, 70, 70));
        button.rect.setOutlineColor(sf::Color::White);
        button.rect.setOutlineThickness(1);
        button.text.setFont(font);
        button.text.setString(items[i].first);
        button.text.setCharacterSize(16);
        button.text.setFillColor(sf::Color::White);
        button.text.setPosition(0, 0);
        itemButtons.push_back(button);
    }
}

void SFMLUI::CreateSerializationButtons()
{
    serializationButtons.clear();

    float totalWidth = 2 * 130 + 1 * 8;
    float startX = (WINDOW_WIDTH - totalWidth) / 2.f;
    float y = 730;
    float width = 130;
    float height = 40;
    float spacing = 8;

    std::vector<std::pair<std::string, int8_t>> buttons =
    {
        {"JSON", GameEnums::JSON},
        {"TXT", GameEnums::TXT}
    };

    for (int8_t i = 0; i < buttons.size(); ++i)
    {
        Button button;
        button.actionId = buttons[i].second;
        button.isHovered = false;

        float buttonX = startX + (i * (width + spacing));
        button.rect.setSize(sf::Vector2f(width, height));
        button.rect.setPosition(buttonX, y);
        button.rect.setFillColor(sf::Color(70, 70, 70));
        button.rect.setOutlineColor(sf::Color::White);
        button.rect.setOutlineThickness(1);

        button.text.setFont(font);
        button.text.setString(buttons[i].first);
        button.text.setCharacterSize(16);
        button.text.setFillColor(sf::Color::White);

        sf::FloatRect bounds = button.text.getLocalBounds();
        button.text.setOrigin(bounds.width / 2, bounds.height / 2);
        button.text.setPosition(buttonX + width / 2, y + height / 2);

        serializationButtons.push_back(button);
    }
}

void SFMLUI::CreateDifficultyButtons()
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
        Button button;
        button.actionId = buttons[i].second;
        button.isHovered = false;

        float buttonX = startX + (i * (width + spacing));
        button.rect.setSize(sf::Vector2f(width, height));
        button.rect.setPosition(buttonX, y);
        button.rect.setFillColor(sf::Color(70, 70, 70));
        button.rect.setOutlineColor(sf::Color::White);
        button.rect.setOutlineThickness(1);

        button.text.setFont(font);
        button.text.setString(buttons[i].first);
        button.text.setCharacterSize(16);
        button.text.setFillColor(sf::Color::White);

        sf::FloatRect bounds = button.text.getLocalBounds();
        button.text.setOrigin(bounds.width / 2, bounds.height / 2);
        button.text.setPosition(buttonX + width / 2, y + height / 2);

        difficultyButtons.push_back(button);
    }
}

void SFMLUI::CreateRestartButtons(float x, float y)
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

void SFMLUI::CreateFilenameInput(int8_t action)
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

int8_t SFMLUI::HandleFilenameInput(const sf::Event& event) noexcept
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Enter
            || event.key.code == sf::Keyboard::Escape)
        {
            SetCurrentFilenameState(false);
            SetSaveLoadMenu(false);
            if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::SAVE_MENU)
            {
                return GameEnums::SAVE;
            }
            if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::LOAD_MENU)
            {
                return GameEnums::LOAD;
            }
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

int8_t SFMLUI::HandleGameOverInput(const sf::Vector2i& mousePos) noexcept
{
    if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::RESTART_MENU)
    {
        if (restartButton.rect.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
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

int8_t SFMLUI::HandleNormalGameInput(const sf::Vector2i& mousePos) noexcept
{
    if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::INVENTORY_MENU)
    { 
        return InputItemChoice(mousePos);
    }
    else if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::DIFFICULTY_MENU)
    { 
        return InputDifficultyLevel(mousePos);
    }
    else if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::SERIALIZATION_MENU)
    {
        return InputSerializationType(mousePos);
    }
    else
    {
        for (const auto& button : mainButtons)
        {
            if (button.rect.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                if (button.actionId == GameEnums::USEITEM) { SetItemMenu(true); }
                else if (button.actionId == GameEnums::DIFFICULTY) { SetDifficultyMenu(true); }
                else if (button.actionId == GameEnums::SERIALIZATION) { SetSerializationMenu(true); }
                else if (button.actionId == GameEnums::SAVE
                    || button.actionId == GameEnums::LOAD) 
                { 
                    SetCurrentFilenameState(true);
                    SetSaveLoadMenu(true);
                }
                return button.actionId;
            }
        }
        return GameEnums::NO_CHOICE;
    }
}

int8_t SFMLUI::InputDifficultyLevel(const sf::Vector2i& mousePos) noexcept
{
    if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::DIFFICULTY_MENU)
    {
        for (const auto& button : difficultyButtons)
        {
            if (button.rect.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                SetDifficultyMenu(false);
                return button.actionId;
            }
        }
        return GameEnums::NO_CHOICE;
    }
    return GameEnums::NO_CHOICE;
}

int8_t SFMLUI::InputSerializationType(const sf::Vector2i& mousePos) noexcept
{
    if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::SERIALIZATION_MENU)
    {
        for (const auto& button : serializationButtons)
        {
            if (button.rect.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                SetSerializationMenu(false);
                return button.actionId;
            }
        }
        return GameEnums::NO_CHOICE;
    }
    return GameEnums::NO_CHOICE;
}

int8_t SFMLUI::InputItemChoice(const sf::Vector2i& mousePos) noexcept
{
    if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::INVENTORY_MENU)
    {
        for (const auto& button : itemButtons)
        {
            if (button.rect.getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                SetItemMenu(false);
                return button.actionId;
            }
        }
		return GameEnums::NO_CHOICE;
    }
    return GameEnums::NO_CHOICE;
}

int8_t SFMLUI::Decision() noexcept
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Resized) 
        {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            if (gs->GetGameLoopState().GetIsOnePlayerAlive())
            {
                return HandleGameOverInput(mousePos);
            }
            else { return HandleNormalGameInput(mousePos); }
        }
        else if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::SAVE_MENU
            || gs->GetDecisionState().GetCurrentMenu() == GameEnums::LOAD_MENU)
        {
            return HandleFilenameInput(event);
        }
        else if (event.type == sf::Event::KeyPressed
            && event.key.code == sf::Keyboard::Escape
            && (gs->GetDecisionState().GetCurrentMenu() == GameEnums::SAVE_MENU
            || gs->GetDecisionState().GetCurrentMenu() == GameEnums::LOAD_MENU))
        {
            if (IsWaitingForFilename()) { SetCurrentFilenameState(false); }
            else if (IsShowingInventoryMenu()) { SetItemMenu(false); }
            else if (IsShowingSaveLoadMenu()) { SetSaveLoadMenu(false); }
            else if (IsShowingDifficultyMenu()) { SetDifficultyMenu(false); }
            else if (IsRestartButtonCreated()) { SetRestartMenu(false); }
            else if (isShowingSerializationMenu()) { SetSerializationMenu(false); }
            return GameEnums::NO_CHOICE;
        }
    }
    return GameEnums::NO_CHOICE;
}

void SFMLUI::Render()
{
    // Test FPS

    /*static int frameCount = 0;
    static sf::Clock clock;
    frameCount++;
    if (clock.getElapsedTime().asSeconds() >= 1.0f) {
        std::cout << "FPS: " << frameCount << std::endl;
        frameCount = 0;
        clock.restart();
    }*/

    window.clear(sf::Color(20, 20, 30));
    if (gs->GetDecisionState().GetCurrentMenu() == GameEnums::SAVE_MENU
        || gs->GetDecisionState().GetCurrentMenu() == GameEnums::LOAD_MENU)
    { 
        DrawFilenameInput(0, 0);
    }
    else if (gs->GetGameLoopState().GetIsOnePlayerAlive())
    {
        DrawGameOverScreen((WINDOW_WIDTH - (WINDOW_WIDTH / 2.f)) / 2.f, (WINDOW_HEIGHT) / 6.f);
    }
    else 
    { 
        DrawDecisionPanel();
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

void SFMLUI::ResetUI()
{
    SetItemMenu(false);
    SetSaveLoadMenu(false);
    SetDifficultyMenu(false);
    SetRestartMenu(false);
    SetCurrentFilenameState(false);
    SetRestartButtonState(false);
    SetSerializationMenu(false);
    ClearLog();
}

bool SFMLUI::GetUIType() const noexcept { return false; }

std::string SFMLUI::GetFilename() const noexcept { return fileName; }

bool SFMLUI::IsWindowOpen() const noexcept { return window.isOpen(); }

void SFMLUI::CloseWindow() { if (window.isOpen()) { window.close(); } }

void SFMLUI::ClearLog() { log.clear(); }

const std::deque<std::string>& SFMLUI::GetLog() const noexcept { return log; }

std::string SFMLUI::GetRecentLogLine() const noexcept
{
    if (log.empty()) { return ""; }
    return log.back();
}

void SFMLUI::GetRecentLogUpdate(std::string newLogUpdate) { log.push_back(newLogUpdate); }

std::string SFMLUI::GetAIDifficulty(int8_t difficulty) const noexcept
{
    if (difficulty == GameEnums::EASY) { return "latwy"; }
    else if (difficulty == GameEnums::NORMAL) { return "normalny"; }
    else { return "trudny"; }
}

SFMLUI::~SFMLUI() { CloseWindow(); }
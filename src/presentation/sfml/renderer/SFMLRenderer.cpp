#include "SFMLRenderer.h"
#include "AIState.h"
#include "ApplicationState.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "HP.h"
#include "Inventory.h"
#include "Logger.h"
#include "Magazine.h"
#include "Player.h"
#include "SFMLColors.hpp"
#include "SFMLInitializer.h"
#include "SFMLLayout.hpp"
#include "SFMLText.hpp"
#include "SerializationState.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <boost/static_string/static_string.hpp>
#include <cstdint>
#include <format>
#include <iterator>
#include <string>
#include <string_view>
#include <utility>

SFMLRenderer::SFMLRenderer(const ApplicationState& app, const DomainState& domain, Logger& logger,
                           SFMLInitializer& initializer, sf::RenderWindow& window) noexcept
    : m_app(app), m_domain(domain), m_logger(logger), m_initializer(initializer), m_window(window)
{
    const auto windowSize = window.getSize();
    m_windowSize = sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
}

auto SFMLRenderer::GetScaleFactor() const -> float
{
    const auto scaleX = m_windowSize.x / static_cast<float>(GameConfig::WINDOW_WIDTH);
    const auto scaleY = m_windowSize.y / static_cast<float>(GameConfig::WINDOW_HEIGHT);
    return std::clamp((std::min)(scaleX, scaleY), SFMLLayout::MIN_SCALE_FACTOR, SFMLLayout::MAX_SCALE_FACTOR);
}

auto SFMLRenderer::ScaleFont(float baseSize) const -> unsigned int
{
    return static_cast<unsigned int>(baseSize * GetScaleFactor());
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
auto SFMLRenderer::ScaleFontWithWidthLimit(float baseSize, float panelWidth, float maxCharacters) const -> unsigned int
{
    const auto sizeByHeight = ScaleFont(baseSize);
    const auto maxSizeByWidth =
        (panelWidth * SFMLLayout::WIDTH_LIMIT_RATIO) / (maxCharacters * SFMLLayout::CHAR_WIDTH_RATIO);
    return maxSizeByWidth < static_cast<float>(sizeByHeight) ? static_cast<unsigned int>(maxSizeByWidth) : sizeByHeight;
}

auto SFMLRenderer::DrawPanel(sf::FloatRect rectangle, sf::Color fill, bool withBorder) -> void
{
    auto& bufferRectangle = m_initializer.GetBufferRectangle();
    m_initializer.ResetBufferRectangle();
    bufferRectangle.setSize(rectangle.size);
    bufferRectangle.setPosition(rectangle.position);
    bufferRectangle.setFillColor(fill);
    if (withBorder)
    {
        bufferRectangle.setOutlineColor(sf::Color::White);
        bufferRectangle.setOutlineThickness(SFMLLayout::BORDER_THICKNESS);
    }
    m_window.draw(bufferRectangle);
}

auto SFMLRenderer::DrawText(std::string_view text, sf::Vector2f position, unsigned int size, sf::Color color,
                            sf::Text::Style style) -> float
{
    auto& bufferText = m_initializer.GetBufferText();
    m_initializer.ResetBufferText();
    auto& bufferString = m_initializer.GetBufferString();
    bufferString = text;
    bufferText.setString(bufferString);
    bufferText.setCharacterSize(size);
    bufferText.setFillColor(color);
    bufferText.setStyle(style);
    bufferText.setPosition(position);
    m_window.draw(bufferText);
    return bufferText.getLocalBounds().size.x;
}

auto SFMLRenderer::DrawTextCentered(std::string_view text, sf::Vector2f center, unsigned int size, sf::Color color,
                                    sf::Text::Style style) -> void
{
    auto& bufferText = m_initializer.GetBufferText();
    m_initializer.ResetBufferText();
    auto& bufferString = m_initializer.GetBufferString();
    bufferString = text;
    bufferText.setString(bufferString);
    bufferText.setCharacterSize(size);
    bufferText.setFillColor(color);
    bufferText.setStyle(style);
    const auto bounds = bufferText.getLocalBounds();
    bufferText.setOrigin(
        sf::Vector2f(bounds.size.x / SFMLLayout::CENTER_DIVISOR, bounds.size.y / SFMLLayout::CENTER_DIVISOR));
    bufferText.setPosition(center);
    m_window.draw(bufferText);
}

auto SFMLRenderer::DrawTextTopCentered(std::string_view text, sf::Vector2f position, unsigned int size, sf::Color color,
                                       sf::Text::Style style) -> void
{
    auto& bufferText = m_initializer.GetBufferText();
    m_initializer.ResetBufferText();
    auto& bufferString = m_initializer.GetBufferString();
    bufferString = text;
    bufferText.setString(bufferString);
    bufferText.setCharacterSize(size);
    bufferText.setFillColor(color);
    bufferText.setStyle(style);
    const auto bounds = bufferText.getLocalBounds();
    bufferText.setOrigin(sf::Vector2f(bounds.size.x / SFMLLayout::CENTER_DIVISOR, 0.0F));
    bufferText.setPosition(position);
    m_window.draw(bufferText);
}

auto SFMLRenderer::DrawButton(Button& button, sf::FloatRect rectangle, sf::Color fill, unsigned int labelSize) -> void
{
    button.m_rect.setSize(rectangle.size);
    button.m_rect.setPosition(rectangle.position);
    button.m_rect.setFillColor(fill);
    button.m_rect.setOutlineColor(sf::Color::White);
    button.m_rect.setOutlineThickness(SFMLLayout::BORDER_THICKNESS);

    button.m_label.setCharacterSize(labelSize);
    button.m_label.setFillColor(sf::Color::White);
    const auto bounds = button.m_label.getLocalBounds();
    button.m_label.setOrigin(
        sf::Vector2f(bounds.size.x / SFMLLayout::CENTER_DIVISOR, bounds.size.y / SFMLLayout::CENTER_DIVISOR));
    button.m_label.setPosition(
        sf::Vector2f(rectangle.position.x + (rectangle.size.x / SFMLLayout::CENTER_DIVISOR),
                     rectangle.position.y + (rectangle.size.y / SFMLLayout::BUTTON_LABEL_VERTICAL_DIVISOR)));

    m_window.draw(button.m_rect);
    m_window.draw(button.m_label);
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
auto SFMLRenderer::DrawSegmentedBar(sf::FloatRect rectangle, uint8_t filled, uint8_t maxSegments, sf::Color fillColor,
                                    sf::Color emptyColor) -> void
{
    DrawPanel(rectangle, sf::Color::Transparent, true);

    auto& bufferRectangle = m_initializer.GetBufferRectangle();
    m_initializer.ResetBufferRectangle();
    const auto segmentWidth = (rectangle.size.x - (static_cast<float>(maxSegments + 1) * SFMLLayout::SEGMENT_GAP)) /
                              static_cast<float>(maxSegments);
    bufferRectangle.setSize(sf::Vector2f(segmentWidth, rectangle.size.y - SFMLLayout::BORDER_THICKNESS));

    for (auto index = 0UZ; index < maxSegments; ++index)
    {
        bufferRectangle.setPosition(
            sf::Vector2f(rectangle.position.x + SFMLLayout::SEGMENT_GAP +
                             (static_cast<float>(index) * (segmentWidth + SFMLLayout::SEGMENT_GAP)),
                         rectangle.position.y + SFMLLayout::SEGMENT_GAP));
        bufferRectangle.setFillColor(index < filled ? fillColor : emptyColor);
        m_window.draw(bufferRectangle);
    }
}

auto SFMLRenderer::DrawStatsPanel(sf::FloatRect rectangle, const bool isHuman) -> void
{
    const auto& player = isHuman ? m_domain.GetHuman() : m_domain.GetComputer();
    const auto playerColor = isHuman ? SFMLColors::HUMAN_COLOR : SFMLColors::COMPUTER_COLOR;

    DrawPanel(rectangle, SFMLColors::PANEL_BACKGROUND_COLOR);

    const auto marginX = rectangle.size.x * SFMLLayout::STATS_MARGIN_X;
    const auto marginY = rectangle.size.y * SFMLLayout::STATS_MARGIN_Y;
    const auto barWidth = rectangle.size.x - (SFMLLayout::CENTER_DIVISOR * marginX);
    const auto titleSize =
        ScaleFontWithWidthLimit(SFMLLayout::FONT_SIZE_TITLE, rectangle.size.x, SFMLLayout::MAX_CHARS_TITLE);
    const auto textSize =
        ScaleFontWithWidthLimit(SFMLLayout::FONT_SIZE_NORMAL, rectangle.size.x, SFMLLayout::MAX_CHARS_BODY);

    DrawTextTopCentered(
        player.GetName(),
        {rectangle.position.x + (rectangle.size.x / SFMLLayout::CENTER_DIVISOR), rectangle.position.y + marginY},
        titleSize, playerColor, sf::Text::Bold);

    const auto startY =
        rectangle.position.y + marginY + (static_cast<float>(titleSize) * SFMLLayout::TITLE_OFFSET_RATIO);
    const auto availableHeight = (rectangle.position.y + rectangle.size.y - marginY) - startY;
    const auto barHeight = rectangle.size.y * SFMLLayout::STATS_BAR_HEIGHT_RATIO;
    const auto textHeight = static_cast<float>(textSize) * SFMLLayout::TEXT_HEIGHT_RATIO;
    const auto totalElementHeight = availableHeight / SFMLLayout::STATS_ROW_COUNT;

    auto gap = (totalElementHeight - textHeight - barHeight) * SFMLLayout::STATS_ROW_GAP_RATIO;
    gap = std::max<float>(gap, 0.0F);

    auto currentY = startY;

    // clang-format off
    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    const auto drawRow = [&](std::string_view label, uint8_t count, uint8_t max, sf::Color textColor,
                             sf::Color barColor) -> void
    // clang-format on
    {
        DrawText(label, {rectangle.position.x + marginX, currentY + gap}, textSize, textColor);
        DrawSegmentedBar({{rectangle.position.x + marginX, currentY + gap + textHeight + gap}, {barWidth, barHeight}},
                         count, max, barColor);
        currentY += totalElementHeight;
    };

    drawRow(SFMLText::LABEL_HP, player.GetHP().GetHP(), GameConfig::MAX_PLAYER_HP, sf::Color::White, playerColor);

    for (const auto& item : GameConfig::ITEM_TYPES)
    {
        drawRow(item.first, player.GetInventory().GetItemCount(item.second), GameConfig::MAX_ITEMS, sf::Color::White,
                SFMLColors::BAR_PRIMARY_COLOR);
    }

    auto totalItems = GameConfig::MIN_ITEMS;
    for (const auto& item : GameConfig::ITEM_TYPES)
    {
        totalItems += player.GetInventory().GetItemCount(item.second);
    }
    drawRow(SFMLText::LABEL_TOTAL, totalItems, GameConfig::MAX_ITEMS, SFMLColors::TEXT_HIGHLIGHT_COLOR,
            SFMLColors::BAR_SECONDARY_COLOR);
}

auto SFMLRenderer::DrawMagazinePanel(sf::FloatRect rectangle) -> void
{
    DrawPanel(rectangle, SFMLColors::PANEL_BACKGROUND_COLOR);

    const auto& magazine = m_domain.GetMagazine();
    const auto statsSize =
        ScaleFontWithWidthLimit(SFMLLayout::FONT_SIZE_TINY, rectangle.size.x, SFMLLayout::MAX_CHARS_LABEL);
    const auto marginX = rectangle.size.x * SFMLLayout::MAGAZINE_MARGIN_X;
    const auto marginY = rectangle.size.y * SFMLLayout::MAGAZINE_MARGIN_Y;
    const auto barHeight = rectangle.size.y * SFMLLayout::MAGAZINE_BAR_HEIGHT_RATIO;

    auto currentY = rectangle.position.y + marginY;

    const auto drawRow = [&](std::string_view label, uint8_t count, sf::Color color) -> void {
        const auto labelWidth = DrawText(label, {rectangle.position.x + marginX, currentY}, statsSize, color);
        const auto barX = rectangle.position.x + (marginX * 2) + labelWidth;
        const auto barWidth = (rectangle.position.x + rectangle.size.x - marginX) - barX;
        DrawSegmentedBar({{barX, currentY + (static_cast<float>(statsSize) * SFMLLayout::MAGAZINE_ROW_OFFSET_RATIO)},
                          {barWidth, barHeight}},
                         count, GameConfig::MAX_BULLETS, color);
        currentY += static_cast<float>(statsSize) + (marginY * 2);
    };

    drawRow(SFMLText::LABEL_BLANK, magazine.GetBullets(GameEnums::MagazineChamber::BLANK),
            SFMLColors::BAR_PRIMARY_COLOR);
    drawRow(SFMLText::LABEL_LIVE, magazine.GetBullets(GameEnums::MagazineChamber::LIVE),
            SFMLColors::BAR_SECONDARY_COLOR);
    drawRow(SFMLText::LABEL_TOTAL, magazine.GetMagazineSize(), SFMLColors::BAR_CRITICAL_COLOR);
}

auto SFMLRenderer::DrawDifficultyInfoPanel(sf::FloatRect rectangle) -> void
{
    DrawPanel(rectangle, SFMLColors::PANEL_BACKGROUND_COLOR);

    const auto infoSize =
        ScaleFontWithWidthLimit(SFMLLayout::FONT_SIZE_SMALL, rectangle.size.x, SFMLLayout::MAX_CHARS_LABEL);
    const auto marginX = rectangle.size.x * SFMLLayout::INFO_MARGIN_X;
    const auto marginY = rectangle.size.y * SFMLLayout::INFO_MARGIN_Y;

    const auto difficultyText =
        GameConfig::DIFFICULTY_TYPES[std::to_underlying(m_app.GetAIState().GetDifficulty())].first;
    const auto serializationText =
        GameConfig::SERIALIZATION_TYPES[std::to_underlying(m_app.GetSerializationState().GetSerializationType())].first;

    auto& bufferString = m_initializer.GetBufferString();

    bufferString.clear();
    std::format_to(std::back_inserter(bufferString), SFMLText::FMT_DIFFICULTY, difficultyText);
    const auto textWidth = DrawText(bufferString, {rectangle.position.x + marginX, rectangle.position.y + marginY},
                                    infoSize, sf::Color::White);

    bufferString.clear();
    std::format_to(std::back_inserter(bufferString), SFMLText::FMT_SERIALIZATION, serializationText);
    DrawText(bufferString, {rectangle.position.x + (2 * marginX) + textWidth, rectangle.position.y + marginY}, infoSize,
             sf::Color::White);
}

auto SFMLRenderer::DrawGameLog(sf::FloatRect rectangle) -> void
{
    DrawPanel(rectangle, SFMLColors::PANEL_BACKGROUND_COLOR);

    const auto titleSize =
        ScaleFontWithWidthLimit(SFMLLayout::FONT_SIZE_TITLE, rectangle.size.x, SFMLLayout::MAX_CHARS_TITLE);
    const auto logSize =
        ScaleFontWithWidthLimit(SFMLLayout::FONT_SIZE_SUBTITLE, rectangle.size.x, SFMLLayout::MAX_CHARS_LOG_LINE);
    const auto marginX = rectangle.size.x * SFMLLayout::LOG_MARGIN_X;
    const auto marginY = rectangle.size.y * SFMLLayout::LOG_MARGIN_Y;

    DrawTextTopCentered(
        SFMLText::TITLE_GAME_LOG,
        {rectangle.position.x + (rectangle.size.x / SFMLLayout::CENTER_DIVISOR), rectangle.position.y + marginY},
        titleSize, sf::Color::White, sf::Text::Bold);

    auto textY =
        rectangle.position.y + (2 * marginY) + (static_cast<float>(titleSize) * SFMLLayout::LOG_TITLE_OFFSET_RATIO);
    const auto lineHeight = static_cast<float>(logSize) * SFMLLayout::LINE_HEIGHT_RATIO;
    const auto maxTextY = rectangle.position.y + rectangle.size.y - marginY;

    const auto humanName = m_domain.GetHuman().GetName();
    const auto computerName = m_domain.GetComputer().GetName();

    const auto logs = m_logger.GetLogs();
    auto tempHead = logs.m_head;
    for (auto index = 0UZ; index < GameConfig::MAX_LOGS; ++index)
    {
        if (textY + lineHeight > maxTextY)
        {
            break;
        }

        if (logs.m_logs[tempHead].empty())
        {
            tempHead = (tempHead + 1) % GameConfig::MAX_LOGS;
            continue;
        }

        const auto& lineView = std::string_view(logs.m_logs[tempHead]);
        tempHead = (tempHead + 1) % GameConfig::MAX_LOGS;
        auto currentX = rectangle.position.x + marginX;
        auto position = 0UZ;

        while (position < lineView.length())
        {
            const auto humanPosition = lineView.find(humanName, position);
            const auto computerPosition = lineView.find(computerName, position);
            const auto hasHuman = humanPosition != std::string::npos;
            const auto hasComputer = computerPosition != std::string::npos;

            if (!hasHuman && !hasComputer)
            {
                DrawText(lineView.substr(position), {currentX, textY}, logSize, sf::Color::White);
                break;
            }

            const auto useHuman = hasHuman && (!hasComputer || humanPosition < computerPosition);
            const auto nextPosition = useHuman ? humanPosition : computerPosition;
            const auto foundName = useHuman ? humanName : computerName;
            const auto foundColor = useHuman ? SFMLColors::HUMAN_COLOR : SFMLColors::COMPUTER_COLOR;

            if (nextPosition > position)
            {
                currentX += DrawText(lineView.substr(position, nextPosition - position), {currentX, textY}, logSize,
                                     sf::Color::White);
            }
            currentX += DrawText(foundName, {currentX, textY}, logSize, foundColor);
            position = nextPosition + foundName.length();
        }
        textY += lineHeight;
    }
}

auto SFMLRenderer::DrawGameOverScreen() -> void
{
    DrawPanel({{0.0F, 0.0F}, m_windowSize}, SFMLColors::PANEL_BACKGROUND_COLOR, false);

    const auto gameOverSize =
        ScaleFontWithWidthLimit(SFMLLayout::FONT_SIZE_DISPLAY, m_windowSize.x, SFMLLayout::MAX_CHARS_DISPLAY);
    const auto winnerSize =
        ScaleFontWithWidthLimit(SFMLLayout::FONT_SIZE_TITLE, m_windowSize.x, SFMLLayout::MAX_CHARS_BODY);
    const auto statsSize =
        ScaleFontWithWidthLimit(SFMLLayout::FONT_SIZE_TITLE, m_windowSize.x, SFMLLayout::MAX_CHARS_STATS);

    DrawTextCentered(
        SFMLText::TITLE_GAME_OVER,
        {m_windowSize.x / SFMLLayout::CENTER_DIVISOR, m_windowSize.y * SFMLLayout::GAME_OVER_TITLE_Y_RATIO},
        gameOverSize, sf::Color::White, sf::Text::Bold);

    const auto humanWins = m_domain.GetHuman().IsAlive() == GameEnums::YesNo::YES;
    const auto& winner = humanWins ? m_domain.GetHuman() : m_domain.GetComputer();
    const auto winnerColor = humanWins ? SFMLColors::HUMAN_COLOR : SFMLColors::COMPUTER_COLOR;

    boost::static_string<GameConfig::LOG_LINE_RESERVE> text;
    std::format_to(std::back_inserter(text), SFMLText::FMT_WINNER, winner.GetName());
    DrawTextCentered(
        text, {m_windowSize.x / SFMLLayout::CENTER_DIVISOR, m_windowSize.y * SFMLLayout::GAME_OVER_WINNER_Y_RATIO},
        winnerSize, winnerColor, sf::Text::Bold);

    text.clear();
    std::format_to(std::back_inserter(text), SFMLText::FMT_STATS, m_domain.GetHuman().GetName(),
                   m_domain.GetHumanHP().GetHP(), m_domain.GetComputer().GetName(), m_domain.GetComputerHP().GetHP());
    DrawTextCentered(
        text, {m_windowSize.x / SFMLLayout::CENTER_DIVISOR, m_windowSize.y * SFMLLayout::GAME_OVER_STATS_Y_RATIO},
        statsSize, sf::Color::White);

    auto buttonWidth = (std::min)(m_windowSize.x * SFMLLayout::BUTTON_WIDTH_RATIO, SFMLLayout::BUTTON_MAX_WIDTH);
    const auto spacing = buttonWidth * SFMLLayout::BUTTON_SPACING_RATIO;
    const auto maxTotal = m_windowSize.x * SFMLLayout::BUTTON_MAX_TOTAL_RATIO;
    if ((2 * buttonWidth) + spacing > maxTotal)
    {
        buttonWidth = (std::max)((maxTotal - spacing) / SFMLLayout::CENTER_DIVISOR, SFMLLayout::BUTTON_MIN_WIDTH);
    }
    const auto buttonHeight =
        (std::max)(SFMLLayout::BUTTON_MIN_HEIGHT, m_windowSize.y * SFMLLayout::BUTTON_HEIGHT_RATIO);
    const auto startX = (m_windowSize.x - ((2 * buttonWidth) + spacing)) / SFMLLayout::CENTER_DIVISOR;
    const auto buttonY = m_windowSize.y * SFMLLayout::GAME_OVER_BUTTONS_Y_RATIO;

    const auto maxSizeByWidth =
        (buttonWidth - SFMLLayout::BUTTON_PADDING) /
        (static_cast<float>(SFMLLayout::BUTTON_MAX_LABEL_LENGTH) * SFMLLayout::CHAR_WIDTH_RATIO);
    const auto fontSizeByHeight = buttonHeight * SFMLLayout::CHAR_WIDTH_RATIO;
    const auto buttonLabelSize = std::clamp(static_cast<unsigned int>((std::min)(maxSizeByWidth, fontSizeByHeight)),
                                            SFMLLayout::BUTTON_MIN_FONT_SIZE, SFMLLayout::BUTTON_MAX_FONT_SIZE);

    auto& buttons = m_initializer.GetRestartButtons();
    DrawButton(buttons.front(), {{startX, buttonY}, {buttonWidth, buttonHeight}}, SFMLColors::BUTTON_EXIT_COLOR,
               buttonLabelSize);
    DrawButton(buttons.back(), {{startX + buttonWidth + spacing, buttonY}, {buttonWidth, buttonHeight}},
               SFMLColors::BUTTON_RESTART_COLOR, buttonLabelSize);
}

auto SFMLRenderer::DrawFilenameInput() -> void
{
    DrawPanel({{0.0F, 0.0F}, m_windowSize}, SFMLColors::OVERLAY_BACKGROUND_COLOR, false);

    auto& filenameBox = m_initializer.GetFilenameBox();
    auto& filenameText = m_initializer.GetFilenameText();
    auto& filenameLabel = m_initializer.GetFilenameLabel();

    const auto isSave = m_app.GetGameLoopState().GetCurrentMenu() == GameEnums::Window::SAVE_MENU;
    auto& bufferString = m_initializer.GetBufferString();
    bufferString = isSave ? SFMLText::PROMPT_SAVE : SFMLText::PROMPT_LOAD;
    filenameLabel.setString(bufferString);
    filenameLabel.setFillColor(isSave ? SFMLColors::HUMAN_COLOR : SFMLColors::TEXT_HIGHLIGHT_COLOR);

    const auto boxWidth = m_windowSize.x * SFMLLayout::FILENAME_BOX_WIDTH_RATIO;
    const auto boxHeight = m_windowSize.y * SFMLLayout::FILENAME_BOX_HEIGHT_RATIO;
    const auto boxX = (m_windowSize.x / SFMLLayout::CENTER_DIVISOR) - (boxWidth / SFMLLayout::CENTER_DIVISOR);
    const auto boxY = (m_windowSize.y / SFMLLayout::CENTER_DIVISOR) - (boxHeight / SFMLLayout::CENTER_DIVISOR);

    const auto labelSize = ScaleFontWithWidthLimit(SFMLLayout::FONT_SIZE_LABEL, boxWidth, SFMLLayout::MAX_CHARS_LABEL);
    filenameLabel.setCharacterSize(labelSize);
    filenameLabel.setPosition(sf::Vector2f(
        boxX, boxY - boxHeight - (static_cast<float>(labelSize) * SFMLLayout::FILENAME_LABEL_OFFSET_RATIO)));
    m_window.draw(filenameLabel);

    filenameBox.setSize(sf::Vector2f(boxWidth, boxHeight));
    filenameBox.setPosition(sf::Vector2f(boxX, boxY));
    filenameBox.setFillColor(SFMLColors::FILENAME_BOX_COLOR);
    filenameBox.setOutlineColor(SFMLColors::FILENAME_BOX_BORDER_COLOR);
    filenameBox.setOutlineThickness(SFMLLayout::BORDER_THICKNESS);
    m_window.draw(filenameBox);

    const auto filenameLength = static_cast<float>(filenameText.getString().getSize());
    auto textSize = static_cast<float>(
        ScaleFontWithWidthLimit(SFMLLayout::FONT_SIZE_BODY, boxWidth, SFMLLayout::MAX_CHARS_FILENAME));
    if (filenameLength > SFMLLayout::FILENAME_TEXT_LENGTH_LIMIT)
    {
        textSize = (std::min)(textSize, boxWidth * SFMLLayout::WIDTH_LIMIT_RATIO /
                                            (filenameLength * SFMLLayout::CHAR_WIDTH_RATIO));
    }
    filenameText.setCharacterSize(static_cast<unsigned int>(textSize));
    filenameText.setFillColor(sf::Color::White);
    filenameText.setPosition(sf::Vector2f(
        boxX + SFMLLayout::FILENAME_TEXT_PADDING,
        boxY + ((boxHeight - (textSize * SFMLLayout::FILENAME_TEXT_VERTICAL_DIVISOR)) / SFMLLayout::CENTER_DIVISOR)));
    m_window.draw(filenameText);

    DrawText(SFMLText::HINT_FILENAME, {boxX, boxY + boxHeight + SFMLLayout::FILENAME_HINT_OFFSET},
             ScaleFontWithWidthLimit(SFMLLayout::FONT_SIZE_TINY, boxWidth, SFMLLayout::MAX_CHARS_HINT),
             sf::Color::White);
}

auto SFMLRenderer::DrawDecisionPanel(sf::FloatRect rectangle) -> void
{
    auto* buttons = &m_initializer.GetMainButtons();
    const auto menu = m_app.GetGameLoopState().GetCurrentMenu();
    if (menu == GameEnums::Window::INVENTORY_MENU)
    {
        buttons = &m_initializer.GetItemButtons();
    }
    else if (menu == GameEnums::Window::DIFFICULTY_MENU)
    {
        buttons = &m_initializer.GetDifficultyButtons();
    }
    else if (menu == GameEnums::Window::SERIALIZATION_MENU)
    {
        buttons = &m_initializer.GetSerializationButtons();
    }

    if (buttons->empty())
    {
        return;
    }

    const auto buttonWidth = rectangle.size.x / static_cast<float>(buttons->size());
    const auto labelSize =
        ScaleFontWithWidthLimit(SFMLLayout::FONT_SIZE_LABEL, buttonWidth, SFMLLayout::MAX_CHARS_DISPLAY);
    auto currentX = rectangle.position.x + ((rectangle.size.x - (buttonWidth * static_cast<float>(buttons->size()))) /
                                            SFMLLayout::CENTER_DIVISOR);

    for (auto& button : *buttons)
    {
        DrawButton(button, {{currentX, rectangle.position.y}, {buttonWidth, rectangle.size.y}},
                   SFMLColors::BUTTON_FILL_COLOR, labelSize);
        currentX += buttonWidth;
    }
}

auto SFMLRenderer::Render() -> void
{
    const auto& gameLoop = m_app.GetGameLoopState();
    if (gameLoop.GetRenderFlag() == GameEnums::YesNo::NO)
    {
        return;
    }

    const auto windowSize = m_window.getSize();
    m_windowSize = sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));

    if (m_windowSize.x < static_cast<float>(GameConfig::WINDOW_WIDTH) ||
        m_windowSize.y < static_cast<float>(GameConfig::WINDOW_HEIGHT))
    {
        m_window.clear(SFMLColors::INVALID_WINDOW_COLOR);
        m_window.display();
        return;
    }

    m_window.clear(SFMLColors::WINDOW_BACKGROUND_COLOR);

    if (gameLoop.GetCurrentMenu() == GameEnums::Window::SAVE_MENU ||
        gameLoop.GetCurrentMenu() == GameEnums::Window::LOAD_MENU)
    {
        DrawFilenameInput();
    }
    else if (gameLoop.GetIsOnePlayerAlive() == GameEnums::YesNo::YES)
    {
        DrawGameOverScreen();
    }
    else
    {
        const auto topHeight = m_windowSize.y * SFMLLayout::TOP_PANEL_HEIGHT_RATIO;
        const auto topWidth = (m_windowSize.x - (2 * SFMLLayout::PANEL_GAP)) / SFMLLayout::CENTER_DIVISOR;
        const auto decisionHeight =
            (std::max)(SFMLLayout::DECISION_PANEL_MIN_HEIGHT, m_windowSize.y * SFMLLayout::DECISION_PANEL_HEIGHT_RATIO);
        const auto decisionY = m_windowSize.y - decisionHeight - SFMLLayout::PANEL_GAP;
        const auto mainStartY = SFMLLayout::PANEL_GAP + topHeight;
        const auto mainHeight = decisionY - mainStartY;
        const auto mainWidth = (m_windowSize.x - (2 * SFMLLayout::PANEL_GAP)) / SFMLLayout::MAIN_PANEL_COLUMNS;

        DrawMagazinePanel({{SFMLLayout::PANEL_GAP, SFMLLayout::PANEL_GAP}, {topWidth, topHeight}});
        DrawDifficultyInfoPanel({{SFMLLayout::PANEL_GAP + topWidth, SFMLLayout::PANEL_GAP}, {topWidth, topHeight}});

        DrawStatsPanel({{SFMLLayout::PANEL_GAP, mainStartY}, {mainWidth, mainHeight}}, true);
        DrawGameLog({{SFMLLayout::PANEL_GAP + mainWidth, mainStartY}, {mainWidth, mainHeight}});
        DrawStatsPanel({{SFMLLayout::PANEL_GAP + (2 * mainWidth), mainStartY}, {mainWidth, mainHeight}}, false);

        DrawDecisionPanel(
            {{SFMLLayout::PANEL_GAP, decisionY}, {m_windowSize.x - (2 * SFMLLayout::PANEL_GAP), decisionHeight}});
    }
    m_window.display();
}

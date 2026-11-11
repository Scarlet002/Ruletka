#include "SFMLInitializer.h"
#include "GameConfig.h"
#include "SFMLColors.hpp"
#include "SFMLLayout.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <cstddef>
#include <ranges>
#include <stdexcept>
#include <utility>

SFMLInitializer::SFMLInitializer(sf::RenderWindow& window) : m_window(window)
{
    if (!m_font.openFromFile("assets/fonts/Jersey20-Regular.ttf"))
    {
        throw std::runtime_error("Font not found!");
    }

    constexpr auto BUFFER_STRING_RESERVE = GameConfig::LOG_LINE_RESERVE * SFMLLayout::BUFFER_STRING_RESERVE_MULTIPLIER;
    m_bufferString.reserve(BUFFER_STRING_RESERVE);
    m_filenameText.setFont(m_font);
    m_filenameLabel.setFont(m_font);
    m_bufferText.setFont(m_font);
    m_window.setVerticalSyncEnabled(true);
}

auto SFMLInitializer::CreateRestartButtons() -> void
{
    constexpr std::array<sf::Color, GameConfig::RESTART_BUTTONS_COUNT> COLORS = {
        {SFMLColors::BUTTON_EXIT_COLOR, SFMLColors::BUTTON_RESTART_COLOR},
    };
    constexpr std::array<float, GameConfig::RESTART_BUTTONS_COUNT> POSITIONS = {
        {SFMLLayout::RESTART_BUTTON_X_1, SFMLLayout::RESTART_BUTTON_X_2},
    };

    m_restartButtons.clear();
    m_restartButtons.reserve(GameConfig::RESTART_BUTTONS_COUNT);

    for (const auto [index, entry] : std::views::enumerate(GameConfig::GAMEOVER_BUTTONS))
    {
        auto& button = m_restartButtons.emplace_back(
            m_font, entry.first, std::to_underlying(entry.second),
            sf::Vector2f{POSITIONS[static_cast<size_t>(index)], SFMLLayout::RESTART_BUTTON_Y},
            sf::Vector2f{SFMLLayout::RESTART_BUTTON_WIDTH, SFMLLayout::RESTART_BUTTON_HEIGHT});

        button.m_rect.setFillColor(COLORS[static_cast<size_t>(index)]);
        button.m_rect.setOutlineColor(SFMLColors::BUTTON_OUTLINE_COLOR);
        button.m_rect.setOutlineThickness(SFMLLayout::RESTART_BUTTON_BORDER_THICKNESS);

        button.m_label.setFillColor(SFMLColors::BUTTON_LABEL_COLOR);
        button.m_label.setCharacterSize(SFMLLayout::RESTART_BUTTON_CHARACTER_SIZE);
        const auto bounds = button.m_label.getLocalBounds();
        button.m_label.setOrigin(
            {bounds.size.x / SFMLLayout::CENTER_DIVISOR, bounds.size.y / SFMLLayout::CENTER_DIVISOR});
        button.m_label.setPosition(
            {POSITIONS[static_cast<size_t>(index)] + (SFMLLayout::RESTART_BUTTON_WIDTH / SFMLLayout::CENTER_DIVISOR),
             SFMLLayout::RESTART_BUTTON_Y + (SFMLLayout::RESTART_BUTTON_HEIGHT / SFMLLayout::CENTER_DIVISOR)});
    }
}

auto SFMLInitializer::CreateFilenameInput() -> void
{
    constexpr auto BOX_HALF_WIDTH = SFMLLayout::INIT_FILENAME_BOX_WIDTH / SFMLLayout::CENTER_DIVISOR;
    constexpr auto HALF_WINDOW_WIDTH = static_cast<float>(GameConfig::WINDOW_WIDTH) / SFMLLayout::CENTER_DIVISOR;
    constexpr auto HALF_WINDOW_HEIGHT = static_cast<float>(GameConfig::WINDOW_HEIGHT) / SFMLLayout::CENTER_DIVISOR;

    m_filenameBox.setSize({SFMLLayout::INIT_FILENAME_BOX_WIDTH, SFMLLayout::INIT_FILENAME_BOX_HEIGHT});
    m_filenameBox.setPosition({HALF_WINDOW_WIDTH - BOX_HALF_WIDTH, HALF_WINDOW_HEIGHT});
    m_filenameBox.setFillColor(SFMLColors::FILENAME_BOX_COLOR);
    m_filenameBox.setOutlineColor(SFMLColors::FILENAME_BOX_BORDER_COLOR);
    m_filenameBox.setOutlineThickness(SFMLLayout::INIT_FILENAME_BORDER_THICKNESS);

    m_bufferString = GameConfig::DEFAULT_FILENAME;
    m_filenameText.setString(m_bufferString);
    m_filenameText.setCharacterSize(SFMLLayout::INIT_FILENAME_TEXT_SIZE);
    m_filenameText.setFillColor(SFMLColors::FILENAME_TEXT_COLOR);
    m_filenameText.setPosition({HALF_WINDOW_WIDTH - BOX_HALF_WIDTH + SFMLLayout::INIT_FILENAME_TEXT_OFFSET_X,
                                HALF_WINDOW_HEIGHT + SFMLLayout::INIT_FILENAME_TEXT_OFFSET_Y});

    m_filenameLabel.setCharacterSize(SFMLLayout::INIT_FILENAME_LABEL_SIZE);
    m_filenameLabel.setFillColor(SFMLColors::FILENAME_TEXT_COLOR);
    m_filenameLabel.setPosition(
        {HALF_WINDOW_WIDTH - BOX_HALF_WIDTH, HALF_WINDOW_HEIGHT - SFMLLayout::INIT_FILENAME_LABEL_OFFSET_Y});
}

auto SFMLInitializer::Initialize() -> void
{
    CreateButtons(m_mainButtons, GameConfig::MAIN_CHOICES);
    CreateButtons(m_itemButtons, GameConfig::ITEM_TYPES);
    CreateButtons(m_difficultyButtons, GameConfig::DIFFICULTY_TYPES);
    CreateButtons(m_serializationButtons, GameConfig::SERIALIZATION_TYPES);
    CreateRestartButtons();
    CreateFilenameInput();
}

auto SFMLInitializer::ResetBufferRectangle() noexcept -> void
{
    m_bufferRectangle.setSize({0.0F, 0.0F});
    m_bufferRectangle.setFillColor(SFMLColors::BUTTON_OUTLINE_COLOR);
    m_bufferRectangle.setOutlineColor(SFMLColors::BUTTON_OUTLINE_COLOR);
    m_bufferRectangle.setOutlineThickness(0.0F);
    m_bufferRectangle.setOrigin({0.0F, 0.0F});
    m_bufferRectangle.setPosition({0.0F, 0.0F});
    m_bufferRectangle.setRotation(sf::Angle::Zero);
    m_bufferRectangle.setScale({1.0F, 1.0F});
    m_bufferRectangle.setTexture(nullptr);
    m_bufferRectangle.setTextureRect({});
}

auto SFMLInitializer::ResetBufferText() noexcept -> void
{
    m_bufferText.setString("");
    m_bufferText.setCharacterSize(SFMLLayout::DEFAULT_BUFFER_TEXT_SIZE);
    m_bufferText.setFillColor(SFMLColors::BUTTON_OUTLINE_COLOR);
    m_bufferText.setOutlineColor(SFMLColors::BUTTON_OUTLINE_COLOR);
    m_bufferText.setOutlineThickness(0.0F);
    m_bufferText.setStyle(sf::Text::Regular);
    m_bufferText.setOrigin({0.0F, 0.0F});
    m_bufferText.setPosition({0.0F, 0.0F});
    m_bufferText.setRotation(sf::Angle::Zero);
    m_bufferText.setScale({1.0F, 1.0F});
    m_bufferText.setLetterSpacing(1.0F);
    m_bufferText.setLineSpacing(1.0F);
}

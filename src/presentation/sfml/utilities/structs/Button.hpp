#pragma once

#include "SFMLLayout.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <string>
#include <string_view>

struct Button final
{
    sf::RectangleShape m_rect; // NOLINT(misc-non-private-member-variables-in-classes):
    sf::Text m_label;          // NOLINT(misc-non-private-member-variables-in-classes):
    uint8_t m_actionId = 0U;   // NOLINT(misc-non-private-member-variables-in-classes):

    //explicit Button(const sf::Font& font) : m_label(font, "", SFMLLayout::BUTTON_DEFAULT_FONT_SIZE)
    //{
    //}

    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    Button(const sf::Font& font, std::string_view text, uint8_t actionId, sf::Vector2f position, sf::Vector2f size)
        : m_rect(size), m_label(font, std::string(text), SFMLLayout::BUTTON_DEFAULT_LABEL_SIZE), m_actionId(actionId)
    {
        m_rect.setPosition(position);
        m_label.setPosition(position);
    }
};

#pragma once

#include <SFML/Graphics/Color.hpp>

namespace SFMLColors
{
// Window and panel backgrounds
inline constexpr auto PANEL_BACKGROUND_COLOR = sf::Color(30, 30, 30, 220);
inline constexpr auto OVERLAY_BACKGROUND_COLOR = sf::Color(0, 0, 0, 200);
inline constexpr auto WINDOW_BACKGROUND_COLOR = sf::Color(20, 20, 30);
inline constexpr auto INVALID_WINDOW_COLOR = sf::Color::Black;

// Filename input box
inline constexpr auto FILENAME_BOX_COLOR = sf::Color(50, 50, 70);
inline constexpr auto FILENAME_BOX_BORDER_COLOR = sf::Color::Cyan;
inline constexpr auto FILENAME_TEXT_COLOR = sf::Color::White;

// Segmented bars
inline constexpr auto BAR_PRIMARY_COLOR = sf::Color(100, 200, 255);
inline constexpr auto BAR_SECONDARY_COLOR = sf::Color(255, 200, 50);
inline constexpr auto BAR_CRITICAL_COLOR = sf::Color(255, 100, 100);

// Buttons
inline constexpr auto BUTTON_FILL_COLOR = sf::Color(70, 70, 70);
inline constexpr auto BUTTON_EXIT_COLOR = sf::Color(120, 70, 70);
inline constexpr auto BUTTON_RESTART_COLOR = sf::Color(70, 120, 70);
inline constexpr auto BUTTON_OUTLINE_COLOR = sf::Color::White;
inline constexpr auto BUTTON_LABEL_COLOR = sf::Color::White;

// Player identity colors
inline constexpr auto HUMAN_COLOR = sf::Color::Green;
inline constexpr auto COMPUTER_COLOR = sf::Color::Red;

// Highlighted label
inline constexpr auto TEXT_HIGHLIGHT_COLOR = sf::Color::Yellow;
} // namespace SFMLColors

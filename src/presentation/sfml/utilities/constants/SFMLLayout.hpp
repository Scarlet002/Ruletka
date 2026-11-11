#pragma once

#include <SFML/Graphics/Color.hpp>

namespace SFMLLayout
{
// Window scaling
inline constexpr auto MIN_SCALE_FACTOR = 0.5F;
inline constexpr auto MAX_SCALE_FACTOR = 1.5F;

// Geometry
inline constexpr auto CENTER_DIVISOR = 2.0F;
inline constexpr auto PANEL_GAP = 2.0F;
inline constexpr auto BORDER_THICKNESS = 2.0F;
inline constexpr auto SEGMENT_GAP = 1.0F;

// Font sizes
inline constexpr auto FONT_SIZE_DISPLAY = 52.0F;
inline constexpr auto FONT_SIZE_TITLE = 40.0F;
inline constexpr auto FONT_SIZE_SUBTITLE = 30.0F;
inline constexpr auto FONT_SIZE_BODY = 28.0F;
inline constexpr auto FONT_SIZE_NORMAL = 26.0F;
inline constexpr auto FONT_SIZE_LABEL = 24.0F;
inline constexpr auto FONT_SIZE_SMALL = 22.0F;
inline constexpr auto FONT_SIZE_TINY = 20.0F;

// Text metrics
inline constexpr auto CHAR_WIDTH_RATIO = 0.6F;
inline constexpr auto WIDTH_LIMIT_RATIO = 0.8F;
inline constexpr auto TEXT_HEIGHT_RATIO = 1.1F;
inline constexpr auto LINE_HEIGHT_RATIO = 1.5F;
inline constexpr auto TITLE_OFFSET_RATIO = 0.9F;
inline constexpr auto BUTTON_LABEL_VERTICAL_DIVISOR = 2.5F;

// Max characters hints for ScaleFontWithWidthLimit
inline constexpr auto MAX_CHARS_DISPLAY = 10.0F;
inline constexpr auto MAX_CHARS_TITLE = 12.0F;
inline constexpr auto MAX_CHARS_BODY = 15.0F;
inline constexpr auto MAX_CHARS_FILENAME = 20.0F;
inline constexpr auto MAX_CHARS_LABEL = 25.0F;
inline constexpr auto MAX_CHARS_LOG_LINE = 26.0F;
inline constexpr auto MAX_CHARS_STATS = 30.0F;
inline constexpr auto MAX_CHARS_HINT = 30.0F;

// Stats panel
inline constexpr auto STATS_MARGIN_X = 0.04F;
inline constexpr auto STATS_MARGIN_Y = 0.04F;
inline constexpr auto STATS_BAR_HEIGHT_RATIO = 0.04F;
inline constexpr auto STATS_ROW_COUNT = 8.0F;
inline constexpr auto STATS_ROW_GAP_RATIO = 0.5F;

// Magazine panel
inline constexpr auto MAGAZINE_MARGIN_X = 0.02F;
inline constexpr auto MAGAZINE_MARGIN_Y = 0.06F;
inline constexpr auto MAGAZINE_BAR_HEIGHT_RATIO = 0.18F;
inline constexpr auto MAGAZINE_ROW_OFFSET_RATIO = 0.15F;

// Difficulty info panel
inline constexpr auto INFO_MARGIN_X = 0.03F;
inline constexpr auto INFO_MARGIN_Y = 0.04F;

// Gamelog panel
inline constexpr auto LOG_MARGIN_X = 0.06F;
inline constexpr auto LOG_MARGIN_Y = 0.04F;
inline constexpr auto LOG_TITLE_OFFSET_RATIO = 1.5F;

// Gameover screen
inline constexpr auto GAME_OVER_TITLE_Y_RATIO = 0.2F;
inline constexpr auto GAME_OVER_WINNER_Y_RATIO = 0.4F;
inline constexpr auto GAME_OVER_STATS_Y_RATIO = 0.6F;
inline constexpr auto GAME_OVER_BUTTONS_Y_RATIO = 0.72F;

// Gameover buttons
inline constexpr auto BUTTON_WIDTH_RATIO = 0.3F;
inline constexpr auto BUTTON_MAX_WIDTH = 200.0F;
inline constexpr auto BUTTON_SPACING_RATIO = 0.15F;
inline constexpr auto BUTTON_MAX_TOTAL_RATIO = 0.8F;
inline constexpr auto BUTTON_MIN_WIDTH = 100.0F;
inline constexpr auto BUTTON_HEIGHT_RATIO = 0.1F;
inline constexpr auto BUTTON_MIN_HEIGHT = 40.0F;
inline constexpr auto BUTTON_PADDING = 20.0F;
inline constexpr auto BUTTON_MIN_FONT_SIZE = 12U;
inline constexpr auto BUTTON_MAX_FONT_SIZE = 40U;
inline constexpr auto BUTTON_MAX_LABEL_LENGTH = 16UZ;

// Menu button bar
inline constexpr auto MENU_BUTTON_Y = 720.0F;
inline constexpr auto MENU_BUTTON_WIDTH = 130.0F;
inline constexpr auto MENU_BUTTON_HEIGHT = 40.0F;
inline constexpr auto MENU_BUTTON_SPACING = 8.0F;
inline constexpr auto MENU_BUTTON_BORDER_THICKNESS = 1.0F;

// Restart buttons
inline constexpr auto RESTART_BUTTON_Y = 250.0F;
inline constexpr auto RESTART_BUTTON_WIDTH = 200.0F;
inline constexpr auto RESTART_BUTTON_HEIGHT = 60.0F;
inline constexpr auto RESTART_BUTTON_BORDER_THICKNESS = 2.0F;
inline constexpr auto RESTART_BUTTON_CHARACTER_SIZE = 20U;
inline constexpr auto RESTART_BUTTON_X_1 = 350.0F;
inline constexpr auto RESTART_BUTTON_X_2 = 50.0F;

// Filename input
inline constexpr auto INIT_FILENAME_BOX_WIDTH = 400.0F;
inline constexpr auto INIT_FILENAME_BOX_HEIGHT = 40.0F;
inline constexpr auto INIT_FILENAME_TEXT_SIZE = 24U;
inline constexpr auto INIT_FILENAME_LABEL_SIZE = 20U;
inline constexpr auto INIT_FILENAME_TEXT_OFFSET_X = 10.0F;
inline constexpr auto INIT_FILENAME_TEXT_OFFSET_Y = 5.0F;
inline constexpr auto INIT_FILENAME_LABEL_OFFSET_Y = 40.0F;
inline constexpr auto INIT_FILENAME_BORDER_THICKNESS = 2.0F;

// Buffer defaults
inline constexpr auto BUFFER_STRING_RESERVE_MULTIPLIER = 3U;
inline constexpr auto DEFAULT_BUFFER_TEXT_SIZE = 30U;

// Button defaults
inline constexpr auto BUTTON_DEFAULT_FONT_SIZE = 16U;
inline constexpr auto BUTTON_DEFAULT_LABEL_SIZE = 30U;

// Filename input
inline constexpr auto FILENAME_BOX_WIDTH_RATIO = 0.3F;
inline constexpr auto FILENAME_BOX_HEIGHT_RATIO = 0.06F;
inline constexpr auto FILENAME_LABEL_OFFSET_RATIO = 0.8F;
inline constexpr auto FILENAME_TEXT_LENGTH_LIMIT = 15.0F;
inline constexpr auto FILENAME_TEXT_PADDING = 10.0F;
inline constexpr auto FILENAME_TEXT_VERTICAL_DIVISOR = 1.2F;
inline constexpr auto FILENAME_HINT_OFFSET = 20.0F;

// Main render layout
inline constexpr auto TOP_PANEL_HEIGHT_RATIO = 0.15F;
inline constexpr auto DECISION_PANEL_HEIGHT_RATIO = 0.08F;
inline constexpr auto DECISION_PANEL_MIN_HEIGHT = 40.0F;
inline constexpr auto MAIN_PANEL_COLUMNS = 3.0F;

// Defaults
inline constexpr auto DEFAULT_MAX_CHARACTERS = 25.0F;
inline constexpr auto DEFAULT_EMPTY_BAR_COLOR = sf::Color(50U, 50U, 50U);
} // namespace SFMLLayout

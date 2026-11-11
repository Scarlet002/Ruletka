#pragma once

#include <string_view>

namespace SFMLText
{
// Window
inline constexpr auto WINDOW_TITLE = std::string_view("Roulette");

// Panel labels
inline constexpr auto LABEL_HP = std::string_view("HP:");
inline constexpr auto LABEL_TOTAL = std::string_view("TOTAL:");
inline constexpr auto LABEL_BLANK = std::string_view("BLANK:");
inline constexpr auto LABEL_LIVE = std::string_view("LIVE:");

// Titles
inline constexpr auto TITLE_GAME_LOG = std::string_view("GAME LOG");
inline constexpr auto TITLE_GAME_OVER = std::string_view("GAME OVER");

// Format strings
inline constexpr auto FMT_WINNER = std::string_view("{} WINS!");
inline constexpr auto FMT_STATS = std::string_view("{}: {} HP | {}: {} HP");
inline constexpr auto FMT_DIFFICULTY = std::string_view("DIFFICULTY: {}");
inline constexpr auto FMT_SERIALIZATION = std::string_view("SERIALIZATION: {}");

// Prompts
inline constexpr auto PROMPT_SAVE = std::string_view("SAVE GAME - Enter file name:");
inline constexpr auto PROMPT_LOAD = std::string_view("LOAD GAME - Enter file name:");
inline constexpr auto HINT_FILENAME = std::string_view("Enter file name and press Enter (Esc - cancel)");
} // namespace SFMLText

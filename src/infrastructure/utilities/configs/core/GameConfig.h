#pragma once

#include "GameEnums.h"
#include <array>
#include <cstdint>
#include <string_view>
#include <utility>

namespace GameConfig
{
// Number of main choices
inline constexpr uint8_t MAIN_CHOICES_COUNT = 8U;

// Number of restart buttons
inline constexpr uint8_t RESTART_BUTTONS_COUNT = 2U;

// Number of difficulty types
inline constexpr uint8_t DIFFICULTY_TYPES_COUNT = 3U;

// Number of serialization types
inline constexpr uint8_t SERIALIZATION_TYPES_COUNT = 2U;

// Number of player types
inline constexpr uint8_t PLAYER_TYPES_COUNT = 2U;

// Number of item types
inline constexpr uint8_t ITEM_TYPES_COUNT = 6U;

// Number of ui types
inline constexpr uint8_t UI_TYPES_COUNT = 2U;

// Number of window types
inline constexpr uint8_t WINDOW_TYPES_COUNT = 7U;

// Number of magazine chamber types
inline constexpr uint8_t MAGAZINE_CHAMBER_TYPES_COUNT = 3U;

// FrameLimit
inline constexpr uint8_t SLEEP_FOR_MILLISECONDS = 33U;

// Window width setting
inline constexpr uint16_t WINDOW_WIDTH = 1280U;

// Window height setting
inline constexpr uint16_t WINDOW_HEIGHT = 720U;

// Default difficulty setting
inline constexpr auto DEFAULT_DIFFICULTY = GameEnums::Difficulty::NORMAL;

// Max HP limit
inline constexpr uint8_t MAX_PLAYER_HP = 5U;

// Min HP limit
inline constexpr uint8_t MIN_PLAYER_HP = 0U;

// Max logs limit
inline constexpr uint8_t MAX_LOGS = 12U;

// Min logs limit
inline constexpr uint8_t MIN_LOGS = 0U;

// Number of players
inline constexpr uint8_t MAX_PLAYERS = 1U; // <- ma być 2U

// First item type index for RNG
inline constexpr uint8_t MIN_ITEM_TYPE_RNG = std::to_underlying(GameEnums::ItemType::HANDCUFFS);

// Last item type index for RNG
inline constexpr uint8_t MAX_ITEM_TYPE_RNG = std::to_underlying(GameEnums::ItemType::INVERTER);

// Max items gained in next round
inline constexpr uint8_t MAX_ITEMS_GAINED = 1U;

// Min ammount of items
inline constexpr uint8_t MIN_ITEMS = 0U;

// Max ammount of items
inline constexpr uint8_t MAX_ITEMS = 5U;

// Default damage value
inline constexpr uint8_t DEFAULT_DAMAGE = 1U;

// Saw damage value
inline constexpr uint8_t SAW_DAMAGE = DEFAULT_DAMAGE * 2U;

// Min bullets in magazine
inline constexpr uint8_t MIN_BULLETS = 0U;

// Max bullets in magazine
inline constexpr uint8_t MAX_BULLETS = 8U;

// Min number of bullets that can be generated in RNG
inline constexpr uint8_t MIN_BULLETS_RNG = 2U;

// Max number of bullets that can be generated in RNG
inline constexpr uint8_t MAX_BULLETS_RNG = 8U;

// Easy AI min decision value
inline constexpr uint8_t MIN_EASY_AI = std::to_underlying(GameEnums::MainChoice::HEAL);

// Easy AI max decision value
inline constexpr uint8_t MAX_EASY_AI = std::to_underlying(GameEnums::MainChoice::SHOOT);

// Min probability value
inline constexpr double MIN_PROBABILITY = 0.0;

// Max probability value
inline constexpr double MAX_PROBABILITY = 1.0;

// LogLine reserve size
inline constexpr uint8_t LOG_LINE_RESERVE = 128U;

// Limit for filename length
inline constexpr uint8_t MAX_FILENAME_LENGTH = 32U;

// Starting autosave count
inline constexpr uint8_t STARTING_AUTOSAVE_COUNT = 0U;

inline constexpr auto ITEM_TYPES = std::to_array<std::pair<std::string_view, GameEnums::ItemType>>({
    {"HANDCUFFS", GameEnums::ItemType::HANDCUFFS},
    {"BEER", GameEnums::ItemType::BEER},
    {"MAGNIFIER", GameEnums::ItemType::MAGNIFIER},
    {"SAW", GameEnums::ItemType::SAW},
    {"CELLPHONE", GameEnums::ItemType::CELLPHONE},
    {"INVERTER", GameEnums::ItemType::INVERTER},
});

inline constexpr auto BULLET_TYPES = std::to_array<std::pair<std::string_view, GameEnums::MagazineChamber>>({
    {"EMPTY", GameEnums::MagazineChamber::EMPTY},
    {"BLANK", GameEnums::MagazineChamber::BLANK},
    {"LIVE", GameEnums::MagazineChamber::LIVE},
});

inline constexpr auto DIFFICULTY_TYPES = std::to_array<std::pair<std::string_view, GameEnums::Difficulty>>({
    {"EASY", GameEnums::Difficulty::EASY},
    {"NORMAL", GameEnums::Difficulty::NORMAL},
    {"HARD", GameEnums::Difficulty::HARD},
});

inline constexpr auto SERIALIZATION_TYPES = std::to_array<std::pair<std::string_view, GameEnums::SerializationFormat>>({
    {"TXT", GameEnums::SerializationFormat::TXT},
    {"JSON", GameEnums::SerializationFormat::JSON},
});

inline constexpr auto UI_TYPES = std::to_array<std::pair<std::string_view, GameEnums::UIType>>({
    {"CONSOLE", GameEnums::UIType::CONSOLE},
    {"SFML", GameEnums::UIType::SFML},
});

inline constexpr auto PLAYER_TYPES = std::to_array<std::pair<std::string_view, GameEnums::PlayerType>>({
    {"COMPUTER", GameEnums::PlayerType::COMPUTER},
    {"HUMAN", GameEnums::PlayerType::HUMAN},
});

inline constexpr auto MAIN_CHOICES = std::to_array<std::pair<std::string_view, GameEnums::MainChoice>>({
    {"HEAL", GameEnums::MainChoice::HEAL},
    {"SHOOT", GameEnums::MainChoice::SHOOT},
    {"USE ITEM", GameEnums::MainChoice::USE_ITEM},
    {"SAVE", GameEnums::MainChoice::SAVE},
    {"LOAD", GameEnums::MainChoice::LOAD},
    {"DIFFICULTY", GameEnums::MainChoice::CHANGE_DIFFICULTY},
    {"SERIALIZATION", GameEnums::MainChoice::CHANGE_SERIALIZATION},
    {"EXIT", GameEnums::MainChoice::EXIT},
});

inline constexpr auto WINDOW_TYPES = std::to_array<std::pair<std::string_view, GameEnums::Window>>({
    {"MAIN_MENU", GameEnums::Window::MAIN_MENU},
    {"DIFFICULTY_MENU", GameEnums::Window::DIFFICULTY_MENU},
    {"INVENTORY_MENU", GameEnums::Window::INVENTORY_MENU},
    {"SAVE_MENU", GameEnums::Window::SAVE_MENU},
    {"LOAD_MENU", GameEnums::Window::LOAD_MENU},
    {"SERIALIZATION_MENU", GameEnums::Window::SERIALIZATION_MENU},
    {"RESTART_MENU", GameEnums::Window::RESTART_MENU},
});

inline constexpr auto GAMEOVER_BUTTONS = std::to_array<std::pair<std::string_view, GameEnums::YesNo>>({
    {"EXIT", GameEnums::YesNo::NO},
    {"PLAY AGAIN", GameEnums::YesNo::YES},
});

inline constexpr std::string_view DEFAULT_FILENAME = "SAVE";
}; // namespace GameConfig

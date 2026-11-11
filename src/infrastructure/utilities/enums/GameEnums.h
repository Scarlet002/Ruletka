#pragma once

#include <cstdint>

namespace GameEnums
{
enum class MainChoice : uint8_t
{
    HEAL,
    SHOOT,
    USE_ITEM,
    EXIT,
    SAVE,
    LOAD,
    CHANGE_DIFFICULTY,
    CHANGE_SERIALIZATION,
    AUTOSAVE,
    RESTART,
};

enum class ItemType : uint8_t
{
    NOTHING,
    HANDCUFFS,
    BEER,
    MAGNIFIER,
    SAW,
    CELLPHONE,
    INVERTER,
};

enum class Difficulty : uint8_t
{
    EASY,
    NORMAL,
    HARD,
};

enum class SerializationFormat : uint8_t
{
    TXT,
    JSON,
};

enum class YesNo : uint8_t
{
    NO,
    YES,
};

enum class UIType : uint8_t
{
    CONSOLE,
    SFML,
};

enum class Window : uint8_t
{
    MAIN_MENU,
    DIFFICULTY_MENU,
    INVENTORY_MENU,
    SAVE_MENU,
    LOAD_MENU,
    SERIALIZATION_MENU,
    RESTART_MENU,
};

enum class PlayerType : uint8_t
{
    COMPUTER,
    HUMAN,
};

enum class MagazineChamber : uint8_t
{
    EMPTY,
    BLANK,
    LIVE,
};

enum class SpecialValues : int8_t
{
    NOTHING = -1,
};
} // namespace GameEnums

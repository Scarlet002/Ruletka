#pragma once
namespace GameEnums
{
    enum Difficulty { NORMAL, EASY, HARD };
    enum BulletType { EMPTY, FULL };
    enum Choice { NO_CHOICE = -1, HEAL, SHOOT, USEITEM, EXIT, SAVE, LOAD, DIFFICULTY, SERIALIZATION, AUTOSAVE, RESTART };
    enum PlayerType { COMPUTER, HUMAN };
    enum Item { NO_ITEMS, HANDCUFFS, BEER, MAGNIFIER, SAW, CELLPHONE, INVERTER };
    enum SaveLoadMethod { SAVE_TXT, LOAD_TXT, SAVE_JSON, LOAD_JSON };
    enum GameState { STATE_NOT_RUNNING, STATE_RUNNING };
    enum RestartChoice { RESTART_NO, RESTART_YES };
    enum ItemState { ITEM_NOT_USED, ITEM_USED };
    enum CurrentWindow { MAIN_MENU, DIFFICULTY_MENU, INVENTORY_MENU, SAVE_MENU, LOAD_MENU, SERIALIZATION_MENU, RESTART_MENU };
	enum UIType { CONSOLE = 1, SFML };
    enum BulletNumber { FIRST_BULLET };
    enum SerializationType { JSON, TXT };
}

#pragma once

namespace GameEnums
{
    enum Difficulty { NORMAL, EASY, HARD };
    enum Bullet { EMPTY, FULL };
    enum Choice { NO_CHOICE = -1, HEAL, SHOOT, USEITEM, EXIT, SAVE, LOAD, DIFFICULTY };
    enum Starter { STARTER_COMPUTER, STARTER_HUMAN };
    enum Target { TARGET_COMPUTER, TARGET_HUMAN };
	enum PlayerType { COMPUTER, HUMAN };
    enum Shooter { SHOOTER_COMPUTER, SHOOTER_HUMAN };
    enum Item { NO_ITEMS, HANDCUFFS, BEER, MAGNIFIER, SAW, CELLPHONE, INVERTER };
    enum SaveLoadMethod { SAVE_TXT, LOAD_TXT, SAVE_JSON, LOAD_JSON };
    enum GameStateEnum { STATE_NOT_RUNNING, STATE_RUNNING, STATE_HUMAN_WIN, STATE_COMPUTER_WIN };
	enum HandCuffsState { HANDCUFFS_NOT_USED, HANDCUFFS_USED };
    enum RestartChoice { RESTART_NO, RESTART_YES };
    enum IsSaving { NOT_SAVING, SAVING };
    enum WasMagazineShown { MAGAZINE_NOT_SHOWN, MAGAZINE_SHOWN };
    enum WasLogCleared { LOG_NOT_CLEARED, LOG_CLEARED };
    enum WasAutoSaved { NOT_AUTO_SAVED, AUTO_SAVED };
    enum Turn { TURN_COMPUTER, TURN_HUMAN };
    enum WaitingForRestartChoice { NOT_WAITING_FOR_RESTART_CHOICE, WAITING_FOR_RESTART_CHOICE };
    enum WaitingForPlayer { NOT_WAITING_FOR_PLAYER, WAITING_FOR_PLAYER };
    enum WasInventoryShownForComputer { INVENTORY_NOT_SHOWN, INVENTORY_SHOWN };
}

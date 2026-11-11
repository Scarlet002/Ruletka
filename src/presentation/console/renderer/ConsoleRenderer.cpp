#include "ConsoleRenderer.h"
#include "AIState.h"
#include "ApplicationState.h"
#include "DomainState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "HP.h"
#include "Inventory.h"
#include "ItemState.h"
#include "Logger.h"
#include "Magazine.h"
#include "Player.h"
#include "SerializationState.h"
#include <boost/static_string/static_string.hpp>
#include <iostream>
#include <sstream>
#include <string_view>

#ifdef _WIN32
#include <consoleapi2.h>
#include <consoleapi3.h>
#include <handleapi.h>
#include <minwindef.h>
#include <processenv.h>
#include <winbase.h>
#include <wincontypes.h>
#include <windows.h>
#include <winnt.h>
#else
#include <unistd.h>
#endif

ConsoleRenderer::ConsoleRenderer(const ApplicationState& app, const DomainState& domain, const Logger& logger)
    : m_app(app), m_domain(domain), m_logger(logger)
{
}

auto ConsoleRenderer::Clear() -> void
{
#ifdef _WIN32
    HANDLE hStdOut = nullptr;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count = 0U;
    DWORD cellCount = 0U;
    const COORD homeCoords = {.X = 0, .Y = 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
    {
        return;
    }

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi) == 0)
    {
        return;
    }

    cellCount = static_cast<DWORD>(csbi.dwSize.X * csbi.dwSize.Y);

    if (!FillConsoleOutputCharacter(hStdOut, static_cast<TCHAR>(' '), cellCount, homeCoords, &count))
    {
        return;
    }

    if (FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count) == 0)
    {
        return;
    }

    SetConsoleCursorPosition(hStdOut, homeCoords);
#else
    constexpr auto CLEAR_SEQ = std::string_view("\033[2J\033[H");
    constexpr auto CLEAR_SEQ_LENGTH = 7U;
    write(STDOUT_FILENO, CLEAR_SEQ.data(), CLEAR_SEQ_LENGTH);
#endif
}

auto ConsoleRenderer::DisplayLastTurnLog(std::ostringstream& oss) const -> void
{
    const auto logs = m_logger.GetLogs();
    auto tempHead = logs.m_head;
    for (auto index = 0UZ; index < GameConfig::MAX_LOGS; ++index)
    {
        if (logs.m_logs[tempHead].empty())
        {
            tempHead = (tempHead + 1) % GameConfig::MAX_LOGS;
            continue;
        }
        oss << logs.m_logs[tempHead] << '\n';
        tempHead = (tempHead + 1) % GameConfig::MAX_LOGS;
    }
}

auto ConsoleRenderer::GetAIDifficulty(GameEnums::Difficulty difficulty) noexcept -> std::string_view
{
    switch (difficulty)
    {
    case GameEnums::Difficulty::EASY:
        return "Easy";
    case GameEnums::Difficulty::NORMAL:
        return "Normal";
    case GameEnums::Difficulty::HARD:
        return "Hard";
    default:
        return "Unknown";
    }
}

auto ConsoleRenderer::GetSerializationType(GameEnums::SerializationFormat type) noexcept -> std::string_view
{
    return type == GameEnums::SerializationFormat::JSON ? "JSON" : "TXT";
}

auto ConsoleRenderer::DisplayStats(std::ostringstream& oss, std::string_view line) const -> void
{
    using namespace GameEnums;
    const auto& aiState = m_app.GetAIState();
    const auto& serialization = m_app.GetSerializationState();
    oss << line << '\n'
        << "Difficulty level: " << GetAIDifficulty(aiState.GetDifficulty()) << '\n'
        << "Serialization format: " << GetSerializationType(serialization.GetSerializationType()) << '\n'
        << "Statistics:\n\n";

    const auto& human = m_domain.GetHuman();
    const auto& humanHP = human.GetHP();
    const auto humanName = human.GetName();
    oss << humanName << " HP: " << static_cast<int>(humanHP.GetHP()) << '\n';

    const auto& humanInventory = m_domain.GetHumanInventory();
    oss << humanName << " Saws: " << static_cast<int>(humanInventory.GetItemCount(ItemType::SAW)) << '\n'
        << humanName << " Beers: " << static_cast<int>(humanInventory.GetItemCount(ItemType::BEER)) << '\n'
        << humanName << " Magnifiers: " << static_cast<int>(humanInventory.GetItemCount(ItemType::MAGNIFIER)) << '\n'
        << humanName << " Cellphones: " << static_cast<int>(humanInventory.GetItemCount(ItemType::CELLPHONE)) << '\n'
        << humanName << " Handcuffs: " << static_cast<int>(humanInventory.GetItemCount(ItemType::HANDCUFFS)) << '\n'
        << humanName << " Inverters: " << static_cast<int>(humanInventory.GetItemCount(ItemType::INVERTER)) << '\n'
        << '\n';

    const auto& computer = m_domain.GetComputer();
    const auto& computerHP = computer.GetHP();
    const auto computerName = computer.GetName();
    oss << computerName << " HP: " << static_cast<int>(computerHP.GetHP()) << '\n';

    const auto& computerInventory = m_domain.GetComputerInventory();
    oss << computerName << " Saws: " << static_cast<int>(computerInventory.GetItemCount(ItemType::SAW)) << '\n'
        << computerName << " Beers: " << static_cast<int>(computerInventory.GetItemCount(ItemType::BEER)) << '\n'
        << computerName << " Magnifiers: " << static_cast<int>(computerInventory.GetItemCount(ItemType::MAGNIFIER))
        << '\n'
        << computerName << " Cellphones: " << static_cast<int>(computerInventory.GetItemCount(ItemType::CELLPHONE))
        << '\n'
        << computerName << " Handcuffs: " << static_cast<int>(computerInventory.GetItemCount(ItemType::HANDCUFFS))
        << '\n'
        << computerName << " Inverters: " << static_cast<int>(computerInventory.GetItemCount(ItemType::INVERTER))
        << '\n'
        << '\n';

    const auto& item = m_domain.GetItemState();
    const auto& magazine = m_domain.GetMagazine();
    auto fullCount = static_cast<int>(magazine.GetBullets(MagazineChamber::LIVE));
    auto emptyCount = static_cast<int>(magazine.GetBullets(MagazineChamber::BLANK));
    if (item.GetStateOfInverter() == YesNo::YES)
    {
        switch (magazine.CheckMagazineChamber(magazine.GetMagazine().m_head))
        {
        case GameEnums::MagazineChamber::BLANK:
            ++fullCount;
            --emptyCount;
            break;
        case GameEnums::MagazineChamber::LIVE:
            --fullCount;
            ++emptyCount;
            break;
        default:
        case GameEnums::MagazineChamber::EMPTY:
            break;
        }
    }

    oss << "Live bullets: " << fullCount << '\n'
        << "Blank bullets: " << emptyCount << '\n'
        << "Bullet count: " << fullCount + emptyCount << '\n'
        << line << '\n';
}

auto ConsoleRenderer::MainMenu(std::ostringstream& oss, std::string_view line) -> void
{
    oss << line << '\n'
        << "Choose what you want to do:\n"
        << "0 - Try to regain 1 HP\n"
        << "1 - Shoot the computer\n"
        << "2 - Use an item\n"
        << "3 - End game\n"
        << "4 - Save game\n"
        << "5 - Load game\n"
        << "6 - Choose difficulty level\n"
        << "7 - Choose serialization format\n"
        << line << '\n';
}

auto ConsoleRenderer::DifficultyMenu(std::ostringstream& oss, std::string_view line) -> void
{
    oss << line << '\n'
        << "Choose difficulty level:\n"
        << "0 - Easy\n"
        << "1 - Normal\n"
        << "2 - Hard\n"
        << line << '\n';
}

auto ConsoleRenderer::RestartMenu(std::ostringstream& oss, std::string_view line) -> void
{
    oss << line << '\n'
        << "Choose whether you want to play again:\n"
        << "0 - No\n"
        << "1 - Yes\n"
        << line << '\n';
}

auto ConsoleRenderer::SerializationMenu(std::ostringstream& oss, std::string_view line) -> void
{
    oss << line << '\n'
        << "Choose serialization format:\n"
        << "0 - TXT\n"
        << "1 - JSON\n"
        << line << '\n';
}

auto ConsoleRenderer::InventoryMenu(std::ostringstream& oss, std::string_view line) -> void
{
    oss << line << '\n'
        << "Choose the item you want to use:\n"
        << "0 - Do not use any item\n"
        << "1 - Handcuffs\n"
        << "2 - Beer\n"
        << "3 - Magnifier\n"
        << "4 - Saw\n"
        << "5 - Cellphone\n"
        << "6 - Inverter\n"
        << line << '\n';
}

auto ConsoleRenderer::Render() -> void
{
    using namespace GameEnums;
    const auto line = boost::static_string<100>(100, '-');
    std::ostringstream oss;
    DisplayStats(oss, line);
    DisplayLastTurnLog(oss);

    switch (m_app.GetGameLoopState().GetCurrentMenu())
    {
    case Window::DIFFICULTY_MENU:
        DifficultyMenu(oss, line);
        break;
    case Window::INVENTORY_MENU:
        InventoryMenu(oss, line);
        break;
    case Window::SAVE_MENU:
    case Window::LOAD_MENU:
        break;
    case Window::SERIALIZATION_MENU:
        SerializationMenu(oss, line);
        break;
    case Window::RESTART_MENU:
        RestartMenu(oss, line);
        break;
    default:
    case Window::MAIN_MENU:
        MainMenu(oss, line);
        break;
    }

    Clear();
    std::cout << oss.str() << std::flush;
}

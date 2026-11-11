#include "SFMLProvider.h"
#include "AIState.h"
#include "ApplicationState.h"
#include "DecisionState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include "SFMLInitializer.h"
#include "SFMLText.hpp"
#include "SerializationState.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <cassert>
#include <format>
#include <iterator>
#include <optional>
#include <string>

SFMLProvider::SFMLProvider(ApplicationState& app, SFMLInitializer& initializer, sf::RenderWindow& window) noexcept
    : m_app(app), m_initializer(initializer), m_window(window)
{
}

auto SFMLProvider::InputFilenameChoice(const sf::Event& event) -> void
{
    using namespace GameEnums;
    auto& decision = m_app.GetDecisionState();
    auto& gameLoop = m_app.GetGameLoopState();
    if (const auto* keyEvent = event.getIf<sf::Event::KeyReleased>())
    {
        if (keyEvent->code == sf::Keyboard::Key::Escape)
        {
            decision.SetMainChoice(std::nullopt);
            gameLoop.SetCurrentMenu(Window::MAIN_MENU);
            gameLoop.SetRenderFlag(YesNo::YES);
            return;
        }

        if (keyEvent->code == sf::Keyboard::Key::Enter)
        {
            decision.SetMainChoice(gameLoop.GetCurrentMenu() == Window::SAVE_MENU ? MainChoice::SAVE
                                                                                  : MainChoice::LOAD);
            gameLoop.SetRenderFlag(YesNo::YES);
            return;
        }

        if (keyEvent->code == sf::Keyboard::Key::Backspace)
        {
            const auto filename = decision.GetFilename();
            if (!filename.empty())
            {
                auto& filenameText = m_initializer.GetFilenameText();
                auto& buffer = m_initializer.GetBufferString();
                buffer.clear();
                std::format_to(std::back_inserter(buffer), "{}", filename.substr(0, filename.size() - 1));
                filenameText.setString(buffer);
                decision.SetFilename(buffer);
                gameLoop.SetRenderFlag(YesNo::YES);
            }
        }
    }
    else if (const auto* textEvent = event.getIf<sf::Event::TextEntered>())
    {
        constexpr auto ASCII_PRINTABLE_LOWER_BAND = 32U;
        constexpr auto ASCII_PRINTABLE_UPPER_BAND = 128U;
        if (textEvent->unicode >= ASCII_PRINTABLE_LOWER_BAND && textEvent->unicode < ASCII_PRINTABLE_UPPER_BAND &&
            decision.GetFilename().size() <= GameConfig::MAX_FILENAME_LENGTH)
        {
            auto& buffer = m_initializer.GetBufferString();
            buffer.clear();
            std::format_to(std::back_inserter(buffer), "{}{}", decision.GetFilename(),
                           static_cast<char>(textEvent->unicode));
            decision.SetFilename(buffer);
            gameLoop.SetRenderFlag(YesNo::YES);
        }
        auto& filenameText = m_initializer.GetFilenameText();
        auto& buffer = m_initializer.GetBufferString();
        buffer = decision.GetFilename();
        filenameText.setString(buffer);
    }
}

auto SFMLProvider::GetInput() -> void
{
    using namespace GameEnums;
    while (auto eventOpt = m_window.pollEvent())
    {
        const auto& event = *eventOpt;
        if (event.is<sf::Event::Closed>())
        {
            m_window.close();
            return;
        }

        auto& gameLoop = m_app.GetGameLoopState();
        const auto* key = event.getIf<sf::Event::KeyReleased>();
        if ((key != nullptr) && key->code == sf::Keyboard::Key::F11)
        {
            gameLoop.SetRenderFlag(YesNo::YES);
            m_isFullscreen = !m_isFullscreen;
            auto& bufferString = m_initializer.GetBufferString();
            bufferString = SFMLText::WINDOW_TITLE;
            if (m_isFullscreen)
            {
                m_savedWindowSize = m_window.getSize();
                m_window.create(sf::VideoMode::getDesktopMode(), bufferString, sf::State::Fullscreen);
            }
            else
            {
                m_window.create(sf::VideoMode(m_savedWindowSize), bufferString, sf::Style::Default);
                m_window.setMinimumSize(sf::Vector2u{GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT});
            }
            continue;
        }

        if (const auto* resized = event.getIf<sf::Event::Resized>())
        {
            gameLoop.SetRenderFlag(YesNo::YES);
            const auto minSize = sf::Vector2u(800U, 600U);
            const auto newSize = sf::Vector2f(static_cast<float>(resized->size.x), static_cast<float>(resized->size.y));
            if (newSize.x < static_cast<float>(minSize.x) || newSize.y < static_cast<float>(minSize.y))
            {
                m_window.setSize(minSize);
            }
            else
            {
                const sf::FloatRect visibleArea(sf::Vector2f(0.0F, 0.0F), newSize);
                m_window.setView(sf::View(visibleArea));
            }
            continue;
        }

        auto& decision = m_app.GetDecisionState();
        switch (m_app.GetGameLoopState().GetCurrentMenu())
        {
        case Window::DIFFICULTY_MENU:
            InputChoice(
                event, m_initializer.GetDifficultyButtons(),
                [&](auto choice) -> void { decision.SetDifficultyChoice(static_cast<Difficulty>(choice)); },
                [&] -> void { decision.SetDifficultyChoice(m_app.GetAIState().GetDifficulty()); });

            break;
        case Window::INVENTORY_MENU:
            InputChoice(
                event, m_initializer.GetItemButtons(),
                [&](auto choice) -> void { decision.SetItemChoice(static_cast<ItemType>(choice)); },
                [&] -> void { decision.SetItemChoice(GameEnums::ItemType::NOTHING); });
            break;
        case Window::SAVE_MENU:
        case Window::LOAD_MENU:
            InputFilenameChoice(event);
            break;
        case Window::SERIALIZATION_MENU:
            InputChoice(
                event, m_initializer.GetSerializationButtons(),
                [&](auto choice) -> void { decision.SetSerializationChoice(static_cast<SerializationFormat>(choice)); },
                [&] -> void { decision.SetSerializationChoice(m_app.GetSerializationState().GetSerializationType()); });
            break;
        case Window::RESTART_MENU:
            InputChoice(
                event, m_initializer.GetRestartButtons(),
                [&](auto choice) -> void { decision.SetYesNoChoice(static_cast<YesNo>(choice)); }, [] -> void {});
            break;
        case Window::MAIN_MENU:
        default:
            InputChoice(
                event, m_initializer.GetMainButtons(),
                [&](auto choice) -> void { decision.SetMainChoice(static_cast<MainChoice>(choice)); }, [] -> void {});
            break;
        }
    }
}

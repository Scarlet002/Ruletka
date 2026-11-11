#pragma once

#include "ApplicationState.h"
#include "Button.hpp"
#include "GameConfig.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "Provider.h"
#include "SFMLInitializer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <vector>

class SFMLProvider : public Provider
{
private:
    ApplicationState& m_app;
    SFMLInitializer& m_initializer;
    sf::RenderWindow& m_window;
    sf::Vector2u m_savedWindowSize{GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT};
    bool m_isFullscreen = false;

    template <typename EscapeSetter, typename SelectSetter>
    auto InputChoice(const sf::Event& event, const std::vector<Button>& buttons, SelectSetter select,
                     EscapeSetter escape) -> void
    {
        using namespace GameEnums;
        auto& gameLoop = m_app.GetGameLoopState();
        if (const auto* keyEvent = event.getIf<sf::Event::KeyReleased>())
        {
            if (keyEvent->code == sf::Keyboard::Key::Escape)
            {
                escape();
                gameLoop.SetRenderFlag(YesNo::YES);
                return;
            }
        }
        else if (const auto* mouseEvent = event.getIf<sf::Event::MouseButtonReleased>())
        {
            if (mouseEvent->button != sf::Mouse::Button::Left)
            {
                return;
            }
            for (const auto& button : buttons)
            {
                if (button.m_rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouseEvent->position)))
                {
                    select(button.m_actionId);
                    gameLoop.SetRenderFlag(YesNo::YES);
                    return;
                }
            }
        }
    }

    auto InputFilenameChoice(const sf::Event& event) -> void;

public:
    SFMLProvider(ApplicationState& app, SFMLInitializer& initializer, sf::RenderWindow& window) noexcept;

    auto GetInput() -> void override;
};

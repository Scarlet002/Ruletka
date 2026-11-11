#pragma once

#include "GameEnums.h"
#include "UI.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class SFMLInitializer;
class SFMLRenderer;
class SFMLProvider;

class SFMLUI final : public UI
{
private:
    std::unique_ptr<SFMLInitializer> m_initializer;
    std::unique_ptr<SFMLRenderer> m_renderer;
    std::unique_ptr<SFMLProvider> m_provider;
    std::unique_ptr<sf::RenderWindow> m_window;

public:
    SFMLUI(std::unique_ptr<SFMLInitializer> initializer, std::unique_ptr<SFMLRenderer> renderer,
           std::unique_ptr<SFMLProvider> provider, std::unique_ptr<sf::RenderWindow> window) noexcept;

    SFMLUI(const SFMLUI&) = delete;
    auto operator=(const SFMLUI&) -> SFMLUI& = delete;

    SFMLUI(SFMLUI&&) = delete;
    auto operator=(SFMLUI&&) -> SFMLUI& = delete;

    auto GetInput() -> void override;
    [[nodiscard]]
    auto GetUIType() const noexcept -> GameEnums::UIType override;
    auto Initialize() -> void override; // <- to nie powinno być public
    auto Render() -> void override;

    ~SFMLUI() noexcept override;
};

#include "SFMLUI.h"
#include "GameEnums.h"
#include "SFMLInitializer.h"
#include "SFMLProvider.h"
#include "SFMLRenderer.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <utility>

SFMLUI::~SFMLUI() noexcept = default;

SFMLUI::SFMLUI(std::unique_ptr<SFMLInitializer> initializer, std::unique_ptr<SFMLRenderer> renderer,
               std::unique_ptr<SFMLProvider> provider, std::unique_ptr<sf::RenderWindow> window) noexcept
    : m_initializer(std::move(initializer)), m_renderer(std::move(renderer)), m_provider(std::move(provider)),
      m_window(std::move(window))
{
    m_initializer->Initialize();
}

auto SFMLUI::GetInput() -> void
{
    m_provider->GetInput();
}

auto SFMLUI::GetUIType() const noexcept -> GameEnums::UIType
{
    return GameEnums::UIType::SFML;
}

auto SFMLUI::Render() -> void
{
    m_renderer->Render();
}

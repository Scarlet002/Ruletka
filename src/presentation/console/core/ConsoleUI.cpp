#include "ConsoleUI.h"
#include "ConsoleInitializer.h"
#include "ConsoleProvider.h"
#include "ConsoleRenderer.h"
#include "GameEnums.h"
#include <memory>
#include <utility>

ConsoleUI::~ConsoleUI() noexcept = default;

ConsoleUI::ConsoleUI(std::unique_ptr<ConsoleInitializer> initializer, std::unique_ptr<ConsoleRenderer> renderer,
                     std::unique_ptr<ConsoleProvider> provider) noexcept
    : m_initializer(std::move(initializer)), m_renderer(std::move(renderer)), m_provider(std::move(provider))
{
    m_initializer->Initialize();
}

auto ConsoleUI::GetInput() -> void
{
    m_provider->GetInput();
}

auto ConsoleUI::GetUIType() const noexcept -> GameEnums::UIType
{
    return GameEnums::UIType::CONSOLE;
}

auto ConsoleUI::Render() -> void
{
    m_renderer->Render();
}

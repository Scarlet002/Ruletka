#pragma once

#include "GameEnums.h"
#include "UI.h"
#include <memory>

class ConsoleInitializer;
class ConsoleRenderer;
class ConsoleProvider;

class ConsoleUI final : public UI
{
private:
    std::unique_ptr<ConsoleInitializer> m_initializer;
    std::unique_ptr<ConsoleRenderer> m_renderer;
    std::unique_ptr<ConsoleProvider> m_provider;

public:
    ConsoleUI(std::unique_ptr<ConsoleInitializer> initializer, std::unique_ptr<ConsoleRenderer> renderer,
              std::unique_ptr<ConsoleProvider> provider) noexcept;

    auto GetInput() -> void override;
    [[nodiscard]]
    auto GetUIType() const noexcept -> GameEnums::UIType override;
    auto Render() -> void override;

    ~ConsoleUI() noexcept override;
};

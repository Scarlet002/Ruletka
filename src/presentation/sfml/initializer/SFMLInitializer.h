#pragma once

#include "Button.hpp"
#include "GameConfig.h"
#include "Initializer.h"
#include "SFMLColors.hpp"
#include "SFMLLayout.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <cstddef>
#include <ranges>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

class SFMLInitializer final : public Initializer
{
private:
    std::string m_bufferString;
    sf::Font m_font;
    sf::Text m_filenameText{m_font};
    sf::Text m_filenameLabel{m_font};
    sf::Text m_bufferText{m_font};
    sf::RectangleShape m_bufferRectangle;
    sf::RectangleShape m_filenameBox;
    sf::RenderWindow& m_window;
    std::vector<Button> m_restartButtons;
    std::vector<Button> m_mainButtons;
    std::vector<Button> m_itemButtons;
    std::vector<Button> m_difficultyButtons;
    std::vector<Button> m_serializationButtons;

    template <size_t N, typename T>
        requires std::is_enum_v<T>
    auto CreateButtons(std::vector<Button>& out, const std::array<std::pair<std::string_view, T>, N>& data) -> void
    {
        constexpr auto TOTAL_WIDTH = (static_cast<float>(N) * SFMLLayout::MENU_BUTTON_WIDTH) +
                                     (static_cast<float>(N - 1U) * SFMLLayout::MENU_BUTTON_SPACING);
        constexpr auto START_X =
            (static_cast<float>(GameConfig::WINDOW_WIDTH) - TOTAL_WIDTH) / SFMLLayout::CENTER_DIVISOR;

        out.clear();
        out.reserve(N);

        for (const auto& [index, entry] : std::views::enumerate(data))
        {
            const auto buttonX = START_X + (static_cast<float>(index) *
                                            (SFMLLayout::MENU_BUTTON_WIDTH + SFMLLayout::MENU_BUTTON_SPACING));

            auto& button = out.emplace_back(
                m_font, entry.first, std::to_underlying(entry.second), sf::Vector2f{buttonX, SFMLLayout::MENU_BUTTON_Y},
                sf::Vector2f{SFMLLayout::MENU_BUTTON_WIDTH, SFMLLayout::MENU_BUTTON_HEIGHT});

            button.m_rect.setFillColor(SFMLColors::BUTTON_FILL_COLOR);
            button.m_rect.setOutlineColor(SFMLColors::BUTTON_OUTLINE_COLOR);
            button.m_rect.setOutlineThickness(SFMLLayout::MENU_BUTTON_BORDER_THICKNESS);

            button.m_label.setFillColor(SFMLColors::BUTTON_LABEL_COLOR);
            const auto bounds = button.m_label.getLocalBounds();
            button.m_label.setOrigin(
                {bounds.size.x / SFMLLayout::CENTER_DIVISOR, bounds.size.y / SFMLLayout::CENTER_DIVISOR});
            button.m_label.setPosition({
                buttonX + (SFMLLayout::MENU_BUTTON_WIDTH / SFMLLayout::CENTER_DIVISOR),
                SFMLLayout::MENU_BUTTON_Y + (SFMLLayout::MENU_BUTTON_HEIGHT / SFMLLayout::CENTER_DIVISOR),
            });
        }
    }

    auto CreateRestartButtons() -> void;
    auto CreateFilenameInput() -> void;

public:
    explicit SFMLInitializer(sf::RenderWindow& window);

    auto Initialize() -> void override;
    auto ResetBufferRectangle() noexcept -> void;
    auto ResetBufferText() noexcept -> void;

    [[nodiscard]]
    auto GetRestartButtons() noexcept -> auto&
    {
        return m_restartButtons;
    }

    [[nodiscard]]
    auto GetMainButtons() noexcept -> auto&
    {
        return m_mainButtons;
    }

    [[nodiscard]]
    auto GetItemButtons() noexcept -> auto&
    {
        return m_itemButtons;
    }

    [[nodiscard]]
    auto GetDifficultyButtons() noexcept -> auto&
    {
        return m_difficultyButtons;
    }

    [[nodiscard]]
    auto GetSerializationButtons() noexcept -> auto&
    {
        return m_serializationButtons;
    }

    [[nodiscard]]
    auto GetRestartButtons() const noexcept -> const auto&
    {
        return m_restartButtons;
    }

    [[nodiscard]]
    auto GetMainButtons() const noexcept -> const auto&
    {
        return m_mainButtons;
    }

    [[nodiscard]]
    auto GetItemButtons() const noexcept -> const auto&
    {
        return m_itemButtons;
    }

    [[nodiscard]]
    auto GetDifficultyButtons() const noexcept -> const auto&
    {
        return m_difficultyButtons;
    }

    [[nodiscard]]
    auto GetSerializationButtons() const noexcept -> const auto&
    {
        return m_serializationButtons;
    }

    [[nodiscard]]
    auto GetBufferString() noexcept -> std::string&
    {
        return m_bufferString;
    }

    [[nodiscard]]
    auto GetBufferStringView() noexcept -> std::string_view
    {
        return m_bufferString;
    }

    [[nodiscard]]
    auto GetBufferText() noexcept -> sf::Text&
    {
        return m_bufferText;
    }

    [[nodiscard]]
    auto GetBufferRectangle() noexcept -> sf::RectangleShape&
    {
        return m_bufferRectangle;
    }

    [[nodiscard]]
    auto GetFilenameText() noexcept -> sf::Text&
    {
        return m_filenameText;
    }

    [[nodiscard]]
    auto GetFilenameBox() noexcept -> sf::RectangleShape&
    {
        return m_filenameBox;
    }

    [[nodiscard]]
    auto GetFilenameLabel() noexcept -> sf::Text&
    {
        return m_filenameLabel;
    }

    [[nodiscard]]
    auto GetFont() noexcept -> sf::Font&
    {
        return m_font;
    }

    [[nodiscard]]
    auto GetFilenameText() const noexcept -> const sf::Text&
    {
        return m_filenameText;
    }

    [[nodiscard]]
    auto GetFilenameBox() const noexcept -> const sf::RectangleShape&
    {
        return m_filenameBox;
    }

    [[nodiscard]]
    auto GetFilenameLabel() const noexcept -> const sf::Text&
    {
        return m_filenameLabel;
    }

    [[nodiscard]]
    auto GetFont() const noexcept -> const sf::Font&
    {
        return m_font;
    }
};

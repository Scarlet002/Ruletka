#pragma once

#include "GameConfig.h"
#include "Renderer.h"
#include "SFMLLayout.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <string_view>

struct Button;

class ApplicationState;
class DomainState;
class SFMLInitializer;
class Logger;

class SFMLRenderer final : public Renderer
{
private:
    const ApplicationState& m_app;
    const DomainState& m_domain;
    Logger& m_logger;
    SFMLInitializer& m_initializer;
    sf::RenderWindow& m_window;
    sf::Vector2f m_windowSize{static_cast<float>(GameConfig::WINDOW_WIDTH),
                              static_cast<float>(GameConfig::WINDOW_HEIGHT)};

    [[nodiscard]]
    auto GetScaleFactor() const -> float;
    [[nodiscard]]
    auto ScaleFont(float baseSize) const -> unsigned int;

    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    [[nodiscard]]
    auto ScaleFontWithWidthLimit(float baseSize, float panelWidth,
                                 float maxCharacters = SFMLLayout::DEFAULT_MAX_CHARACTERS) const -> unsigned int;

    auto DrawPanel(sf::FloatRect rect, sf::Color fill, bool withBorder = true) -> void;
    auto DrawText(std::string_view text, sf::Vector2f position, unsigned int size, sf::Color color,
                  sf::Text::Style style = sf::Text::Regular) -> float;
    auto DrawTextCentered(std::string_view text, sf::Vector2f center, unsigned int size, sf::Color color,
                          sf::Text::Style style = sf::Text::Regular) -> void;
    auto DrawTextTopCentered(std::string_view text, sf::Vector2f position, unsigned int size, sf::Color color,
                             sf::Text::Style style = sf::Text::Regular) -> void;
    auto DrawButton(Button& button, sf::FloatRect rect, sf::Color fill, unsigned int labelSize) -> void;

    // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
    auto DrawSegmentedBar(sf::FloatRect rect, uint8_t filled, uint8_t maxSegments, sf::Color fillColor,
                          sf::Color emptyColor = SFMLLayout::DEFAULT_EMPTY_BAR_COLOR) -> void;

    auto DrawStatsPanel(sf::FloatRect rect, bool isHuman) -> void;
    auto DrawMagazinePanel(sf::FloatRect rect) -> void;
    auto DrawDifficultyInfoPanel(sf::FloatRect rect) -> void;
    auto DrawGameLog(sf::FloatRect rect) -> void;
    auto DrawGameOverScreen() -> void;
    auto DrawFilenameInput() -> void;
    auto DrawDecisionPanel(sf::FloatRect rect) -> void;

public:
    SFMLRenderer(const ApplicationState& app, const DomainState& domain, Logger& logger, SFMLInitializer& initializer,
                 sf::RenderWindow& window) noexcept;

    auto Render() -> void override;
};

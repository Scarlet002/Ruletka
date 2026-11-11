#pragma once

#include "GameEnums.h"
#include "Renderer.h"
#include <sstream>
#include <string_view>

class ApplicationState;
class DomainState;
class Logger;

class ConsoleRenderer final : public Renderer
{
private:
    const ApplicationState& m_app;
    const DomainState& m_domain;
    const Logger& m_logger;

    static auto Clear() -> void;

    auto DisplayLastTurnLog(std::ostringstream& oss) const -> void;
    auto DisplayStats(std::ostringstream& oss, std::string_view line) const -> void;

    static auto MainMenu(std::ostringstream& oss, std::string_view line) -> void;
    static auto DifficultyMenu(std::ostringstream& oss, std::string_view line) -> void;
    static auto RestartMenu(std::ostringstream& oss, std::string_view line) -> void;
    static auto SerializationMenu(std::ostringstream& oss, std::string_view line) -> void;
    static auto InventoryMenu(std::ostringstream& oss, std::string_view line) -> void;

    [[nodiscard]]
    static auto GetAIDifficulty(GameEnums::Difficulty difficulty) noexcept -> std::string_view;
    [[nodiscard]]
    static auto GetSerializationType(GameEnums::SerializationFormat type) noexcept -> std::string_view;

public:
    ConsoleRenderer(const ApplicationState& app, const DomainState& domain, const Logger& logger);

    auto Render() -> void override;
};

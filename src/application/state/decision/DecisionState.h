#pragma once

#include "GameConfig.h"
#include "GameEnums.h"
#include <boost/static_string/static_string.hpp>
#include <optional>
#include <string_view>

class DecisionState final
{
private:
    boost::static_string<GameConfig::LOG_LINE_RESERVE> m_currentFilename;
    std::optional<GameEnums::MainChoice> m_currentMainChoice = std::nullopt;
    std::optional<GameEnums::ItemType> m_currentItemChoice = std::nullopt;
    std::optional<GameEnums::Difficulty> m_currentDifficultyChoice = std::nullopt;
    std::optional<GameEnums::YesNo> m_currentYesNoChoice = std::nullopt;
    std::optional<GameEnums::UIType> m_currentUIChoice = std::nullopt;
    std::optional<GameEnums::SerializationFormat> m_currentSerializationChoice = std::nullopt;

public:
    explicit DecisionState();

    auto Reset() -> void;
    auto SetMainChoice(std::optional<GameEnums::MainChoice> newMainChoice) noexcept -> void;
    auto SetItemChoice(std::optional<GameEnums::ItemType> newItemChoice) noexcept -> void;
    auto SetDifficultyChoice(std::optional<GameEnums::Difficulty> newDifficultyChoice) noexcept -> void;
    auto SetYesNoChoice(std::optional<GameEnums::YesNo> newYesNoChoice) noexcept -> void;
    auto SetUIChoice(std::optional<GameEnums::UIType> newUIChoice) noexcept -> void;
    auto SetSerializationChoice(std::optional<GameEnums::SerializationFormat> newSerializationChoice) noexcept -> void;
    auto SetFilename(std::string_view newFilename) -> void;

    [[nodiscard]]
    auto GetMainChoice() const noexcept -> std::optional<GameEnums::MainChoice>;
    [[nodiscard]]
    auto GetItemChoice() const noexcept -> std::optional<GameEnums::ItemType>;
    [[nodiscard]]
    auto GetDifficultyChoice() const noexcept -> std::optional<GameEnums::Difficulty>;
    [[nodiscard]]
    auto GetYesNoChoice() const noexcept -> std::optional<GameEnums::YesNo>;
    [[nodiscard]]
    auto GetUIChoice() const noexcept -> std::optional<GameEnums::UIType>;
    [[nodiscard]]
    auto GetSerializationChoice() const noexcept -> std::optional<GameEnums::SerializationFormat>;
    [[nodiscard]]
    auto GetFilename() const noexcept -> std::string_view;
};

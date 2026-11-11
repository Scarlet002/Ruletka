#include "DecisionState.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include <optional>
#include <string_view>

DecisionState::DecisionState() : m_currentFilename(GameConfig::DEFAULT_FILENAME)
{
    m_currentFilename.reserve(GameConfig::LOG_LINE_RESERVE);
}

auto DecisionState::Reset() -> void
{
    m_currentFilename = GameConfig::DEFAULT_FILENAME;
    m_currentMainChoice = std::nullopt;
    m_currentItemChoice = std::nullopt;
    m_currentDifficultyChoice = std::nullopt;
    m_currentYesNoChoice = std::nullopt;
    m_currentUIChoice = std::nullopt;
    m_currentSerializationChoice = std::nullopt;
}

auto DecisionState::SetMainChoice(std::optional<GameEnums::MainChoice> newMainChoice) noexcept -> void
{
    m_currentMainChoice = newMainChoice;
}

auto DecisionState::SetItemChoice(std::optional<GameEnums::ItemType> newItemChoice) noexcept -> void
{
    m_currentItemChoice = newItemChoice;
}

auto DecisionState::SetDifficultyChoice(std::optional<GameEnums::Difficulty> newDifficultyChoice) noexcept -> void
{
    m_currentDifficultyChoice = newDifficultyChoice;
}

auto DecisionState::SetYesNoChoice(std::optional<GameEnums::YesNo> newYesNoChoice) noexcept -> void
{
    m_currentYesNoChoice = newYesNoChoice;
}

auto DecisionState::SetUIChoice(std::optional<GameEnums::UIType> newUIChoice) noexcept -> void
{
    m_currentUIChoice = newUIChoice;
}

auto DecisionState::SetSerializationChoice(
    std::optional<GameEnums::SerializationFormat> newSerializationChoice) noexcept -> void
{
    m_currentSerializationChoice = newSerializationChoice;
}

auto DecisionState::SetFilename(std::string_view newFilename) -> void
{
    m_currentFilename = newFilename;
}

[[nodiscard]]
auto DecisionState::GetMainChoice() const noexcept -> std::optional<GameEnums::MainChoice>
{
    return m_currentMainChoice;
}

[[nodiscard]]
auto DecisionState::GetItemChoice() const noexcept -> std::optional<GameEnums::ItemType>
{
    return m_currentItemChoice;
}

[[nodiscard]]
auto DecisionState::GetDifficultyChoice() const noexcept -> std::optional<GameEnums::Difficulty>
{
    return m_currentDifficultyChoice;
}

[[nodiscard]]
auto DecisionState::GetYesNoChoice() const noexcept -> std::optional<GameEnums::YesNo>
{
    return m_currentYesNoChoice;
}

[[nodiscard]]
auto DecisionState::GetUIChoice() const noexcept -> std::optional<GameEnums::UIType>
{
    return m_currentUIChoice;
}

[[nodiscard]]
auto DecisionState::GetSerializationChoice() const noexcept -> std::optional<GameEnums::SerializationFormat>
{
    return m_currentSerializationChoice;
}

[[nodiscard]]
auto DecisionState::GetFilename() const noexcept -> std::string_view
{
    return m_currentFilename;
}

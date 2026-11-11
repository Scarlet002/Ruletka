#pragma once

#include "Provider.h"
#include <cstdint>
#include <string>
#include <string_view>

class DecisionState;
class GameLoopState;

class ConsoleProvider final : public Provider
{
private:
    DecisionState& m_decision;
    const GameLoopState& m_gameLoop;

    auto InputDifficultyLevel() -> void;
    auto InputSerializationType() -> void;
    auto InputItemChoice() -> void;
    auto InputRestartChoice() -> void;
    auto InputMainChoice() -> void;
    auto InputFilenameChoice() -> void;
    static auto InputValidationFail() -> void;

public:
    ConsoleProvider(DecisionState& decision, const GameLoopState& gameLoop);

    [[nodiscard]]
    static auto GetValidatedInput(bool (*validator)(std::string_view)) -> std::string;
    [[nodiscard]]
    static auto GetValidatedInput(int lowerBand, int upperBand, bool (*validator)(int, int, int)) -> uint8_t;

    auto GetInput() -> void override;
};

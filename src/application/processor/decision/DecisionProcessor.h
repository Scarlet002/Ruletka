#pragma once

#include "GameEnums.h"
#include "IProcessor.h"
#include <memory>
#include <unordered_map>

class ApplicationState;
class DomainState;
class AIManager;
class UIManager;
class IAction;

class DecisionProcessor final : public IProcessor
{
private:
    std::unordered_map<GameEnums::MainChoice, std::unique_ptr<IAction>> m_decisions;
    ApplicationState& m_appState;
    DomainState& m_domainState;
    AIManager& m_aiManager;

    auto GetAIInput() -> void;
    auto CalcProbability() -> void;
    auto SetDecision(GameEnums::MainChoice action) -> void;

public:
    DecisionProcessor(ApplicationState& appState, DomainState& domainState, AIManager& aiManager);

    DecisionProcessor(const DecisionProcessor&) = delete;
    auto operator=(const DecisionProcessor&) -> DecisionProcessor& = delete;

    DecisionProcessor(DecisionProcessor&&) = delete;
    auto operator=(DecisionProcessor&&) -> DecisionProcessor& = delete;

    ~DecisionProcessor() noexcept override;

    auto AddAction(GameEnums::MainChoice key, std::unique_ptr<IAction> action) -> void;
    auto Process() -> void override;
};

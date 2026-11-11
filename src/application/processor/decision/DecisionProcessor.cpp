#include "DecisionProcessor.h"
#include "AIManager.h"
#include "ApplicationState.h"
#include "DecisionState.h"
#include "DomainState.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "IAction.h"
#include "ItemState.h"
#include "Magazine.h"
#include <memory>
#include <utility>

DecisionProcessor::~DecisionProcessor() noexcept = default;

DecisionProcessor::DecisionProcessor(ApplicationState& appState, DomainState& domainState, AIManager& aiManager)
    : m_appState(appState), m_domainState(domainState), m_aiManager(aiManager)
{
}

auto DecisionProcessor::AddAction(GameEnums::MainChoice key, std::unique_ptr<IAction> action) -> void
{
    m_decisions[key] = std::move(action);
}

auto DecisionProcessor::GetAIInput() -> void
{
    if (m_appState.GetGameLoopState().GetStarter() == GameEnums::PlayerType::COMPUTER)
    {
        CalcProbability();
        m_aiManager.GetInput();
    }
}

auto DecisionProcessor::SetDecision(GameEnums::MainChoice action) -> void
{
    const auto iterator = m_decisions.find(action);
    if (iterator == m_decisions.end())
    {
        return;
    }

    iterator->second->Execute();
    if (m_appState.GetGameLoopState().GetStarter() == GameEnums::PlayerType::HUMAN &&
        (action == GameEnums::MainChoice::HEAL || action == GameEnums::MainChoice::SHOOT))
    {
        m_appState.GetDecisionState().SetMainChoice(GameEnums::MainChoice::AUTOSAVE);
    }
}

auto DecisionProcessor::CalcProbability() -> void
{
    const auto& itemState = m_domainState.GetItemState();
    if (itemState.GetStateOfMagnifier() == GameEnums::YesNo::NO &&
        itemState.GetStateOfCellPhone() == GameEnums::YesNo::NO)
    {
        m_domainState.GetMagazine().CalculateHitProbability();
    }
}

auto DecisionProcessor::Process() -> void
{
    GetAIInput();
    const auto action = m_appState.GetDecisionState().GetMainChoice();
    if (action.has_value())
    {
        SetDecision(action.value());
    }
}

#include "GameLoopInitializer.h"
#include "ApplicationState.h"
#include "DecisionState.h"
#include "DomainState.h"
#include "GameLoopState.h"
#include "HP.h"
#include "Inventory.h"
#include "ItemState.h"
#include "Magazine.h"

GameLoopInitializer::GameLoopInitializer(ApplicationState& appState, DomainState& domainState) noexcept
    : m_appState(appState), m_domainState(domainState)
{
}

auto GameLoopInitializer::Initialize() -> void
{
    m_appState.GetDecisionState().Reset();
    m_domainState.GetItemState().Reset();
    m_domainState.GetMagazine().Reload();
    m_domainState.GetHumanHP().ResetHP();
    m_domainState.GetComputerHP().ResetHP();
    m_domainState.GetHumanInventory().ResetInventory();
    m_domainState.GetComputerInventory().ResetInventory();
    auto& gameLoopState = m_appState.GetGameLoopState();
    gameLoopState.Reset();
    gameLoopState.RandomizeStarter();
}

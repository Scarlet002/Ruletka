#include "InventoryProcessor.h"
#include "DecisionState.h"
#include "GameEnums.h"
#include "IAction.h"
#include <memory>
#include <utility>

InventoryProcessor::~InventoryProcessor() noexcept = default;

InventoryProcessor::InventoryProcessor(const DecisionState& decisionState) : m_decisionState(decisionState)
{
}

auto InventoryProcessor::Process() -> void
{
    const auto item = m_decisionState.GetItemChoice();
    if (!item.has_value())
    {
        return;
    }

    const auto value = item.value();
    if (value == GameEnums::ItemType::NOTHING)
    {
        return;
    }

    const auto iterator = m_itemActions.find(value);
    if (iterator != m_itemActions.end())
    {
        iterator->second->Execute();
    }
}

auto InventoryProcessor::AddAction(GameEnums::ItemType key, std::unique_ptr<IAction> action) -> void
{
    m_itemActions[key] = std::move(action);
}

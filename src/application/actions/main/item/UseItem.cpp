#include "UseItem.h"
#include "DecisionState.h"
#include "GameEnums.h"
#include "GameLoopState.h"
#include "InventoryProcessor.h"
#include <optional>

UseItem::~UseItem() noexcept = default;

UseItem::UseItem(IProcessor& inventory, DecisionState& decision, GameLoopState& loop) noexcept
    : m_inventory(inventory), m_decision(decision), m_loop(loop)
{
}

auto UseItem::Execute() -> void
{
    m_loop.SetCurrentMenu(GameEnums::Window::INVENTORY_MENU);
    m_inventory.Process();
    if (m_decision.GetItemChoice().has_value() || !m_decision.GetMainChoice().has_value())
    {
        m_decision.SetItemChoice(std::nullopt);
        m_decision.SetMainChoice(std::nullopt);
        m_loop.SetCurrentMenu(GameEnums::Window::MAIN_MENU);
    }
}

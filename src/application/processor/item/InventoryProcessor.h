#pragma once

#include "GameEnums.h"
#include "IProcessor.h"
#include <memory>
#include <unordered_map>

class DecisionState;
class IAction;

class InventoryProcessor final : public IProcessor
{
private:
    std::unordered_map<GameEnums::ItemType, std::unique_ptr<IAction>> m_itemActions;
    const DecisionState& m_decisionState;

public:
    explicit InventoryProcessor(const DecisionState& decisionState);

    InventoryProcessor(const InventoryProcessor&) = delete;
    auto operator=(const InventoryProcessor&) -> InventoryProcessor& = delete;

    InventoryProcessor(InventoryProcessor&&) = delete;
    auto operator=(InventoryProcessor&&) -> InventoryProcessor& = delete;

    ~InventoryProcessor() noexcept override;

    auto AddAction(GameEnums::ItemType key, std::unique_ptr<IAction> action) -> void;
    auto Process() -> void override;
};

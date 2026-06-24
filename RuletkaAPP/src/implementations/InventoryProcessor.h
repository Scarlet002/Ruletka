#pragma once
#include "ForwardDeclarations.h"
#include "Action.h"
#include "Processor.h"
#include "IGameState.h"
#include "AIManager.h"
#include "Logger.h"
#include "IPlayer.h"
#include "UI.h"
#include <memory>
#include <unordered_map>

class InventoryProcessor : public Processor
{
private:
    std::unordered_map<int8_t, std::shared_ptr<Action>> itemActions;
    std::shared_ptr<IGameState> gs;
    std::shared_ptr<Logger> logger;
    std::shared_ptr<UI> ui;
public:
    explicit InventoryProcessor(std::shared_ptr<IGameState> gs
        , std::shared_ptr<Logger> logger
        , std::shared_ptr<UI> ui);

    void AddAction(int8_t choice, std::shared_ptr<Action> action) override;

    void Process() override;
};
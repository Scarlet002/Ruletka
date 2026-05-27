#pragma once
#include "ForwardDeclarations.h"
#include "Processor.h"
#include "IPlayer.h"
#include "SerializationManager.h"
#include "AsyncSerializer.h"
#include "InventoryProcessor.h"
#include "Logger.h"
#include "IGameState.h"
#include "Action.h"
#include "AIManager.h"
#include "UI.h"
#include <unordered_map>

class DecisionProcessor : public Processor
{
private:
    std::unordered_map<int8_t, std::shared_ptr<Action>> decisions;
    std::shared_ptr<Action> decision;
    std::shared_ptr<IGameState> gs;
    std::shared_ptr<Logger> logger;
    std::shared_ptr<UI> ui;
    std::shared_ptr<AIManager> aim;

    void Decision();
    void CalcProbability();
    void SetDecision(int8_t choice);
public:
    explicit DecisionProcessor(std::shared_ptr<IGameState> gs
        , std::shared_ptr<AIManager> aim
        , std::shared_ptr<Logger> logger
        , std::shared_ptr<UI> ui);

    void AddAction(int8_t choice, std::shared_ptr<Action> action) override;

	void Process() override;
};

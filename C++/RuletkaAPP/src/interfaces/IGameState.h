#pragma once
#include "IGameStateAIs.h"
#include "IGameStateCore.h"
#include "IGameStateDecisions.h"
#include "IGameStateItems.h"
#include "IGameStateMagazine.h"
#include "IGameStatePlayers.h"
#include "IGameStateSerializations.h"
#include "IGameStateLoop.h"

class IGameState 
    : public IGameStateCore
    , public IGameStateAIs
    , public IGameStateItems
    , public IGameStateDecisions
    , public IGameStateMagazine
    , public IGameStateSerializations
    , public IGameStatePlayers
    , public IGameStateLoop
{
protected:
	IGameState() = default;
public:
	IGameState(const IGameState&) = delete;
	IGameState& operator=(const IGameState&) = delete;

	IGameState(IGameState&&) = delete;
	IGameState& operator=(IGameState&&) = delete;

	virtual ~IGameState() = default;
};
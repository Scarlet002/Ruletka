#pragma once

class IAIStrategyManager
{
public:
	virtual void SetStrategy(int difficulty) = 0;
	virtual int MakeDecision() const = 0;

	virtual ~IAIStrategyManager() = default;
};
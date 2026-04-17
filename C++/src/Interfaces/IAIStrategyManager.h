#pragma once
#include <cstdint>

class IAIStrategyManager
{
public:
	virtual void SetStrategy(int8_t difficulty) = 0;
	virtual int8_t Decision() const = 0;

	virtual ~IAIStrategyManager() = default;
};
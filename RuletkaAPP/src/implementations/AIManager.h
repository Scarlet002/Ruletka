#pragma once
#include "AI.h"
#include <memory>
#include <unordered_map>
#include <cstdint>
#include <cassert>
#include <utility>
#include <stdexcept>

class AIManager
{
private:
	std::unordered_map<uint8_t, std::shared_ptr<AI>> strategies;
	std::shared_ptr<AI> strategy;
public:
	AIManager() = default;

	AIManager(const AIManager&) = delete;
	AIManager& operator=(const AIManager&) = delete;

	AIManager(AIManager&&) = delete;
	AIManager& operator=(AIManager&&) = delete;

	void SetStrategy(uint8_t difficulty)
	{
		assert(strategies.contains(difficulty));
		if (strategies.contains(difficulty)) strategy = strategies.at(difficulty);
		else throw std::runtime_error("Brak wybranej strategii!");
	}

	void AddStrategy(uint8_t difficulty, std::shared_ptr<AI> ai)
	{
		assert(!strategies.contains(difficulty));
		if (!strategies.contains(difficulty))
		{
			strategies[difficulty] = std::move(ai);
			if (!strategy) strategy = strategies[difficulty];
		}
		else throw std::runtime_error("Proba zdublowania strategii!");
	}

	[[nodiscard]] int8_t Decision() const
	{
		assert(strategy);
		if (!strategy) throw std::runtime_error("Nie ustawiono strategii!");
		return strategy->Decision();
	}

	~AIManager() = default;
};
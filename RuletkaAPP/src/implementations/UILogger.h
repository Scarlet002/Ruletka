#pragma once
#include "LogObserver.h"
#include "Logger.h"
#include <string>
#include <vector>
#include <deque>
#include <memory>
#include <iostream>

class UILogger : public Logger
{
private:
	std::deque<std::string> logs;
	std::vector<std::shared_ptr<LogObserver>> observers;
public:
	explicit UILogger()
		: logs()
		, observers()
	{
		observers.reserve(GameConfig::maxObservers);
	}
	void UpdateLog(std::string newLogUpdate) override 
	{ 
		if (logs.size() >= GameConfig::maxLogsRendered) logs.pop_front();
		logs.push_back(newLogUpdate);
		NotifyObservers(newLogUpdate);
	}
	void NotifyObservers(std::string newLogUpdate) override 
	{ 
		for (const auto& observer : observers) observer->GetRecentLogUpdate(newLogUpdate); 
	}
	void AddObservers(std::shared_ptr<LogObserver> newObserver) override { observers.push_back(newObserver); }
};
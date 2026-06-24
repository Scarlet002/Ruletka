#pragma once
#include "LogObserver.h"
#include <string>
#include <memory>

class Logger
{
protected:
	Logger() = default;
public:
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	Logger(Logger&&) = delete;
	Logger& operator=(Logger&&) = delete;

	virtual void UpdateLog(std::string newLogUpdate) = 0;
	virtual void NotifyObservers(std::string newLogUpdate) = 0;
	virtual void AddObservers(std::shared_ptr<LogObserver> newObserver) = 0;

	virtual ~Logger() = default;
};
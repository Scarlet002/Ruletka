#pragma once
#include <string>

class LogObserver
{
protected:
	LogObserver() = default;
public:
	LogObserver(const LogObserver&) = delete;
	LogObserver& operator=(const LogObserver&) = delete;

	LogObserver(LogObserver&&) = delete;
	LogObserver& operator=(LogObserver&&) = delete;

	virtual void GetRecentLogUpdate(std::string newLogUpdate) = 0;

	virtual ~LogObserver() = default;
};
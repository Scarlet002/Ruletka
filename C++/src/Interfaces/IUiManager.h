#pragma once
#include "ForwardDeclarations.h"
#include <string>
#include <vector>
#include <cstdint>

class IUiManager
{
public:
    // UI methods
    virtual int8_t Decision() = 0;
    virtual bool Initialize() = 0;
	virtual void Render() = 0;
	virtual void ResetUI() = 0;
    virtual std::string GetFilename() const = 0;
    virtual std::string GetAIDifficulty(int8_t difficulty) const = 0;
	virtual bool GetUIType() const = 0;

    // Log methods
    virtual void SetLog(const std::vector<std::string>& newLog) = 0;
    virtual void ClearLog() = 0;
    virtual const std::vector<std::string>& GetLog() const = 0;
    virtual std::string GetRecentLogLine() const = 0;
    virtual void SetRecentLogLine(std::string newLogLine) = 0;

	virtual ~IUiManager() = default;
};

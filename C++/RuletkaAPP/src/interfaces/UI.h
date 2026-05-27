#pragma once
#include "ForwardDeclarations.h"
#include <string>
#include <vector>
#include <deque>
#include <cstdint>

class UI
{
protected:
	UI() = default;
public:
    UI(const UI&) = delete;
	UI& operator=(const UI&) = delete;

    UI(UI&&) = delete;
	UI& operator=(UI&&) = delete;

    // UI methods
    [[nodiscard]] virtual int8_t Decision() noexcept = 0;
    virtual void Initialize() = 0;
	virtual void Render() = 0;
	virtual void ResetUI() = 0;
    [[nodiscard]] virtual std::string GetFilename() const noexcept = 0;
    [[nodiscard]] virtual std::string GetAIDifficulty(int8_t difficulty) const noexcept = 0;
    [[nodiscard]] virtual bool GetUIType() const noexcept = 0;

    // Log methods
    virtual void ClearLog() = 0;
    [[nodiscard]] virtual const std::deque<std::string>& GetLog() const noexcept = 0;
    [[nodiscard]] virtual std::string GetRecentLogLine() const noexcept = 0;

	virtual ~UI() = default;
};

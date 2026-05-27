#pragma once
#include "ForwardDeclarations.h"
#include "UI.h"
#include "LogObserver.h"
#include "GameEnums.h"
#include <string>
#include <vector>
#include <deque>

class ConsoleUI : public UI, public LogObserver
{
private:
    std::string fileName = "";
    std::deque<std::string> log;
    const std::shared_ptr<IGameState> gs;

    // Methods related to rendering and handling input
    void InventoryMenu() const;
    void DisplayStats() const;
    void Menu() const;
    void DifficultyMenu() const;
    void RestartMenu() const;
    void SerializationMenu() const;
    int8_t InputRestartChoice() noexcept;
    int8_t InputSerializationType() noexcept;
	int8_t InputDifficultyLevel() noexcept;
    int8_t InputItemChoice() noexcept;
    void DisplayLastTurnLog();
    void Clear() const;
    std::string GetSerializationType(const int8_t serializationType) const noexcept;

public:
	explicit ConsoleUI(const std::shared_ptr<IGameState> gs);

    // UI methods
    int8_t Decision() noexcept override;
    void Initialize() override;
    void Render() override;
    void ResetUI() override;
    std::string GetAIDifficulty(int8_t difficulty) const noexcept override;
    std::string GetFilename() const noexcept override;
	bool GetUIType() const noexcept override;

    // Log methods
    void ClearLog() override;
    const std::deque<std::string>& GetLog() const noexcept override;
    std::string GetRecentLogLine() const noexcept override;
    
    void GetRecentLogUpdate(std::string newLogUpdate) override;
};
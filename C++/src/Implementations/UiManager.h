#pragma once
#include "ForwardDeclarations.h"
#include "IUiManager.h"
#include "GameState.h"
#include <string>
#include <vector>

class UiManager : public IUiManager 
{
private:
    std::string fileName = "";
	std::string autoSaveFileName = "autosave";
    std::string logLine = "";
    std::vector<std::string> log;
    const GameState& state;
public:
	explicit UiManager(const GameState& state);

    std::string GetFileName() const override;
    void SetFileName(std::string newFileName) override;
	void DisplayLastTurnLog() override;
    void SetLog(const std::vector<std::string>& newLog) override;
    void ClearLog() override;
    const std::vector<std::string>& GetLog() const override;
    std::string GetRecentLogLine() const override;
    void SetRecentLogLine(std::string newLogLine) override;
	int HumanDecision() override;
    void DisplayStats() const override;
    void Menu() const override;
    void DifficultyMenu() const override;
    std::string GetAIDifficulty(int difficulty) const override;
    void InventoryMenu() const override;

    void InputSaveTXT() override;
    void InputLoadTXT() override;
    void InputSaveJSON() override;
    void InputLoadJSON() override;
    int InputdifficultyLevel() override;
    int InputItemChoice() override;

    bool WantsToContinue() override;

    void ComputerChoosing() const override;
    void ComputerStarts() const override;
    void HumanStarts() const override;
    void ShowPointer() const override;
    void NewLine() const override;
    void AutoSaveDone() const override;
    std::string GetAutoSaveName() const override;
    void SavingSucces() const override;
    void LoadingSucces() const override;
    void DifficultyChangeSucces() const override;
    void InvalidInput() const override;
    void ComputerWin() const override;
    void HumanWin() const override;
    void EndOfBullets() const override;
    void ThankYou() const override;
    void Clear() const override;
};
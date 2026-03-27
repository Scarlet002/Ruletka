#pragma once
#include "ForwardDeclarations.h"
#include <string>
#include <vector>

class IUiManager
{
public:
	virtual std::string GetFileName() const = 0;
	virtual void SetFileName(std::string newFileName) = 0;
	virtual void DisplayLastTurnLog() = 0;
	virtual void SetLog(const std::vector<std::string>& newLog) = 0;
	virtual void ClearLog() = 0;
	virtual const std::vector<std::string>& GetLog() const = 0;
    virtual std::string GetRecentLogLine() const = 0;
    virtual void SetRecentLogLine(std::string newLogLine) = 0;
	virtual int HumanDecision() = 0;
    virtual void DisplayStats() const = 0;
    virtual void Menu() const = 0;
    virtual void DifficultyMenu() const = 0;
    virtual std::string GetAIDifficulty(int difficulty) const = 0;
    virtual void InventoryMenu() const = 0;

    virtual void InputSaveTXT() = 0;
    virtual void InputLoadTXT() = 0;
    virtual void InputSaveJSON() = 0;
    virtual void InputLoadJSON() = 0;
    virtual int InputdifficultyLevel() = 0;
    virtual int InputItemChoice() = 0;
    virtual bool WantsToContinue() = 0;

    virtual void ComputerChoosing() const = 0;
    virtual void ComputerStarts() const = 0;
    virtual void HumanStarts() const = 0;
    virtual void ShowPointer() const = 0;
    virtual void NewLine() const = 0;
    virtual void AutoSaveDone() const = 0;
    virtual std::string GetAutoSaveName() const = 0;
    virtual void SavingSucces() const = 0;
    virtual void LoadingSucces() const = 0;
    virtual void DifficultyChangeSucces() const = 0;
    virtual void InvalidInput() const = 0;
    virtual void ComputerWin() const = 0;
    virtual void HumanWin() const = 0;
    virtual void EndOfBullets() const = 0;
    virtual void ThankYou() const = 0;
    virtual void Clear() const = 0;

	virtual ~IUiManager() = default;
};

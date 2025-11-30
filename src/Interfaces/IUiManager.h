#pragma once
#include "ForwardDeclarations.h"
#include "GameState.h"
#include <string>

class IUiManager
{
public:

    virtual void DisplayStats(const GameState& gameState) const = 0;
    virtual void ScrollScreen() const = 0;
    virtual void Menu() const = 0;
    virtual void DifficultyMenu() const = 0;
    virtual void ShowAIDifficulty(int difficulty) const = 0;
    virtual void InputSaveTXT(string& fileName) = 0;
    virtual void InputLoadTXT(string& fileName) = 0;
    virtual void InputSaveJSON(string& fileName) = 0;
    virtual void InputLoadJSON(string& fileName) = 0;
    virtual void InputdifficultyLevel(GameState& gameState) = 0;
    virtual bool WantsToContinue(GameState& gameState) = 0;
    virtual void ComputerChoosing() const = 0;
    virtual void ComputerStarts() const = 0;
    virtual void HumanStarts() const = 0;
    virtual void ShowPointer() const = 0;
    virtual void NewLine() const = 0;
    virtual void AutoSaveDone() const = 0;
    virtual void ShowAutoSaveName(string& autoSaveFileName) const = 0;
    virtual void SavingSucces() const = 0;
    virtual void LoadingSucces() const = 0;
    virtual void DifficultyChangeSucces() const = 0;
    virtual void InvalidInput() const = 0;
    virtual void ComputerWin() const = 0;
    virtual void HumanWin() const = 0;
    virtual void EndOfBullets() const = 0;
    virtual void ThankYou() const = 0;

    virtual ~IUiManager() = default;
};

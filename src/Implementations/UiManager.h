#pragma once
#include "ForwardDeclarations.h"
#include "IUiManager.h"
#include "GameState.h"
#include <string>

using std::string;

class UiManager : public IUiManager {
public:
    UiManager() {};

    void DisplayStats(const GameState& gameState) const override;
    void ScrollScreen() const override;
    void Menu() const override;
    void DifficultyMenu() const override;
    void ShowAIDifficulty(int difficulty) const override;
    void InventoryMenu() const override;

    void InputSaveTXT(string& fileName) override;
    void InputLoadTXT(string& fileName) override;
    void InputSaveJSON(string& fileName) override;
    void InputLoadJSON(string& fileName) override;
    void InputdifficultyLevel(GameState& gameState) override;
    void InputItemChoice(GameState& gameState) override;

    bool WantsToContinue(GameState& gameState) override;

    void ComputerChoosing() const override;
    void ComputerStarts() const override;
    void HumanStarts() const override;
    void ShowPointer() const override;
    void NewLine() const override;
    void AutoSaveDone() const override;
    void ShowAutoSaveName(string& autoSaveFileName) const override;
    void SavingSucces() const override;
    void LoadingSucces() const override;
    void DifficultyChangeSucces() const override;
    void ItemUseSuccesHuman(GameState& gameState) const override;
    void ItemUseSuccesComputer(GameState& gameState) const override;
    void InvalidInput() const override;
    void ComputerWin() const override;
    void HumanWin() const override;
    void EndOfBullets() const override;
    void ThankYou() const override;
    void Clear() const override;

    ~UiManager() {};
};
#pragma once
#include "ForwardDeclarations.h"
#include "IUiManager.h"
#include "GameEnums.h"
#include <string>
#include <vector>

class UiManager : public IUiManager 
{
private:
    std::string fileName = "";
    std::string logLine = "";
    std::vector<std::string> log;
    std::vector<std::string> recentLog;
	bool showInventory = GameEnums::NOT_SHOWN;
	bool showSaveLoad = GameEnums::NOT_SHOWN;
	bool showDifficulty = GameEnums::NOT_SHOWN;
	bool showRestart = GameEnums::NOT_SHOWN;
    const GameState& state;

    // Metody prawdopodobnie do usuniecia
    inline void ComputerChoosing() const;
    inline void ComputerStarts() const;
    inline void HumanStarts() const;
    inline void ShowPointer() const;
    inline void NewLine() const;
    inline void AutoSaveDone() const;
    inline void SavingSucces() const;
    inline void LoadingSucces() const;
    inline void DifficultyChangeSucces() const;
    inline void InvalidInput() const;
    inline void ComputerWin() const;
    inline void HumanWin() const;
    inline void EndOfBullets() const;
    inline void ThankYou() const;
    inline void Clear() const;

    // Methods related to rendering and handling input
    inline void InventoryMenu() const;
    inline void DisplayStats() const;
    inline void Menu() const;
    inline void DifficultyMenu() const;
    inline void RestartMenu() const;
	inline int8_t HandleGameOverInput();
	inline int8_t InputDifficultyLevel();
    inline int8_t InputItemChoice();
    inline void SetRecentLog(const std::vector<std::string>& newRecentLog);
    inline const std::vector<std::string>& GetRecentLog() const;
    inline void DisplayLastTurnLog();

    // Gettery
    inline bool IsShowingInventoryMenu() const;
    inline bool IsShowingSaveLoadMenu() const;
    inline bool IsShowingDifficultyMenu() const;
    inline bool IsShowingRestartMenu() const;

    // Settery
    inline void SetItemMenu(bool newState);
    inline void SetSaveLoadMenu(bool newState);
    inline void SetDifficultyMenu(bool newState);
    inline void SetRestartMenu(bool newState);

public:
	explicit UiManager(const GameState& state);

    // UI methods
    int8_t Decision() override;
    bool Initialize() override;
    void Render() override;
    void ResetUI() override;
    std::string GetAIDifficulty(int8_t difficulty) const override;
    std::string GetFilename() const override;
	bool GetUIType() const override;

    // Log methods
    void SetLog(const std::vector<std::string>& newLog) override;
    void ClearLog() override;
    const std::vector<std::string>& GetLog() const override;
    std::string GetRecentLogLine() const override;
    void SetRecentLogLine(std::string newLogLine) override;
};
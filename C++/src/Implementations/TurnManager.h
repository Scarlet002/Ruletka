#pragma once
#include "ForwardDeclarations.h"
#include "ITurnManager.h"
#include "GameEnums.h"
#include "GameConfig.h"
#include <string>
#include <memory>
#include <cstdint>

class TurnManager : public ITurnManager
{
private:
    float hitProbability = 0.0;
    int8_t difficulty = GameConfig::defaultDifficulty;
    uint8_t starter = GameEnums::HUMAN;
    int8_t choice = GameEnums::NO_CHOICE;
	int8_t previousChoice = GameEnums::EXIT;
    uint8_t target = GameEnums::COMPUTER;
    uint8_t shooter = GameEnums::HUMAN;
    uint8_t item = GameEnums::NO_ITEMS;
    uint8_t damage = GameConfig::defaultDamage;
    uint8_t currentMenu = GameEnums::MAIN_MENU;
	uint8_t recentDifficulty = GameConfig::defaultDifficulty;
    bool wereHandCuffsUsed = GameEnums::ITEM_NOT_USED;
    bool wasInventoryShownForComputer = GameEnums::NOT_SHOWN;
    bool wasMagnifierUsed = GameEnums::ITEM_NOT_USED;
	bool wasCellPhoneUsed = GameEnums::ITEM_NOT_USED;
    bool wasLogCleared = GameEnums::LOG_NOT_CLEARED;
    bool wasAutoSaved = GameEnums::NOT_SAVING;
    bool isOnePlayerAlive = false;
public:
	// Setters and actions
	void SetDifficulty(int8_t newDifficulty) override;
    void SetItem(uint8_t newItem) override;
    void SetStarter(uint8_t newStarter) override;
    void SetChoice(int8_t newChoice) override;
	void SetPreviousChoice(int8_t newPreviousChoice) override;
    void SetTarget(uint8_t newTarget) override;
    void SetShooter(uint8_t newShooter) override;
    void SetDamage(uint8_t newDamage) override;
	void SetCurrentMenu(uint8_t newMenu) override;
    void SetRecentDifficulty(uint8_t newDifficulty) override;
    void SetStateOfHandCuffs(bool newState) override;
    void SetStateOfInventory(bool newState) override;
    void SetStateOfMagnifier(bool newState) override;
    void SetStateOfCellPhone(bool newState) override;
    void SetStateOfLog(bool newState) override;
    void SetStateOfAutoSave(bool newState) override;
    void SetHitProbability(float newProbability) override;
    void SetIsOnePlayerAlive(bool newState) override;
    uint8_t RandomizeStarter() override;
    void ResetDamage() override;

	// Getters
	int8_t GetDifficulty() const override;
    uint8_t GetStarter() const override;
    int8_t GetChoice() const override;
	int8_t GetPreviousChoice() const override;
    uint8_t GetTarget() const override;
    uint8_t GetShooter() const override;
    uint8_t GetDamage() const override;
    uint8_t GetItem() const override;
	uint8_t GetCurrentMenu() const override;
	uint8_t GetRecentDifficulty() const override;
    bool GetStateOfHandCuffs() const override;
    bool GetStateOfInventory() const override;
    bool GetStateOfMagnifier() const override;
    bool GetStateOfCellPhone() const override;
    bool GetStateOfLog() const override;
    bool GetStateOfAutoSave() const override;
	bool GetIsOnePlayerAlive() const override;
    float GetHitProbability() const override;
};
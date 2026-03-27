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
    double hitProbability = 0.0;
    uint8_t difficulty = GameConfig::defaultDifficulty;
    uint8_t starter = GameEnums::SHOOTER_HUMAN;
    uint8_t choice = GameEnums::NO_CHOICE;
    uint8_t target = GameEnums::TARGET_COMPUTER;
    uint8_t shooter = GameEnums::SHOOTER_HUMAN;
    uint8_t item = GameEnums::NO_ITEMS;
    uint8_t damage = GameConfig::defaultDamage;
    bool wereHandCuffsUsed = false;
    bool wasInventoryShownForComputer = GameEnums::INVENTORY_NOT_SHOWN;
    bool wasMagnifierUsed = false;
    bool wasCellPhoneUsed = false;
public:
	// Setters and actions
	void SetDifficulty(int newDifficulty) override;
    void SetItem(int newItem) override;
    void SetStarter(int newStarter) override;
    void SetChoice(int newChoice) override;
    void SetTarget(int newTarget) override;
    void SetShooter(int newShooter) override;
    void SetDamage(int newDamage) override;
    void SetStateOfHandCuffs(bool newState) override;
    void SetStateOfInventory(bool newState) override;
    void SetStateOfMagnifier(bool newState) override;
    void SetStateOfCellPhone(bool newState) override;
    void SetHitProbability(double newProbability) override;
    int RandomizeStarter() override;
    void ResetDamage() override;

	// Getters
	int GetDifficulty() const override;
    int GetStarter() const override;
    int GetChoice() const override;
    int GetTarget() const override;
    int GetShooter() const override;
    int GetDamage() const override;
    int GetItem() const override;
    bool GetStateOfHandCuffs() const override;
    bool GetStateOfInventory() const override;
    bool GetStateOfMagnifier() const override;
    bool GetStateOfCellPhone() const override;
    double GetHitProbability() const override;
};
#pragma once
#include <string>
#include <cstdint>

class ITurnManager
{
public:
	// Setters and actions
	virtual void SetDifficulty(int8_t newDifficulty) = 0;
    virtual void SetItem(uint8_t newItem) = 0;
    virtual void SetStarter(uint8_t newStarter) = 0;
    virtual void SetChoice(int8_t newChoice) = 0;
	virtual void SetPreviousChoice(int8_t newPreviousChoice) = 0;
    virtual void SetTarget(uint8_t newTarget) = 0;
    virtual void SetShooter(uint8_t newShooter) = 0;
    virtual void SetDamage(uint8_t newDamage) = 0;
	virtual void SetCurrentMenu(uint8_t newMenu) = 0;
    virtual void SetRecentDifficulty(uint8_t newDifficulty) = 0;
    virtual void SetStateOfHandCuffs(bool newState) = 0;
    virtual void SetStateOfInventory(bool newState) = 0;
    virtual void SetStateOfMagnifier(bool newState) = 0;
    virtual void SetStateOfCellPhone(bool newState) = 0;
    virtual void SetStateOfLog(bool newState) = 0;
    virtual void SetStateOfAutoSave(bool newState) = 0;
    virtual void SetHitProbability(float newProbability) = 0;
	virtual void SetIsOnePlayerAlive(bool newState) = 0;
    virtual uint8_t RandomizeStarter() = 0;
    virtual void ResetDamage() = 0;

	// Getters
	virtual int8_t GetDifficulty() const = 0;
    virtual uint8_t GetStarter() const = 0;
    virtual int8_t GetChoice() const = 0;
	virtual int8_t GetPreviousChoice() const = 0;
    virtual uint8_t GetTarget() const = 0;
    virtual uint8_t GetShooter() const = 0;
    virtual uint8_t GetDamage() const = 0;
    virtual uint8_t GetItem() const = 0;
	virtual uint8_t GetCurrentMenu() const = 0;
    virtual uint8_t GetRecentDifficulty() const = 0;
    virtual bool GetStateOfHandCuffs() const = 0;
    virtual bool GetStateOfInventory() const = 0;
    virtual bool GetStateOfMagnifier() const = 0;
    virtual bool GetStateOfCellPhone() const = 0;
    virtual bool GetStateOfLog() const = 0;
    virtual bool GetStateOfAutoSave() const = 0;
	virtual bool GetIsOnePlayerAlive() const = 0;
    virtual float GetHitProbability() const = 0;

    virtual ~ITurnManager() = default;
};
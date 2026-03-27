#pragma once
#include <string>

class ITurnManager
{
public:
	// Setters and actions
	virtual void SetDifficulty(int newDifficulty) = 0;
    virtual void SetItem(int newItem) = 0;
    virtual void SetStarter(int newStarter) = 0;
    virtual void SetChoice(int newChoice) = 0;
    virtual void SetTarget(int newTarget) = 0;
    virtual void SetShooter(int newShooter) = 0;
    virtual void SetDamage(int newDamage) = 0;
    virtual void SetStateOfHandCuffs(bool newState) = 0;
    virtual void SetStateOfInventory(bool newState) = 0;
    virtual void SetStateOfMagnifier(bool newState) = 0;
    virtual void SetStateOfCellPhone(bool newState) = 0;
    virtual void SetHitProbability(double newProbability) = 0;
    virtual int RandomizeStarter() = 0;
    virtual void ResetDamage() = 0;

	// Getters
	virtual int GetDifficulty() const = 0;
    virtual int GetStarter() const = 0;
    virtual int GetChoice() const = 0;
    virtual int GetTarget() const = 0;
    virtual int GetShooter() const = 0;
    virtual int GetDamage() const = 0;
    virtual int GetItem() const = 0;
    virtual bool GetStateOfHandCuffs() const = 0;
    virtual bool GetStateOfInventory() const = 0;
    virtual bool GetStateOfMagnifier() const = 0;
    virtual bool GetStateOfCellPhone() const = 0;
    virtual double GetHitProbability() const = 0;

    virtual ~ITurnManager() = default;
};
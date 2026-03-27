#pragma once
#include <vector>
#include <cstdint>

class Inventory
{
public:
	virtual void GetRandomItem() = 0;
	virtual void GetNumberOfItems() = 0;
	virtual void UseItem(int itemType) = 0;
	virtual void ResetInventory() = 0;

	virtual void SetFreeSlots(int newFree) = 0;
	virtual void SetSaws(int newSaws) = 0;
	virtual void SetBeers(int newBeers) = 0;
	virtual void SetMagnifiers(int newMagnifiers) = 0;
	virtual void SetHandCuffs(int newHandCuffs) = 0;
	virtual void SetInverters(int newInverters) = 0;
	virtual void SetCellPhones(int newCellPhones) = 0;
	virtual void SetInventory(const std::vector<uint8_t>& newInventory) = 0;

	virtual int GetFreeSlots() const = 0;
	virtual int GetSaws() const = 0;
	virtual int GetBeers() const = 0;
	virtual int GetMagnifiers() const = 0;
	virtual int GetHandCuffs() const = 0;
	virtual int GetInverters() const = 0;
	virtual int GetCellPhones() const = 0;
	virtual const std::vector<uint8_t>& GetInventory() const = 0;

	virtual ~Inventory() = default;
};


#pragma once
#include <vector>
#include <cstdint>

class Inventory
{
public:
	virtual void GetRandomItem() = 0;
	virtual void GetNumberOfItems() = 0;
	virtual void UseItem(uint8_t itemType) = 0;
	virtual void ResetInventory() = 0;

	virtual void SetFreeSlots(uint8_t newFree) = 0;
	virtual void SetSaws(uint8_t newSaws) = 0;
	virtual void SetBeers(uint8_t newBeers) = 0;
	virtual void SetMagnifiers(uint8_t newMagnifiers) = 0;
	virtual void SetHandCuffs(uint8_t newHandCuffs) = 0;
	virtual void SetInverters(uint8_t newInverters) = 0;
	virtual void SetCellPhones(uint8_t newCellPhones) = 0;
	virtual void SetInventory(const std::vector<uint8_t>& newInventory) = 0;

	virtual uint8_t GetFreeSlots() const = 0;
	virtual uint8_t GetSaws() const = 0;
	virtual uint8_t GetBeers() const = 0;
	virtual uint8_t GetMagnifiers() const = 0;
	virtual uint8_t GetHandCuffs() const = 0;
	virtual uint8_t GetInverters() const = 0;
	virtual uint8_t GetCellPhones() const = 0;
	virtual const std::vector<uint8_t>& GetInventory() const = 0;

	virtual ~Inventory() = default;
};


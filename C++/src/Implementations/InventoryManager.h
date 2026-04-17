#pragma once
#include "Inventory.h"
#include "GameConfig.h"
#include "ForwardDeclarations.h"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <cstdint>

class InventoryManager : public Inventory
{
private:
	std::vector<uint8_t> inventory;
	uint8_t free = GameConfig::minInventorySize;
	uint8_t numberOfItems = GameConfig::minNumberOfItems;
	uint8_t saws = GameConfig::minNumberOfItems;
	uint8_t cellPhones = GameConfig::minNumberOfItems;
	uint8_t beers = GameConfig::minNumberOfItems;
	uint8_t handCuffs = GameConfig::minNumberOfItems;
	uint8_t magnifiers = GameConfig::minNumberOfItems;
	uint8_t inverters = GameConfig::minNumberOfItems;
public:
	explicit InventoryManager();

	void GetRandomItem() override;
	void GetNumberOfItems() override;
	void UseItem(uint8_t itemType) override;
	void ResetInventory() override;

	void SetFreeSlots(uint8_t newFree) override;
	void SetSaws(uint8_t newSaws) override;
	void SetBeers(uint8_t newBeers) override;
	void SetMagnifiers(uint8_t newMagnifiers) override;
	void SetHandCuffs(uint8_t newHandCuffs) override;
	void SetInverters(uint8_t newInverters) override;
	void SetCellPhones(uint8_t newCellPhones) override;
	void SetInventory(const std::vector<uint8_t>& newInventory) override;

	uint8_t GetFreeSlots() const override;
	uint8_t GetSaws() const override;
	uint8_t GetBeers() const override;
	uint8_t GetMagnifiers() const override;
	uint8_t GetHandCuffs() const override;
	uint8_t GetInverters() const override;
	uint8_t GetCellPhones() const override;
	const std::vector<uint8_t>& GetInventory() const override;
};


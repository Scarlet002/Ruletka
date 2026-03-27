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
	void UseItem(int itemType) override;
	void ResetInventory() override;

	void SetFreeSlots(int newFree) override;
	void SetSaws(int newSaws) override;
	void SetBeers(int newBeers) override;
	void SetMagnifiers(int newMagnifiers) override;
	void SetHandCuffs(int newHandCuffs) override;
	void SetInverters(int newInverters) override;
	void SetCellPhones(int newCellPhones) override;
	void SetInventory(const std::vector<uint8_t>& newInventory) override;

	int GetFreeSlots() const override;
	int GetSaws() const override;
	int GetBeers() const override;
	int GetMagnifiers() const override;
	int GetHandCuffs() const override;
	int GetInverters() const override;
	int GetCellPhones() const override;
	const std::vector<uint8_t>& GetInventory() const override;
};


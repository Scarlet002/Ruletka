#include "InventoryManager.h"
#include "GameEnums.h"
#include "GameConfig.h"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>
#include <cstdint>

InventoryManager::InventoryManager() 
	: inventory() 
	{ inventory.resize(GameConfig::maxInventorySize, GameEnums::NO_ITEMS); }

void InventoryManager::UseItem(uint8_t itemType)
{
	uint8_t k = 0;
	for (uint8_t& item : inventory)
	{
		if (item == itemType
			&& k == 0)
		{
			item = GameEnums::NO_ITEMS;
			k++;
			break;
		}
	}
	GetNumberOfItems();
}

void InventoryManager::GetRandomItem() 
{
	uint8_t k = 0;
	for (uint8_t& item : inventory)
	{
		if (GetFreeSlots() > 0 
			&& k < GameConfig::maxItemsRand)
		{
			if (item == GameEnums::NO_ITEMS)
			{
				item = rand() % GameConfig::numberOfItemTypes
					+ GameConfig::minItemsRand;
				k++;
			}
		}
		else { break; }
	}
	GetNumberOfItems();
}

void InventoryManager::GetNumberOfItems()
{
	SetFreeSlots(GameConfig::minInventorySize);
	SetSaws(GameConfig::minSaws);
	SetBeers(GameConfig::minBeers);
	SetMagnifiers(GameConfig::minMagnifiers);
	SetInverters(GameConfig::minInverters);
	SetCellPhones(GameConfig::minCellPhones);
	SetHandCuffs(GameConfig::minHandCuffs);

	for (uint8_t& item : inventory)
	{
		if (item == GameEnums::CELLPHONE) { cellPhones++; }
		else if (item == GameEnums::BEER) { beers++; }
		else if (item == GameEnums::SAW) { saws++; }
		else if (item == GameEnums::MAGNIFIER) { magnifiers++; }
		else if (item == GameEnums::INVERTER) { inverters++; }
		else if (item == GameEnums::HANDCUFFS) { handCuffs++; }
		else { free++; }
	}
	SetFreeSlots(free);
	SetSaws(saws);
	SetBeers(beers);
	SetMagnifiers(magnifiers);
	SetInverters(inverters);
	SetCellPhones(cellPhones);
	SetHandCuffs(handCuffs);
}

void InventoryManager::ResetInventory()
{
	inventory.clear();
	SetFreeSlots(GameConfig::maxInventorySize);
	SetSaws(GameConfig::minSaws);
	SetBeers(GameConfig::minBeers);
	SetMagnifiers(GameConfig::minMagnifiers);
	SetInverters(GameConfig::minInverters);
	SetCellPhones(GameConfig::minCellPhones);
	SetHandCuffs(GameConfig::minHandCuffs);
	inventory.resize(GameConfig::maxInventorySize, GameEnums::NO_ITEMS);
}

void InventoryManager::SetFreeSlots(uint8_t newFree) { free = newFree; }

void InventoryManager::SetSaws(uint8_t newSaws) { saws = newSaws; }

void InventoryManager::SetBeers(uint8_t newBeers) { beers = newBeers; }

void InventoryManager::SetMagnifiers(uint8_t newMagnifiers) { magnifiers = newMagnifiers; }

void InventoryManager::SetHandCuffs(uint8_t newHandCuffs) { handCuffs = newHandCuffs; }

void InventoryManager::SetInverters(uint8_t newInverters) { inverters = newInverters; }

void InventoryManager::SetCellPhones(uint8_t newCellPhones) { cellPhones = newCellPhones; }

void InventoryManager::SetInventory(const std::vector<uint8_t>& newInventory) { inventory = newInventory; }

uint8_t InventoryManager::GetFreeSlots() const { return free; }

uint8_t InventoryManager::GetSaws() const { return saws; }

uint8_t InventoryManager::GetBeers() const { return beers; }

uint8_t InventoryManager::GetMagnifiers() const { return magnifiers; }

uint8_t InventoryManager::GetHandCuffs() const { return handCuffs; }

uint8_t InventoryManager::GetInverters() const { return inverters; }

uint8_t InventoryManager::GetCellPhones() const { return cellPhones; }

const std::vector<uint8_t>& InventoryManager::GetInventory() const { return inventory; }
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

void InventoryManager::UseItem(int itemType)
{
	uint8_t k = 0;
	for (uint8_t i = 0; i < inventory.size(); ++i)
	{
		if (inventory[i] == itemType 
			&& k == 0)
		{
			inventory[i] = GameEnums::NO_ITEMS;
			k++;
		}
		else { continue; }
	}
	GetNumberOfItems();
}
void InventoryManager::GetRandomItem() 
{
	uint8_t k = 0;
	for (uint8_t i = 0; i < inventory.size(); ++i)
	{
		if (GetFreeSlots() > 0 
			&& k < GameConfig::maxItemsRand)
		{
			if (inventory[i] == GameEnums::NO_ITEMS)
			{
				inventory[i] = rand() % GameConfig::numberOfItemTypes 
					+ GameConfig::minItemsRand;
				k++;
			}
			else { continue; }
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

	for (uint8_t i = 0; i < inventory.size(); ++i)
	{
		if (inventory[i] == GameEnums::CELLPHONE) { cellPhones++; }
		else if (inventory[i] == GameEnums::BEER) { beers++; }
		else if (inventory[i] == GameEnums::SAW) { saws++; }
		else if (inventory[i] == GameEnums::MAGNIFIER) { magnifiers++; }
		else if (inventory[i] == GameEnums::INVERTER) { inverters++; }
		else if (inventory[i] == GameEnums::HANDCUFFS) { handCuffs++; }
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
void InventoryManager::SetFreeSlots(int newFree) { free = newFree; }
void InventoryManager::SetSaws(int newSaws) { saws = newSaws; }
void InventoryManager::SetBeers(int newBeers) { beers = newBeers; }
void InventoryManager::SetMagnifiers(int newMagnifiers) { magnifiers = newMagnifiers; }
void InventoryManager::SetHandCuffs(int newHandCuffs) { handCuffs = newHandCuffs; }
void InventoryManager::SetInverters(int newInverters) { inverters = newInverters; }
void InventoryManager::SetCellPhones(int newCellPhones) { cellPhones = newCellPhones; }
void InventoryManager::SetInventory(const std::vector<uint8_t>& newInventory) { inventory = newInventory; }

int InventoryManager::GetFreeSlots() const { return free; }
int InventoryManager::GetSaws() const { return saws; }
int InventoryManager::GetBeers() const { return beers; }
int InventoryManager::GetMagnifiers() const { return magnifiers; }
int InventoryManager::GetHandCuffs() const { return handCuffs; }
int InventoryManager::GetInverters() const { return inverters; }
int InventoryManager::GetCellPhones() const { return cellPhones; }
const std::vector<uint8_t>& InventoryManager::GetInventory() const { return inventory; }
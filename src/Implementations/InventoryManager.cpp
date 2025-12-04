#include "InventoryManager.h"
#include "GameState.h"
#include "GameEnums.h"
#include "GameConfig.h"
#include "CellPhone.h"
#include "Beer.h"
#include "HandCuffs.h"
#include "Saw.h"
#include "Inverter.h"
#include "Magnifier.h"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>

using std::vector;

InventoryManager::InventoryManager(GameConfig& gameConfig) : 
	gameConfig(gameConfig),
	free(gameConfig.maxInventorySize),
	numberOfItems(gameConfig.minNumberOfItems),
	saws(gameConfig.minSaws),
	beers(gameConfig.minBeers),
	magnifiers(gameConfig.minMagnifiers),
	handCuffsAmount(gameConfig.minHandCuffs),
	inverters(gameConfig.minInverters),
	cellPhones(gameConfig.minCellPhones), 
	inventorySize(gameConfig.maxInventorySize),
	inventory(gameConfig.maxInventorySize, GameEnums::NOITEMS)
{}

void InventoryManager::GetRandomItem(GameState& gameState) 
{
	int k = 0;
	for (int i = 0; i < inventorySize; i++)
	{
		if (GetFreeSlots() > 0 && k < 2)
		{
			if (inventory[i] == GameEnums::NOITEMS)
			{
				inventory[i] = rand() % gameState.gameConfig.numberOfItemTypes + gameState.gameConfig.minItemsRand;
				SetFreeSlots(GetFreeSlots() - 1);
				GetNumberOfItems(gameState);
				k++;
			}
			else
			{
				continue;
			}
		}
		else
		{
			break;
		}
	}
}

void InventoryManager::GetNumberOfItems(GameState& gameState)
{
	SetFreeSlots(gameState.gameConfig.maxInventorySize);
	SetSaws(gameState.gameConfig.minSaws);
	SetBeers(gameState.gameConfig.minBeers);
	SetMagnifiers(gameState.gameConfig.minMagnifiers);
	SetInverters(gameState.gameConfig.minInverters);
	SetCellPhones(gameState.gameConfig.minCellPhones);
	SetHandCuffs(gameState.gameConfig.minHandCuffs);

	for (int i = 0; i < inventorySize; i++)
	{
		if (inventory[i] == GameEnums::NOITEMS)
		{
			free++;
		}
		else if (inventory[i] == GameEnums::CELLPHONE)
		{
			cellPhones++;
		}
		else if (inventory[i] == GameEnums::BEER)
		{
			beers++;
		}
		else if (inventory[i] == GameEnums::SAW)
		{
			saws++;
		}
		else if (inventory[i] == GameEnums::MAGNIFIER)
		{
			magnifiers++;
		}
		else if (inventory[i] == GameEnums::INVERTER)
		{
			inverters++;
		}
		else if (inventory[i] == GameEnums::HANDCUFFS)
		{
			handCuffsAmount++;
		}
	}
	SetFreeSlots(free);
	SetSaws(saws);
	SetBeers(beers);
	SetMagnifiers(magnifiers);
	SetInverters(inverters);
	SetCellPhones(cellPhones);
	SetHandCuffs(handCuffsAmount);
}

int InventoryManager::SetFreeSlots(int newFree) { return free = newFree; }
int InventoryManager::SetSaws(int newSaws) { return saws = newSaws; }
int InventoryManager::SetBeers(int newBeers) { return beers = newBeers; }
int InventoryManager::SetMagnifiers(int newMagnifiers) { return magnifiers = newMagnifiers; }
int InventoryManager::SetHandCuffs(int newHandCuffs) { return handCuffsAmount = newHandCuffs; }
int InventoryManager::SetInverters(int newInverters) { return inverters = newInverters; }
int InventoryManager::SetCellPhones(int newCellPhones) { return cellPhones = newCellPhones; }

int InventoryManager::GetFreeSlots() const { return free; }
int InventoryManager::GetSaws() const { return saws; }
int InventoryManager::GetBeers() const { return beers; }
int InventoryManager::GetMagnifiers() const { return magnifiers; }
int InventoryManager::GetHandCuffs() const { return handCuffsAmount; }
int InventoryManager::GetInverters() const { return inverters; }
int InventoryManager::GetCellPhones() const { return cellPhones; }

void InventoryManager::ResetInventory(GameState& gameState) 
{ 
	inventory.clear();
	SetFreeSlots(gameState.gameConfig.maxInventorySize);
	SetSaws(gameState.gameConfig.minSaws);
	SetBeers(gameState.gameConfig.minBeers);
	SetMagnifiers(gameState.gameConfig.minMagnifiers);
	SetInverters(gameState.gameConfig.minInverters);
	SetCellPhones(gameState.gameConfig.minCellPhones);
	SetHandCuffs(gameState.gameConfig.minHandCuffs);
	inventory.resize(gameState.gameConfig.maxInventorySize, GameEnums::NOITEMS);
}

void InventoryManager::UseSaw(GameState& gameState) 
{
	int k = 0;
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] == GameEnums::SAW && k == 0)
		{
			inventory[i] = GameEnums::NOITEMS;
			SetSaws(GetSaws() - 1);
			GetNumberOfItems(gameState);
			k++;
		}
		else
		{
			continue;
		}
	}
	saw.UseItem(gameState); 
	GetNumberOfItems(gameState); 
}
void InventoryManager::UseBeer(GameState& gameState) 
{
	int k = 0;
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] == GameEnums::BEER && k == 0)
		{
			inventory[i] = GameEnums::NOITEMS;
			SetBeers(GetBeers() - 1);
			GetNumberOfItems(gameState);
			k++;
		}
		else
		{
			continue;
		}
	}
	beer.UseItem(gameState);
	GetNumberOfItems(gameState);
}
void InventoryManager::UseMagnifier(GameState& gameState) 
{ 
	int k = 0;
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] == GameEnums::MAGNIFIER && k == 0)
		{
			inventory[i] = GameEnums::NOITEMS;
			SetMagnifiers(GetMagnifiers() - 1);
			GetNumberOfItems(gameState);
			k++;
		}
		else
		{
			continue;
		}
	}
	magnifier.UseItem(gameState);
	GetNumberOfItems(gameState);
}
void InventoryManager::UseHandCuffs(GameState& gameState) 
{ 
	int k = 0;
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] == GameEnums::HANDCUFFS && k == 0)
		{
			inventory[i] = GameEnums::NOITEMS;
			SetHandCuffs(GetHandCuffs() - 1);
			GetNumberOfItems(gameState);
			k++;
		}
		else
		{
			continue;
		}
	}
	handCuffs.UseItem(gameState);
	GetNumberOfItems(gameState);
}
void InventoryManager::UseInverter(GameState& gameState) 
{ 
	int k = 0;
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] == GameEnums::INVERTER && k == 0)
		{
			inventory[i] = GameEnums::NOITEMS;
			SetInverters(GetInverters() - 1);
			GetNumberOfItems(gameState);
			k++;
		}
		else
		{
			continue;
		}
	}
	inverter.UseItem(gameState);
	GetNumberOfItems(gameState);
}
void InventoryManager::UseCellPhone(GameState& gameState) 
{ 
	int k = 0;
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i] == GameEnums::CELLPHONE && k == 0)
		{
			inventory[i] = GameEnums::NOITEMS;
			SetCellPhones(GetCellPhones() - 1);
			GetNumberOfItems(gameState);
			k++;
		}
		else
		{
			continue;
		}
	}
	cellPhone.UseItem(gameState);
	GetNumberOfItems(gameState);
}
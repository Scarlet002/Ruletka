#pragma once
#include "Inventory.h"
#include "GameConfig.h"
#include "CellPhone.h"
#include "Beer.h"
#include "HandCuffs.h"
#include "Saw.h"
#include "Inverter.h"
#include "Magnifier.h"
#include "ForwardDeclarations.h"
#include <vector>
#include <stdexcept>
#include <algorithm>

using std::vector;

class InventoryManager : public Inventory
{
private:
	int numberOfItems;
	int free;
	int saws;
	int cellPhones;
	int beers;
	int handCuffsAmount;
	int magnifiers;
	int inverters;
	vector<int> inventory;
	GameConfig& gameConfig;
	Saw saw;
	Magnifier magnifier;
	HandCuffs handCuffs;
	Beer beer;
	Inverter inverter;
	CellPhone cellPhone;

public:
	int inventorySize;

	InventoryManager(GameConfig& gameConfig);

	void GetRandomItem(GameState& gameState) override;
	void GetNumberOfItems(GameState& gameState) override;

	int SetFreeSlots(int newFree) override;
	int SetSaws(int newSaws) override;
	int SetBeers(int newBeers) override;
	int SetMagnifiers(int newMagnifiers) override;
	int SetHandCuffs(int newHandCuffs) override;
	int SetInverters(int newInverters) override;
	int SetCellPhones(int newCellPhones) override;
	void SetInventory(const vector<int>& newInventory) override;

	int GetFreeSlots() const override;
	int GetSaws() const override;
	int GetBeers() const override;
	int GetMagnifiers() const override;
	int GetHandCuffs() const override;
	int GetInverters() const override;
	int GetCellPhones() const override;
	const vector<int>& GetInventory() const override;

	void ResetInventory(GameState& gameState) override;
	void UseSaw(GameState& gameState) override;
	void UseBeer(GameState& gameState) override;
	void UseMagnifier(GameState& gameState) override;
	void UseHandCuffs(GameState& gameState) override;
	void UseInverter(GameState& gameState) override;
	void UseCellPhone(GameState& gameState) override;

	~InventoryManager() {};
};


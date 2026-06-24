#pragma once
#include "IInventory.h"
#include "GameConfig.h"
#include "ForwardDeclarations.h"
#include <cstdint>
#include <unordered_map>

class Inventory : public IInventory
{
private:
	std::unordered_map<uint8_t, uint8_t> items;
public:
	explicit Inventory() = default;

	void GetRandomItems() override;
	void UseItem(uint8_t itemType) override;
	void ResetInventory() override;
	void AddItemType(uint8_t itemType, uint8_t itemCount) override;	

	void SetItemCount(uint8_t itemType, uint8_t newItemCount) override;

	uint8_t GetItemCount(uint8_t itemType) const noexcept override;
	uint8_t GetItemsCount() const noexcept override;
};


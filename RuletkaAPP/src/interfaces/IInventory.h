#pragma once
#include <cstdint>

class IInventory
{
protected:
	IInventory() = default;
public:
	IInventory(const IInventory&) = delete;
	IInventory& operator=(const IInventory&) = delete;

	IInventory(IInventory&&) = delete;
	IInventory& operator=(IInventory&&) = delete;

	virtual void GetRandomItems() = 0;
	virtual void UseItem(uint8_t itemType) = 0;
	virtual void ResetInventory() = 0;
	virtual void AddItemType(uint8_t itemType, uint8_t itemCount) = 0;

	// Inventory setters
	virtual void SetItemCount(uint8_t itemType, uint8_t newItemCount) = 0;

	// Inventory getters
	[[nodiscard]] virtual uint8_t GetItemCount(uint8_t itemType) const noexcept = 0;
	[[nodiscard]] virtual uint8_t GetItemsCount() const noexcept = 0;

	virtual ~IInventory() = default;
};


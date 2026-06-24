#include "Inventory.h"
#include "GameEnums.h"
#include "GameConfig.h"
#include "RNG.h"
#include <algorithm>
#include <cstdint>

void Inventory::UseItem(uint8_t itemType)
{
	auto it = items.find(itemType);
	if (it != items.end() && it->second > GameConfig::minItems) it->second--;
}
void Inventory::GetRandomItems()
{
	if (GetItemsCount() < GameConfig::maxItemsFiveSlots)
	{
		for (uint8_t i = 0; i < GameConfig::maxItemsGained; ++i)
		{
			uint8_t itemType = RNG::GetRN(GameConfig::minItemTypeRNG, GameConfig::maxItemTypeRNG);
			auto it = items.find(itemType);
			if (it != items.end())
			{
				if (it->second < GameConfig::maxItemsFiveSlots) it->second++;
			}
			else items[itemType] += 1;
		}
	}
}
void Inventory::ResetInventory() { for (auto& item : items) item.second = GameConfig::minItems; }
void Inventory::AddItemType(uint8_t itemType, uint8_t item) { items[itemType] = item; }
void Inventory::SetItemCount(uint8_t itemType, uint8_t newItemCount) 
{
	items[itemType] = std::clamp(static_cast<int>(newItemCount)
		, 0, static_cast<int>(GameConfig::maxItemsFiveSlots));
}

uint8_t Inventory::GetItemCount(uint8_t itemType) const noexcept 
{
	auto it = items.find(itemType);
	return (it != items.end()) ? it->second : GameConfig::minItems;
}
uint8_t Inventory::GetItemsCount() const noexcept 
{ 
	uint8_t total = GameConfig::minItems;
	for (const auto& item : items) total += item.second;
	return total;
}
#pragma once
#include "ForwardDeclarations.h"
#include "IPlayer.h"
#include "IHpManager.h"
#include "Inventory.h"
#include <string>
#include <memory>
#include <vector>
#include <cstdint>

class Player : public IPlayer
{
private:
    std::string name;
    std::string type;
	std::unique_ptr<Inventory> inventory;
	std::unique_ptr<IHpManager> hp;
public:
    Player(const std::string& playerName,
        const std::string& playerType);

	void SetHP(uint8_t newHP) override;
    void LoseHP(uint8_t damage) override;
    void RegainHP() override;
    void ResetHP() override;
    int8_t GetHP() const override;

    bool IsAlive() const override;
    bool GetType() const override;
    std::string GetName() const override;

    uint8_t GetFreeSlots() const override;
    uint8_t GetSaws() const override;
    uint8_t GetBeers() const override;
    uint8_t GetMagnifiers() const override;
    uint8_t GetHandCuffs() const override;
    uint8_t GetInverters() const override;
    uint8_t GetCellPhones() const override;
    const std::vector<uint8_t>& GetInventory() const override;

    void SetFreeSlots(uint8_t newFree) override;
	void SetSaws(uint8_t newSaws) override;
	void SetBeers(uint8_t newBeers) override;
	void SetMagnifiers(uint8_t newMagnifiers) override;
	void SetHandCuffs(uint8_t newHandCuffs) override;
	void SetInverters(uint8_t newInverters) override;
	void SetCellPhones(uint8_t newCellPhones) override;
	void SetInventory(const std::vector<uint8_t>& newInventory) override;

    void GetRandomItem() override;
    void GetNumberOfItems() override;
    void ResetInventory() override;
    void UseItem(uint8_t itemType) override;
};
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

	void SetHP(int newHP) override;
    void LoseHP(int damage) override;
    void RegainHP() override;
    void ResetHP() override;
    int GetHP() const override;

    bool IsAlive() const override;
    bool GetType() const override;
    std::string GetName() const override;

    int GetFreeSlots() const override;
    int GetSaws() const override;
    int GetBeers() const override;
    int GetMagnifiers() const override;
    int GetHandCuffs() const override;
    int GetInverters() const override;
    int GetCellPhones() const override;
    const std::vector<uint8_t>& GetInventory() const override;

    void SetFreeSlots(int newFree) override;
	void SetSaws(int newSaws) override;
	void SetBeers(int newBeers) override;
	void SetMagnifiers(int newMagnifiers) override;
	void SetHandCuffs(int newHandCuffs) override;
	void SetInverters(int newInverters) override;
	void SetCellPhones(int newCellPhones) override;
	void SetInventory(const std::vector<uint8_t>& newInventory) override;

    void GetRandomItem() override;
    void GetNumberOfItems() override;
    void ResetInventory() override;
    void UseItem(int itemType) override;
};
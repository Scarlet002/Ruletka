#pragma once
#include "ForwardDeclarations.h"
#include "IPlayer.h"
#include "HP.h"
#include "Inventory.h"
#include "HPManager.h"
#include "IInventory.h"
#include <string>
#include <memory>
#include <cstdint>
#include <utility>

class Player : public IPlayer
{
private:
    std::string name;
    std::string type;
    std::shared_ptr<HP> hp;
    std::shared_ptr<IInventory> inventory;
public:
    Player(std::shared_ptr<HP> hp, std::shared_ptr<IInventory> inventory,
        std::string playerName, std::string playerType);

    IInventory& GetInventory() noexcept override;
    HP& GetHP() noexcept override;

	void SetName(const std::string& newName) override;
	void SetType(const std::string& newType) override;

    bool IsAlive() const noexcept override;
    bool GetType() const noexcept override;
	std::string GetTypeString() const noexcept override;
    std::string GetName() const noexcept override;
};
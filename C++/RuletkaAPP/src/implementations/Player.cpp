#include "Player.h"
#include <string>
#include <cstdint>

Player::Player(std::shared_ptr<HP> hp, std::shared_ptr<IInventory> inventory,
	std::string playerName, std::string playerType)
	: hp(std::move(hp))
	, inventory(std::move(inventory))
    , name(playerName)
	, type(playerType) {}

IInventory& Player::GetInventory() noexcept { return *inventory; }

HP& Player::GetHP() noexcept { return *hp; }

void Player::SetName(const std::string& newName) { name = newName; }

void Player::SetType(const std::string& newType) { type = newType; }

bool Player::IsAlive() const noexcept { return hp->GetHP() > 0; }

bool Player::GetType() const noexcept { return type == "human" || type == "Human" || type == "HUMAN"; }

std::string Player::GetTypeString() const noexcept { return type; }

std::string Player::GetName() const noexcept { return name; }
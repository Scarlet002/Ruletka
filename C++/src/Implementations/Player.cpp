#include "Player.h"
#include "HpManager.h"
#include "InventoryManager.h"
#include <string>
#include <vector>
#include <cstdint>

Player::Player(const std::string& playerName, 
	const std::string& playerType) 
	: hp(std::make_unique<HpManager>())
	, inventory(std::make_unique<InventoryManager>())
    , name(playerName)
	, type(playerType) {}

void Player::SetHP(uint8_t newHP) { hp->SetHP(newHP); }

void Player::LoseHP(uint8_t damage) { hp->LoseHP(damage); }

void Player::RegainHP() { hp->RegainHP(); }

void Player::ResetHP() { hp->ResetHP(); }

int8_t Player::GetHP() const { return hp->GetHP(); }

bool Player::IsAlive() const { return hp->GetHP() > 0; }

bool Player::GetType() const { return type == "human" || type == "Human" || type == "HUMAN"; }

std::string Player::GetName() const { return name; }

uint8_t Player::GetFreeSlots() const { return inventory->GetFreeSlots(); }

uint8_t Player::GetSaws() const { return inventory->GetSaws(); }

uint8_t Player::GetBeers() const { return inventory->GetBeers(); }

uint8_t Player::GetMagnifiers() const { return inventory->GetMagnifiers(); }

uint8_t Player::GetHandCuffs() const { return inventory->GetHandCuffs(); }

uint8_t Player::GetInverters() const { return inventory->GetInverters(); }

uint8_t Player::GetCellPhones() const { return inventory->GetCellPhones(); }

const std::vector<uint8_t>& Player::GetInventory() const { return inventory->GetInventory(); }

void Player::GetRandomItem() { inventory->GetRandomItem(); }

void Player::GetNumberOfItems() { inventory->GetNumberOfItems(); }

void Player::UseItem(uint8_t itemType) { inventory->UseItem(itemType); }

void Player::ResetInventory() { inventory->ResetInventory(); }

void Player::SetFreeSlots(uint8_t newFree) { inventory->SetFreeSlots(newFree); }

void Player::SetSaws(uint8_t newSaws) { inventory->SetSaws(newSaws); }

void Player::SetBeers(uint8_t newBeers) { inventory->SetBeers(newBeers); }

void Player::SetMagnifiers(uint8_t newMagnifiers) { inventory->SetMagnifiers(newMagnifiers); }

void Player::SetHandCuffs(uint8_t newHandCuffs) { inventory->SetHandCuffs(newHandCuffs); }

void Player::SetInverters(uint8_t newInverters) { inventory->SetInverters(newInverters); }

void Player::SetCellPhones(uint8_t newCellPhones) { inventory->SetCellPhones(newCellPhones); }

void Player::SetInventory(const std::vector<uint8_t>& newInventory) { inventory->SetInventory(newInventory); }
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

void Player::SetHP(int newHP) { hp->SetHP(newHP); }
void Player::LoseHP(int damage) { hp->LoseHP(damage); }
void Player::RegainHP() { hp->RegainHP(); }
void Player::ResetHP() { hp->ResetHP(); }
int Player::GetHP() const { return hp->GetHP(); }

bool Player::IsAlive() const { return hp->GetHP() > 0; }
bool Player::GetType() const { return type == "human" || type == "Human" || type == "HUMAN"; }
std::string Player::GetName() const { return name; }

int Player::GetFreeSlots() const { return inventory->GetFreeSlots(); }
int Player::GetSaws() const { return inventory->GetSaws(); }
int Player::GetBeers() const { return inventory->GetBeers(); }
int Player::GetMagnifiers() const { return inventory->GetMagnifiers(); }
int Player::GetHandCuffs() const { return inventory->GetHandCuffs(); }
int Player::GetInverters() const { return inventory->GetInverters(); }
int Player::GetCellPhones() const { return inventory->GetCellPhones(); }
const std::vector<uint8_t>& Player::GetInventory() const { return inventory->GetInventory(); }
void Player::GetRandomItem() { inventory->GetRandomItem(); }
void Player::GetNumberOfItems() { inventory->GetNumberOfItems(); }
void Player::UseItem(int itemType) { inventory->UseItem(itemType); }
void Player::ResetInventory() { inventory->ResetInventory(); }

void Player::SetFreeSlots(int newFree) { inventory->SetFreeSlots(newFree); }
void Player::SetSaws(int newSaws) { inventory->SetSaws(newSaws); }
void Player::SetBeers(int newBeers) { inventory->SetBeers(newBeers); }
void Player::SetMagnifiers(int newMagnifiers) { inventory->SetMagnifiers(newMagnifiers); }
void Player::SetHandCuffs(int newHandCuffs) { inventory->SetHandCuffs(newHandCuffs); }
void Player::SetInverters(int newInverters) { inventory->SetInverters(newInverters); }
void Player::SetCellPhones(int newCellPhones) { inventory->SetCellPhones(newCellPhones); }
void Player::SetInventory(const std::vector<uint8_t>& newInventory) { inventory->SetInventory(newInventory); }
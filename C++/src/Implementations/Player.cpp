#include "Player.h"
#include "HpManger.h"
#include "GameState.h"
#include "ShootingManager.h"
#include "DecisionManager.h"
#include "InventoryManager.h"
#include <string>
#include <vector>

using std::vector;

Player::Player(const string& playerName, const string& playerType, GameConfig& gameConfig) :
    name(playerName), 
    type(playerType),
    inventory(gameConfig),
    hp(gameConfig)
{
    decision = std::make_unique<DecisionManager>();
	gun = std::make_unique<ShootingManager>();
}

void Player::LoseHP(GameState& gameState) { hp.LoseHP(gameState); }
void Player::RegainHP() { hp.RegainHP(); }
void Player::ResetHP() { hp.ResetHP(); }
int Player::GetHP() const { return hp.GetHP(); }
void Player::SetHP(int newHP) { hp.SetHP(newHP); }
bool Player::isAlive() const { return hp.GetHP() > 0; }
bool Player::IsHuman() const { return type == "human" || type == "Human"; }
bool Player::IsComputer() const { return type == "computer" || type == "Computer"; }

int Player::MakeDecision(GameState& gameState) const { return decision->MakeDecision(gameState); }

void Player::Shoot(GameState& gameState) { gun->Shoot(gameState); }

int Player::SetFreeSlots(int newFree) { return inventory.SetFreeSlots(newFree); }
int Player::SetSaws(int newSaws) { return inventory.SetSaws(newSaws); }
int Player::SetBeers(int newBeers) { return inventory.SetBeers(newBeers); }
int Player::SetMagnifiers(int newMagnifiers) { return inventory.SetMagnifiers(newMagnifiers); }
int Player::SetHandCuffs(int newHandCuffs) { return inventory.SetHandCuffs(newHandCuffs); }
int Player::SetInverters(int newInverters) { return inventory.SetInverters(newInverters); }
int Player::SetCellPhones(int newCellPhones) { return inventory.SetCellPhones(newCellPhones); }
void Player::SetInventory(const vector<int>& newInventory) { inventory.SetInventory(newInventory); }

int Player::GetFreeSlots() const { return inventory.GetFreeSlots(); }
int Player::GetSaws() const { return inventory.GetSaws(); }
int Player::GetBeers() const { return inventory.GetBeers(); }
int Player::GetMagnifiers() const { return inventory.GetMagnifiers(); }
int Player::GetHandCuffs() const { return inventory.GetHandCuffs(); }
int Player::GetInverters() const { return inventory.GetInverters(); }
int Player::GetCellPhones() const { return inventory.GetCellPhones(); }
const vector<int>& Player::GetInventory() const { return inventory.GetInventory(); }

void Player::GetRandomItem(GameState& gameState) { inventory.GetRandomItem(gameState); }
void Player::GetNumberOfItems(GameState& gameState) 
{ 
    inventory.GetNumberOfItems(gameState);
}
void Player::ResetInventory(GameState& gameState) 
{ 
    inventory.ResetInventory(gameState); 
}
void Player::UseSaw(GameState& gameState) { inventory.UseSaw(gameState); }
void Player::UseMagnifier(GameState& gameState) { inventory.UseMagnifier(gameState); }
void Player::UseBeer(GameState& gameState) { inventory.UseBeer(gameState); }
void Player::UseCellPhone(GameState& gameState) { inventory.UseCellPhone(gameState); }
void Player::UseInverter(GameState& gameState) { inventory.UseInverter(gameState); }
void Player::UseHandCuffs(GameState& gameState) { inventory.UseHandCuffs(gameState); }
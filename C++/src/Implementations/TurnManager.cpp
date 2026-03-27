#include "TurnManager.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include <cstdlib>

// Setters and actions
void TurnManager::SetDifficulty(int newDifficulty) { difficulty = newDifficulty; }
void TurnManager::SetItem(int newItem) { item = newItem; }
void TurnManager::SetStarter(int newStarter) { starter = newStarter; }
void TurnManager::SetChoice(int newChoice) { choice = newChoice; }
void TurnManager::SetTarget(int newTarget){ target = newTarget; }
void TurnManager::SetShooter(int newShooter) { shooter = newShooter; }
void TurnManager::SetDamage(int newDamage) { damage = newDamage; }
void TurnManager::SetStateOfHandCuffs(bool newState) { wereHandCuffsUsed = newState; }
void TurnManager::SetStateOfInventory(bool newState) { wasInventoryShownForComputer = newState; }
void TurnManager::SetStateOfMagnifier(bool newState) { wasMagnifierUsed = newState; };
void TurnManager::SetStateOfCellPhone(bool newState) { wasCellPhoneUsed = newState; };
void TurnManager::SetHitProbability(double newProbability) { hitProbability = newProbability; }
int TurnManager::RandomizeStarter()
{
    starter = rand() % GameConfig::numberOfPlayers;
    return starter;
}
void TurnManager::ResetDamage() { SetDamage(GameConfig::defaultDamage); }

// Getters
int TurnManager::GetDifficulty() const { return difficulty; }
int TurnManager::GetStarter() const { return starter; }
int TurnManager::GetChoice() const { return choice; }
int TurnManager::GetTarget() const { return target; }
int TurnManager::GetShooter() const { return shooter; }
int TurnManager::GetDamage() const { return damage; }
int TurnManager::GetItem() const { return item; }
bool TurnManager::GetStateOfHandCuffs() const { return wereHandCuffsUsed; }
bool TurnManager::GetStateOfInventory() const { return wasInventoryShownForComputer; }
bool TurnManager::GetStateOfMagnifier() const { return wasMagnifierUsed; }
bool TurnManager::GetStateOfCellPhone() const { return wasCellPhoneUsed; }

double TurnManager::GetHitProbability() const { return hitProbability; }
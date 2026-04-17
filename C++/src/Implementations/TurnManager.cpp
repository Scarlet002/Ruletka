#include "TurnManager.h"
#include "GameConfig.h"
#include "GameEnums.h"
#include <cstdlib>

// Setters and actions
void TurnManager::SetDifficulty(int8_t newDifficulty) { difficulty = newDifficulty; }

void TurnManager::SetItem(uint8_t newItem) { item = newItem; }

void TurnManager::SetStarter(uint8_t newStarter) { starter = newStarter; }

void TurnManager::SetChoice(int8_t newChoice) 
{ 
	SetPreviousChoice(choice);
	choice = newChoice;
}

void TurnManager::SetPreviousChoice(int8_t newPreviousChoice) { previousChoice = newPreviousChoice; }

void TurnManager::SetTarget(uint8_t newTarget){ target = newTarget; }

void TurnManager::SetShooter(uint8_t newShooter) { shooter = newShooter; }

void TurnManager::SetDamage(uint8_t newDamage) { damage = newDamage; }

void TurnManager::SetCurrentMenu(uint8_t newMenu) { currentMenu = newMenu; }

void TurnManager::SetRecentDifficulty(uint8_t newDifficulty) { recentDifficulty = newDifficulty; }

void TurnManager::SetStateOfHandCuffs(bool newState) { wereHandCuffsUsed = newState; }

void TurnManager::SetStateOfInventory(bool newState) { wasInventoryShownForComputer = newState; }

void TurnManager::SetStateOfMagnifier(bool newState) { wasMagnifierUsed = newState; };

void TurnManager::SetStateOfCellPhone(bool newState) { wasCellPhoneUsed = newState; };

void TurnManager::SetStateOfLog(bool newState) { wasLogCleared = newState; }

void TurnManager::SetStateOfAutoSave(bool newState) { wasAutoSaved = newState; }

void TurnManager::SetHitProbability(float newProbability) { hitProbability = newProbability; }

void TurnManager::SetIsOnePlayerAlive(bool newState) { isOnePlayerAlive = newState; }

uint8_t TurnManager::RandomizeStarter() { return starter = rand() % GameConfig::numberOfPlayers; }

void TurnManager::ResetDamage() { SetDamage(GameConfig::defaultDamage); }

// Getters
int8_t TurnManager::GetDifficulty() const { return difficulty; }

uint8_t TurnManager::GetStarter() const { return starter; }

int8_t TurnManager::GetChoice() const { return choice; }

int8_t TurnManager::GetPreviousChoice() const { return previousChoice; }

uint8_t TurnManager::GetTarget() const { return target; }

uint8_t TurnManager::GetShooter() const { return shooter; }

uint8_t TurnManager::GetDamage() const { return damage; }

uint8_t TurnManager::GetItem() const { return item; }

uint8_t TurnManager::GetCurrentMenu() const { return currentMenu; }

uint8_t TurnManager::GetRecentDifficulty() const { return recentDifficulty; }

bool TurnManager::GetStateOfHandCuffs() const { return wereHandCuffsUsed; }

bool TurnManager::GetStateOfInventory() const { return wasInventoryShownForComputer; }

bool TurnManager::GetStateOfMagnifier() const { return wasMagnifierUsed; }

bool TurnManager::GetStateOfCellPhone() const { return wasCellPhoneUsed; }

bool TurnManager::GetStateOfLog() const { return wasLogCleared; }

bool TurnManager::GetStateOfAutoSave() const { return wasAutoSaved; }

bool TurnManager::GetIsOnePlayerAlive() const { return isOnePlayerAlive; }

float TurnManager::GetHitProbability() const { return hitProbability; }
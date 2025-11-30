#include "Player.h"
#include "HpManger.h"
#include "GameState.h"
#include "ShootingManager.h"
#include "DecisionManger.h"
#include <string>

static DecisionManager decision;
static ShootingManager gun;

Player::Player(const string& playerName, const string& playerType, HpManager& hpManager)
    : name(playerName), type(playerType), hp(hpManager) {}

void Player::LoseHP() { hp.LoseHP(); }
void Player::RegainHP() { hp.RegainHP(); }
void Player::ResetHP() { hp.ResetHP(); }
int Player::GetHP() const { return hp.GetHP(); }
void Player::SetHP(int newHP) { hp.SetHP(newHP); }
bool Player::isAlive() const { return hp.GetHP() > 0; }
bool Player::IsHuman() const { return type == "czlowiek" || type == "Czlowiek"; }
bool Player::IsComputer() const { return type == "komputer" || type == "Komputer"; }
int Player::MakeDecision(GameState& gameState) const { return decision.MakeDecision(gameState); }
void Player::Shoot(GameState& gameState) { gun.Shoot(gameState); }
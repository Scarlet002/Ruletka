#include "GameState.h"
#include "Player.h"
#include "MagazineManager.h"
#include "TurnManager.h"

GameState::GameState() 
	: human(std::make_unique<Player>("Human", "human"))
	, computer(std::make_unique<Player>("Computer", "computer"))
	, magazine(std::make_unique<MagazineManager>()) 
	, turn(std::make_unique<TurnManager>()) {}

void GameState::CopyStateToSnapshot(const GameState& state)
{
    // Turn
    turn->SetStarter(state.turn->GetStarter());
    turn->SetDifficulty(state.turn->GetDifficulty());
    turn->SetChoice(state.turn->GetChoice());
    turn->SetShooter(state.turn->GetShooter());
    turn->SetTarget(state.turn->GetTarget());
    turn->SetItem(state.turn->GetItem());
    turn->SetDamage(state.turn->GetDamage());
    turn->SetStateOfHandCuffs(state.turn->GetStateOfHandCuffs());
    turn->SetStateOfMagnifier(state.turn->GetStateOfMagnifier());
    turn->SetStateOfCellPhone(state.turn->GetStateOfCellPhone());

    // Human
    human->SetHP(state.human->GetHP());
    human->SetInventory(state.human->GetInventory());
    human->SetSaws(state.human->GetSaws());
    human->SetBeers(state.human->GetBeers());
    human->SetMagnifiers(state.human->GetMagnifiers());
    human->SetInverters(state.human->GetInverters());
    human->SetHandCuffs(state.human->GetHandCuffs());
    human->SetCellPhones(state.human->GetCellPhones());

    // Computer
    computer->SetHP(state.computer->GetHP());
    computer->SetInventory(state.computer->GetInventory());
    computer->SetSaws(state.computer->GetSaws());
    computer->SetBeers(state.computer->GetBeers());
    computer->SetMagnifiers(state.computer->GetMagnifiers());
    computer->SetInverters(state.computer->GetInverters());
    computer->SetHandCuffs(state.computer->GetHandCuffs());
    computer->SetCellPhones(state.computer->GetCellPhones());

    // Magazine
    magazine->SetMagazine(state.magazine->GetMagazine());
    magazine->CheckBullets();
}
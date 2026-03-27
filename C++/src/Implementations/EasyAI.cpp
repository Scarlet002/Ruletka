#include "EasyAI.h"
#include "GameConfig.h"
#include "GameState.h"
#include <cstdlib>
#include <cstdint>

EasyAI::EasyAI(const GameState& state) 
	: state(state) {}

int EasyAI::MakeDecision() const
{
	uint8_t bulletTypes = GameConfig::numberOfBulletTypes;
	uint8_t choice = rand() % bulletTypes;
	return choice;
}
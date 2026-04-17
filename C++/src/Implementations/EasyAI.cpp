#include "EasyAI.h"
#include "GameConfig.h"
#include "GameState.h"
#include <cstdlib>
#include <cstdint>

EasyAI::EasyAI(const GameState& state) 
	: state(state) {}

int8_t EasyAI::Decision() const { return rand() % GameConfig::numberOfBulletTypes; }
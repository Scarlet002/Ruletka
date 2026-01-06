#pragma once
#include "ForwardDeclarations.h"
#include "IShootingManager.h"

class ShootingManager : public IShootingManager
{
public:

	ShootingManager() {};

	void Shoot(GameState& gameState) override;

	~ShootingManager() {};
};
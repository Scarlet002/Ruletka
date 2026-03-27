#pragma once
#include "ForwardDeclarations.h"
#include "ITurnProcessor.h"

class TurnProcessor : ITurnProcessor
{
private:
	GameState& state;

	inline void Heal(IPlayer& shooter);
	inline void Shot(const IPlayer& shooter, const IPlayer& target);
	inline void UseItem(const IPlayer& shooter, const IPlayer& target);
	inline void Exit(const IPlayer& shooter, const IPlayer& target);
	inline void Load(const IPlayer& shooter, const IPlayer& target);
	inline void Save(const IPlayer& shooter, const IPlayer& target);
	inline void Difficulty(const IPlayer& shooter, const IPlayer& target);
public:
	explicit TurnProcessor(GameState& state);

	void ProcessTurn(IPlayer& shooter, IPlayer& target) override;
};
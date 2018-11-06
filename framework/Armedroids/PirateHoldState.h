#pragma once
#include "EnemyState.h"
#include "Pirate.h"

namespace CompEngine
{
class PirateHoldState : public IEnemyState
{
private:
	Pirate* pirate;

public:
	PirateHoldState(Pirate* script);

private:
	void hold();

public:
	virtual void UpdateState();

	virtual void ToPatrolState();

	virtual void ToChaseState();

	virtual void ToAttackState();

	virtual void ToIdleState();
};
}

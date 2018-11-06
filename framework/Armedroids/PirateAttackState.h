#pragma once
#include "EnemyState.h"
#include "Pirate.h"

namespace CompEngine
{
class PirateAttackState : public IEnemyState
{
private:
	Pirate* pirate;

public:
	PirateAttackState(Pirate* script);

private:
	void attack();

public:
	virtual void UpdateState();

	virtual void ToPatrolState();

	virtual void ToChaseState();

	virtual void ToAttackState();

	virtual void ToIdleState();
};
}

#pragma once
#include "EnemyState.h"
#include "Pirate.h"

namespace CompEngine
{
	class PirateChaseState : public IEnemyState
	{
	private:
		Pirate* pirate;

	public:
		PirateChaseState(Pirate* script);

	private:
		void chase();

	public:
		virtual void UpdateState();

		virtual void ToPatrolState();

		virtual void ToChaseState();

		virtual void ToAttackState();

		virtual void ToIdleState();
	};
}
#pragma once
#include "EnemyState.h"
#include "Shark.h"

namespace CompEngine
{
	class SharkPatrolState : public IEnemyState
	{
	private:
		Shark* shark;

	public:
		SharkPatrolState(Shark* script);

	private:
		void patrol();

	public:
		virtual void UpdateState();

		virtual void ToPatrolState();

		virtual void ToChaseState();

		virtual void ToAttackState();

		virtual void ToIdleState();
	};
}

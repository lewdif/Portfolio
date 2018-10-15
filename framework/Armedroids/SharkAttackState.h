#pragma once
#include "EnemyState.h"
#include "Shark.h"

namespace CompEngine
{
	class SharkAttackState : public IEnemyState
	{
	private:
		Shark* shark;

	public:
		SharkAttackState(Shark* script);

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

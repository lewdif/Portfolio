#pragma once
#include "EnemyState.h"
#include "Shark.h"

namespace CompEngine
{
	class SharkChaseState : public IEnemyState
	{
	private:
		Shark* shark;

	public:
		SharkChaseState(Shark* script);

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

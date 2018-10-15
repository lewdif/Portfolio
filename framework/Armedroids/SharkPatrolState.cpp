#include "SharkPatrolState.h"

namespace CompEngine
{
	SharkPatrolState::SharkPatrolState(Shark* script)
	{
		shark = script;
	}

	void SharkPatrolState::patrol()
	{
		if (shark->GetDistToPlayer() < 500)
		{
			ToChaseState();
		}

		shark->Patrol();
	}

	void SharkPatrolState::UpdateState()
	{
		patrol();
	}

	void SharkPatrolState::ToPatrolState()
	{

	}

	void SharkPatrolState::ToChaseState()
	{
		shark->ChangeStateTo(ENEMY_STATUS::CHASE);
	}

	void SharkPatrolState::ToAttackState()
	{

	}

	void SharkPatrolState::ToIdleState()
	{

	}
}
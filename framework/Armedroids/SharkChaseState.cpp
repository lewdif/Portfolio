#include "SharkChaseState.h"

namespace CompEngine
{
	SharkChaseState::SharkChaseState(Shark* script)
	{
		shark = script;
	}

	void SharkChaseState::chase()
	{
		if (shark->GetDistToPlayer() < 180)
		{
			ToAttackState();
		}
		else if (shark->GetDistToPlayer() >= 500)
		{
			ToPatrolState();
		}

		shark->Chase();
	}

	void SharkChaseState::UpdateState()
	{
		chase();
	}

	void SharkChaseState::ToPatrolState()
	{
		shark->ChangeStateTo(ENEMY_STATUS::PATROL);
	}

	void SharkChaseState::ToChaseState()
	{

	}

	void SharkChaseState::ToAttackState()
	{
		shark->ChangeStateTo(ENEMY_STATUS::ATTACK);
	}

	void SharkChaseState::ToIdleState()
	{

	}
}

#include "SharkAttackState.h"

namespace CompEngine
{
	SharkAttackState::SharkAttackState(Shark* script)
	{
		shark = script;
	}

	void SharkAttackState::attack()
	{
		if (shark->GetDistToPlayer() >= 180)
		{
			ToChaseState();
		}
		
		shark->Attack();
	}

	void SharkAttackState::UpdateState()
	{
		attack();
	}

	void SharkAttackState::ToPatrolState()
	{

	}
	
	void SharkAttackState::ToChaseState()
	{
		shark->ChangeStateTo(ENEMY_STATUS::CHASE);
	}
	
	void SharkAttackState::ToAttackState()
	{
		
	}
	
	void SharkAttackState::ToIdleState()
	{

	}
}
#include "PirateAttackState.h"


namespace CompEngine
{
	PirateAttackState::PirateAttackState(Pirate* script)
	{
		pirate = script;
	}

	void PirateAttackState::attack()
	{
		if (pirate->GetDistToPlayer() >= 600)
		{
			ToChaseState();
		}

		pirate->Attack();
	}

	void PirateAttackState::UpdateState()
	{
		attack();
	}

	void PirateAttackState::ToPatrolState()
	{

	}

	void PirateAttackState::ToChaseState()
	{
		pirate->ChangeStateTo(ENEMY_STATUS::CHASE);
	}

	void PirateAttackState::ToAttackState()
	{

	}

	void PirateAttackState::ToIdleState()
	{

	}
}
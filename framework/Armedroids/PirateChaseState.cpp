#include "PirateChaseState.h"


namespace CompEngine
{
	PirateChaseState::PirateChaseState(Pirate* script)
	{
		pirate = script;
	}

	void PirateChaseState::chase()
	{
		if (pirate->GetDistToPlayer() < 600)
		{
			ToAttackState();
		}
		else if (pirate->GetDistToPlayer() >= 800)
		{
			ToPatrolState();
		}

		pirate->Chase();
	}

	void PirateChaseState::UpdateState()
	{
		chase();
	}

	void PirateChaseState::ToPatrolState()
	{
		pirate->ChangeStateTo(ENEMY_STATUS::PATROL);
	}

	void PirateChaseState::ToChaseState()
	{

	}

	void PirateChaseState::ToAttackState()
	{
		pirate->ChangeStateTo(ENEMY_STATUS::ATTACK);
	}

	void PirateChaseState::ToIdleState()
	{

	}
}

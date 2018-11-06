#include "PirateHoldState.h"


namespace CompEngine
{
	PirateHoldState::PirateHoldState(Pirate* script)
	{
		pirate = script;
	}

	void PirateHoldState::hold()
	{
		if (pirate->GetDistToPlayer() < 800)
		{
			ToChaseState();
		}

		pirate->Hold();
	}

	void PirateHoldState::UpdateState()
	{
		hold();
	}

	void PirateHoldState::ToPatrolState()
	{

	}

	void PirateHoldState::ToChaseState()
	{
		pirate->ChangeStateTo(ENEMY_STATUS::CHASE);
	}

	void PirateHoldState::ToAttackState()
	{

	}

	void PirateHoldState::ToIdleState()
	{

	}
}
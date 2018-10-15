#pragma once

namespace CompEngine
{
	enum ENEMY_STATUS{PATROL, CHASE, ATTACK, IDLE};

	typedef struct ENEMY_INFO
	{
		int LV;
		int HP;
		int REM_HP;
		int ATK;
		int DEF;
		int SPD;
	}Status;

	class IEnemyState
	{
	public:
		virtual void UpdateState() = 0;
		virtual void ToPatrolState() = 0;
		virtual void ToChaseState() = 0;
		virtual void ToAttackState() = 0;
		virtual void ToIdleState() = 0;
	};
}